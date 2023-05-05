/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 13:27:42 by yugurlu           #+#    #+#             */
/*   Updated: 2023/05/05 08:09:31 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	pipe_initialize(t_prsd_mng_l *parse)
{
	while (parse)
	{
		pipe(parse->fd);
		parse = parse->next;
	}
}

void	close_files(t_prsd_mng_l *parse)
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

void	choose_execution(t_prsd_mng_l *parse)
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
	if (g_myenv.command_not_found)
		exit(127);
	exit(0);
}

void	child_execution(t_prsd_mng_l *parse)
{
	parse->pid = fork();
	if (parse->pid == 0)
	{
		if (parse->next && parse->command->out_desc == 0)
			dup2(parse->fd[1], STDOUT_FILENO);
		if (parse->previous && parse->command->in_desc == 0)
			dup2(parse->previous->fd[0], STDIN_FILENO);
		managed_redirection(parse);
		if (parse->command->argv[0])
			choose_execution(parse);
		exit(0);
	}
	close_files(parse);
}

void	execution(t_prsd_mng_l *parse)
{
	int				status;
	t_prsd_mng_l	*previous;

	previous = parse;
	if (single_command(parse))
		return ;
	pipe_initialize(parse);
	while (parse)
	{
		get_path(parse);
		child_execution(parse);
		parse = parse->next;
		free_split(g_myenv.path);
	}
	while (previous->previous)
		previous = previous->previous;
	while (previous)
	{
		waitpid(previous->pid, &status, 0);
		g_myenv.ret_exit = WEXITSTATUS(status);
		close(previous->fd[0]);
		close(previous->fd[1]);
		previous = previous->next;
	}
}
