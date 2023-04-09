/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:54:37 by yugurlu           #+#    #+#             */
/*   Updated: 2023/03/30 17:33:34 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	error_cd(char *file, int err_type)
{
	if (err_type == 1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	if (err_type == 2)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	if (err_type == 3)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": Not a directory\n", 2);
	}
	g_myenv.ret_exit = 1;
	free(file);
}

void	error_exit(char *string, int err_type)
{
	if (err_type == 1)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		g_myenv.ret_exit = 1;
	}
	if (err_type == 2)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(string, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(255);
	}
}

void	error_redirections(char *file, int err_type)
{
	if (err_type == 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
}

void	error_command(char *cmd, int err_type)
{
	if (err_type == 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		g_myenv.ret_exit = 127;
		free(cmd);
	}
}
