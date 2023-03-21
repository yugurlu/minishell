/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 13:27:42 by yugurlu           #+#    #+#             */
/*   Updated: 2023/03/21 17:33:06 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
		if(access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (path);
}

void	choose_execution(t_parsed_cmd_managed_list *parse)
{
	if (is_builtin(parse->command->argv[0]))
		exec_builtin(parse, parse->command->argv[0]);
	else
	{
		parse->command->argv[0] = path_finder(parse->command->argv[0]);
		printf("path: %s", parse->command->argv[0]);
		getchar();
		execve(parse->command->argv[0], parse->command->argv, g_myenv.env);
	}
	while (parse->previous)
		parse = parse->previous;
	//FREE ALL
	exit(0);
}

void	child_execution(t_parsed_cmd_managed_list *parse)
{
	parse->pid = fork();
	if (parse->pid == 0)
	{
		if (parse->next)
			dup2(parse->next->fd[1], STDOUT_FILENO);
		if (parse->previous)
			dup2(parse->previous->fd[0], STDIN_FILENO);
		if (managed_redirection(parse))
		{
			close(parse->fd[0]);
			close(parse->fd[1]);
			//FREE ALL
			exit(0);
		}
		close(parse->fd[0]);
		close(parse->fd[1]);
		choose_execution(parse);
	}
}

void	pipe_initialize(t_parsed_cmd_managed_list *parse)
{
	while (parse)
	{
		pipe(parse->fd);
		parse = parse->next;
	}
}

void	execution(t_parsed_cmd_managed_list *parse)
{
	printf("pipe initialize\n");
	if (single_command(parse))
		return ;
	pipe_initialize(parse);
	while (parse)
	{
		child_execution(parse);
		parse = parse->next;
	}
}
