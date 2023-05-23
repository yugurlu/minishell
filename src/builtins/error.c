/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusufugurlu <yusufugurlu@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:54:37 by yugurlu           #+#    #+#             */
/*   Updated: 2023/05/23 17:26:48 by yusufugurlu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	error_export(void)
{
	ft_putstr_fd("$: export: not a valid identifier\n", 2);
	g_myenv.ret_exit = 1;
}

void	error_cd(char *file, int err_type)
{
	if (err_type == 1)
	{
		ft_putstr_fd("$: cd: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	if (err_type == 2)
	{
		ft_putstr_fd("$: cd: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	if (err_type == 3)
	{
		ft_putstr_fd("$: cd: ", 2);
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
		ft_putstr_fd("$: exit: too many arguments\n", 2);
		g_myenv.ret_exit = 1;
	}
	if (err_type == 2)
	{
		ft_putstr_fd("$: exit: ", 2);
		ft_putstr_fd(string, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(255);
	}
}

void	error_redirections(char *file, int err_type)
{
	if (err_type == 1)
	{
		ft_putstr_fd("$: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_myenv.ret_exit = 1;
	}
}

void	error_command(char *cmd, int err_type)
{
	ft_putstr_fd("$: ", 2);
	ft_putstr_fd(cmd, 2);
	if (err_type == 1)
	{
		ft_putstr_fd(": command not found\n", 2);
		g_myenv.ret_exit = 127;
		free(cmd);
	}
	if (err_type == 2)
	{
		ft_putstr_fd(": is a directory\n", 2);
		g_myenv.ret_exit = 126;
	}
	if (err_type == 3)
	{
		ft_putstr_fd(": Permission denied\n", 2);
		g_myenv.ret_exit = 126;
	}
	if (err_type == 4)
	{
		ft_putstr_fd(": No such file or directory\n", 2);
		g_myenv.ret_exit = 127;
	}
}
