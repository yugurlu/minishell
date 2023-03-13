/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 17:06:35 by yugurlu           #+#    #+#             */
/*   Updated: 2023/03/13 18:00:38 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

char	*check_dir(char *args)
{
	char	*dir;

	if (args == NULL || ft_strcmp(args, "~") == 0)
		dir = get_env_value("HOME");
	else if (ft_strcmp(args, "-") == 0)
		dir = get_env_value("OLDPWD");
	else
		dir = args;
	return (dir);
}

int	cd(char *args)
{
	char	*dir;
	static char *oldpwd;

	dir = check_dir(args);
	oldpwd = getcwd(NULL, 0);
	if (access(dir, F_OK) == -1)
	{
		printf("minishell: cd: %s: No such file or directory\n", dir);
		g_myenv.ret_exit = 1;
		return (1);
	}
	if (access(dir, R_OK) == -1)
	{
		printf("minishell: cd: %s: Permission denied\n", dir);
		g_myenv.ret_exit = 1;
		return (1);
	}
	if (chdir(dir) == -1)
	{
		printf("minishell: cd: %s: Not a directory\n", dir);
		g_myenv.ret_exit = 1;
		return (1);
	}
	set_env("OLDPWD", oldpwd);
	g_myenv.ret_exit = 0;
	return (0);
}
