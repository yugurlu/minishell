/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 13:27:42 by yugurlu           #+#    #+#             */
/*   Updated: 2023/03/26 10:07:02 by yugurlu          ###   ########.fr       */
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

void	close_files(t_parsed_cmd_managed_list *parse)
{
	if (parse->command->in_desc != 0)
		close(parse->command->in_desc);
	if (parse->command->out_desc != 0)
		close(parse->command->out_desc);
	if (parse->next)
		close(parse->fd[1]);
	if (parse->previous)
		close(parse->previous->fd[0]);
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
		exit(0);
	}
	close_files(parse);
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
		get_path();
		child_execution(parse);
		parse = parse->next;
		if (parse)
			previous = parse->previous;
		free_split(g_myenv.path);
	}
	while (previous)
	{
		waitpid(previous->pid, &status, 0);
		g_myenv.ret_exit = WEXITSTATUS(status);
		close(previous->fd[0]);
		close(previous->fd[1]);
		previous = previous->next;
	}
}
