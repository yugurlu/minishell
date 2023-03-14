/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 17:06:35 by yugurlu           #+#    #+#             */
/*   Updated: 2023/03/14 18:18:17 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

char	*check_dir(char *arg)
{
	char	*dir;

	if (arg == NULL || ft_strcmp(arg, "~") == 0)
		dir = get_env_value("$HOME");
	else if (ft_strcmp(arg, "-") == 0)
		dir = get_env_value("$OLDPWD");
	else
		dir = ft_strdup(arg);
	return (dir);
}

void	set_pwd_and_olpwd(char *oldpwd, char *dir)
{
	char	**new_env;

	if (ft_strcmp(dir, "."))
	{
		new_env = set_env("OLDPWD", oldpwd);
		free(oldpwd);
		oldpwd = getcwd(NULL, 0);
		free_split(g_myenv.env);
		init_env(new_env);
		free_split(new_env);
		new_env = set_env("PWD", oldpwd);
		free_split(g_myenv.env);
		init_env(new_env);
		free_split(new_env);
		free(oldpwd);
	}
	g_myenv.ret_exit = 0;
	free(dir);
}

int	check(char *dir, char **oldpwd)
{
	if (access(dir, F_OK) == -1) //file exists
	{
		printf("minishell: cd: %s: No such file or directory\n", dir);
		free(dir);
		return (1);
	}
	if (access(dir, R_OK) == -1) // read permission
	{
		printf("minishell: cd: %s: Permission denied\n", dir);
		g_myenv.ret_exit = 1;
		free(dir);
		return (1);
	}
	*oldpwd = getcwd(NULL, 0);
	if (chdir(dir) == -1) //is a directory?
	{
		printf("minishell: cd: %s: Not a directory\n", dir);
		g_myenv.ret_exit = 1;
		free(oldpwd);
		free(dir);
		return (1);
	}
	return (0);
}

int	cd(char *arg)
{
	char	*dir;
	char	*oldpwd;

	oldpwd = NULL;
	dir = check_dir(arg);
	if (check(dir, &oldpwd))
		return (1);
	set_pwd_and_olpwd(oldpwd, dir);
	return (0);
}
