/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 11:44:59 by yugurlu           #+#    #+#             */
/*   Updated: 2023/03/20 17:21:19 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

int managed_redirection(t_parsed_cmd_managed_list *parse)
{
	if(parse->command->in_desc == -404 || parse->command->out_desc == -404)
		return (0);
	if(parse->command->in_desc != 0)
	{
		dup2(parse->command->in_desc, STDIN_FILENO);
	}
	if(parse->command->out_desc != 0)
	{
		dup2(parse->command->out_desc, STDOUT_FILENO);
	}
	return (1);
}

int control(t_parsed_cmd_managed_list *parse)
{
	if(!is_builtin(parse->command->argv[0]))
		return (1);
	if(managed_redirection(parse))
		return (1);
	return (0);
}

void	close_dup(int in, int out, int setting)
{
	if (setting == 1)
	{
		close(in);
		close(out);
	}
	if (setting == 2)
	{
		dup2(in, 0);
		close(in);
		dup2(out, 1);
		close(out);
	}
}

int exec_builtin(t_parsed_cmd_managed_list *parse, char *cmd)
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
		unset(parse->command->argv[1]);
	else if (ft_strcmp(cmd, "env") == 0)
		env();
	return (0);
}

int	single_command(t_parsed_cmd_managed_list *parse)
{
	int	in;
	int	out;

	in = dup(0);
	out = dup(1);
	if (parse && !parse->next)
	{
		if(control(parse))
		{
			exec_builtin(parse, parse->command->argv[0]);
			close_dup(in, out, 2);
			return (1);
		}
	}
	close_dup(in, out, 1);
	return (0);
}