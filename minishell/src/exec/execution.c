/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 13:27:42 by yugurlu           #+#    #+#             */
/*   Updated: 2023/03/23 15:18:41 by yugurlu          ###   ########.fr       */
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
		parse->command->argv[0] = path_finder(parse->command->argv[0]);
		if (!parse->command->argv[0])
		{
			free_env_list();
			free_parsed_cmd_managed_list(parse);
			exit(127);
		}
		execve(parse->command->argv[0], parse->command->argv, g_myenv.env);
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
		if (parse->next)
			dup2(parse->fd[1], STDOUT_FILENO);
		if (parse->previous)
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
	if(parse->next)
		close(parse->fd[1]);
	if (parse->previous)
		close(parse->previous->fd[0]);
}

void	execution(t_parsed_cmd_managed_list *parse)
{
	int							status;
	t_parsed_cmd_managed_list	*previous;

	previous = parse;
	if (single_command(parse))
		return ;
	pipe_initialize(parse);
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
