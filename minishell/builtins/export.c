/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 15:34:43 by yugurlu           #+#    #+#             */
/*   Updated: 2023/03/12 17:13:48 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

char	**set_env(char *env)
{
	int		i;
	char	**new_env;

	i = 0;
	new_env = malloc(sizeof(char *) * (split_len(g_myenv.env) + 2));
	while (g_myenv.env[i])
	{
		new_env[i] = ft_strdup(g_myenv.env[i]);
		i++;
	}
	new_env[i] = ft_strdup(env);
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
		new_env = set_env(arr);
		free_split(g_myenv.env);
		g_myenv.env = new_env;
		free_split(split);
		g_myenv.ret_exit = 0;
		return ;
	}
	free_split(split);
	g_myenv.ret_exit = 0;
}
