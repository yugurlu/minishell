/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 13:27:42 by yugurlu           #+#    #+#             */
/*   Updated: 2023/03/24 16:49:52 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	pipe_initialize(t_parsed_cmd_managed_list *parse)
{
	while (parse)
	{
		pipe(parse->fd);
		parse = parse->next;
	}
}

char	*path_finder(char *cmd)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	while (g_myenv.path[i])
	{
		path = join_but_no_free(g_myenv.path[i], "/");
		path = ft_strjoin(path, cmd);
		if (access(path, F_OK) == 0)
		{
			free(cmd);
			return (path);
		}
		free(path);
		i++;
	}
	error_command(cmd);
	return (NULL);
}

void	choose_execution(t_parsed_cmd_managed_list *parse)
{
	if (is_builtin(parse->command->argv[0]))
		exec_builtin(parse, parse->command->argv[0]);
	else
	{
		if (access(parse->command->argv[0], F_OK) == 0)
			execve(parse->command->argv[0], parse->command->argv, g_myenv.env);
		else
		{
			parse->command->argv[0] = path_finder(parse->command->argv[0]);
			execve(parse->command->argv[0], parse->command->argv, g_myenv.env);
		}
	}
	while (parse->previous)
		parse = parse->previous;
	free_env_list();
	free_parsed_cmd_managed_list(parse);
	exit(0);
}

void	child_execution(t_parsed_cmd_managed_list *parse)
{
	parse->pid = fork();
	if (parse->pid == 0)
	{
		if (parse->next && parse->command->out_desc == 0)
			dup2(parse->fd[1], STDOUT_FILENO);
		if (parse->previous && parse->command->in_desc == 0)
			dup2(parse->previous->fd[0], STDIN_FILENO);
		if (!managed_redirection(parse))
		{
			close(parse->fd[0]);
			close(parse->fd[1]);
			while (parse->previous)
				parse = parse->previous;
			free_env_list();
			free_parsed_cmd_managed_list(parse);
			exit(1);
		}
		if (parse->command->argv[0])
			choose_execution(parse);
	}
	if (parse->next)
		close(parse->fd[1]);
	if (parse->previous)
		close(parse->previous->fd[0]);
}

void	execution(t_parsed_cmd_managed_list *parse)
{
	int *fd;
	int							status;
	t_parsed_cmd_managed_list	*previous;
	t_parsed_cmd_managed_list	*pipe_parse;

	previous = parse;
	pipe_parse = parse;
	if (single_command(parse))
		return ;
	pipe_initialize(parse);
	while (pipe_parse)
	{
		fd = open_input_ouput_files(pipe_parse->for_redirection->redirections);
		if (fd[0] == -1 || fd[1] == -1)
			return ;
		pipe_parse->command->in_desc = fd[0];
		pipe_parse->command->out_desc = fd[1];
		pipe_parse = pipe_parse->next;

	}
	while (parse)
	{
		child_execution(parse);
		parse = parse->next;
		if (parse)
			previous = parse->previous;
	}
	while (previous)
	{
		waitpid(previous->pid, &status, 0);
		g_myenv.ret_exit = WEXITSTATUS(status);
		previous = previous->next;
	}
}
