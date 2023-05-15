/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusufugurlu <yusufugurlu@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 11:44:59 by yugurlu           #+#    #+#             */
/*   Updated: 2023/05/15 12:38:56 by yusufugurlu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	control(t_prsd_mng_l *parse)
{
	if (!is_builtin(parse->command->argv[0]))
		return (0);
	if (!managed_redirection(parse))
		return (0);
	return (1);
}

int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	return (0);
}

int	exec_builtin(t_prsd_mng_l *parse, char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		echo(parse->command->argv);
	else if (ft_strcmp(cmd, "cd") == 0)
		cd(parse->command->argv[1]);
	else if (ft_strcmp(cmd, "pwd") == 0)
		pwd();
	else if (ft_strcmp(cmd, "export") == 0)
		export(parse->command->argv);
	else if (ft_strcmp(cmd, "unset") == 0)
		unset(parse->command->argv);
	else if (ft_strcmp(cmd, "env") == 0)
		env();
	return (0);
}

int	managed_redirection(t_prsd_mng_l *parse)
{
	if (parse->command->in_desc == -1 || parse->command->out_desc == -1)
		return (0);
	if (parse->command->in_desc != 0)
		dup2(parse->command->in_desc, STDIN_FILENO);
	if (parse->command->out_desc != 0)
		dup2(parse->command->out_desc, STDOUT_FILENO);
	return (1);
}

int	single_command(t_prsd_mng_l *parse)
{
	int	in;
	int	out;

	in = dup(0);
	out = dup(1);
	if (parse && !parse->next)
	{
		if (control(parse))
		{
			exec_builtin(parse, parse->command->argv[0]);
			dup2(in, 0);
			dup2(out, 1);
			close(in);
			close(out);
			return (1);
		}
	}
	close(in);
	close(out);
	return (0);
}
