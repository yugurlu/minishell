/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 14:16:32 by yugurlu           #+#    #+#             */
/*   Updated: 2023/03/12 17:14:46 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

int	find_line(char **arr, char *str)
{
	int		i;
	char	**split;

	i = 0;
	while (arr[i])
	{
		split = ft_split(arr[i], '=');
		if (ft_strcmp(split[0], str) == 0)
		{
			free_split(split);
			return (i);
		}
		free_split(split);
		i++;
	}
	return (-1);
}

char	**remove_line(char **arr, int line)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	new_env = malloc(sizeof(char *) * (split_len(g_myenv.env) - 1));
	while (arr[i])
	{
		if (i != line)
		{
			new_env[j] = ft_strdup(arr[i]);
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	return (new_env);
}

void	unset(char *args)
{
	int		line;
	char	**new_env;

	line = find_line(g_myenv.env, args);
	if (line != -1)
	{
		new_env = remove_line(g_myenv.env, line);
		free_split(g_myenv.env);
		g_myenv.env = new_env;
		g_myenv.ret_exit = 0;
	}
	g_myenv.ret_exit = 0;
}
