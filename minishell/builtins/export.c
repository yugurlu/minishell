/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 15:34:43 by yugurlu           #+#    #+#             */
/*   Updated: 2023/03/13 15:59:05 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

char	**set_env(char *env_name, char *value)
{
	int		i;
	int		line;
	char	**new_env;

	i = -1;
	line = find_line(env_name);
	if (line != -1)
	{
		new_env = malloc(sizeof(char *) * (split_len(g_myenv.env)) + 1);
		while (g_myenv.env[++i])
		{
			if (i == line)
				new_env[i] = ft_strjoin(join_but_no_free(env_name, "="), value);
			else
				new_env[i] = ft_strdup(g_myenv.env[i]);
		}
		new_env[i] = NULL;
		return (new_env);
	}
	new_env = malloc(sizeof(char *) * (split_len(g_myenv.env) + 2));
	while (g_myenv.env[++i])
		new_env[i] = ft_strdup(g_myenv.env[i]);
	new_env[i] = ft_strjoin(join_but_no_free(env_name, "="), value);
	new_env[i + 1] = NULL;
	return (new_env);
}

void	export(char *arr)
{
	char	**split;
	char	**new_env;

	split = ft_split(arr, '=');
	if (split[1])
	{
		new_env = set_env(split[0], split[1]);
		free_split(g_myenv.env);
		g_myenv.env = new_env;
		free_split(split);
		g_myenv.ret_exit = 0;
		return ;
	}
	free_split(split);
	g_myenv.ret_exit = 0;
}
