/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_and_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:06:03 by yugurlu           #+#    #+#             */
/*   Updated: 2023/03/01 14:36:22 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	g_myenv.env = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		g_myenv.env[i] = ft_strdup(env[i]);
		i++;
	}
	g_myenv.env[i] = NULL;
	return ;
}

char	*search_env(char *value, char **env)
{
	int		i;
	char	*valuee;
	char	**split;

	i = 0;
	while (env[i])
	{
		split = ft_split(env[i], '=');
		if (ft_strcmp(split[0], value) == 0)
		{
			free_split(split);
			break ;
		}
		else
			i++;
		free_split(split);
	}
	if (env[i])
	{
		valuee = ft_strchr(env[i], '=');
		if (valuee + 1)
			return (valuee + 1);
	}
	return (NULL);
}

char	*get_env_value(char *env)
{
	int		len;
	char	*value;

	len = 0;
	value = NULL;
	if (env[0] == '$')
	{
		if (search_env(env + 1, g_myenv.env))
		{
			value = malloc(ft_strlen(search_env(env + 1, g_myenv.env)));
			value = search_env(env + 1, g_myenv.env);
		}
	}
	else
	{
		while (env[len] != '$')
			len++;
		if (search_env(env + len + 1, g_myenv.env))
		{
			len += ft_strlen(search_env(env + len + 1, g_myenv.env));
			value = malloc(sizeof(char) * (len + 1));
			len = 0;
			while (env[len] != '$')
			{
				value[len] = env[len];
				len++;
			}
			ft_strcpy(value + len, search_env(env + len + 1, g_myenv.env));
		}
		else
		{
			value = malloc(sizeof(char) * (len + 1));
			len = 0;
			while (env[len] != '$')
			{
				value[len] = env[len];
				len++;
			}
			value[len] = '\0';
		}
	}
	return (value);
}

t_string_list	*dollar_and_env(t_string_list *tokens)
{
	char			*temp;
	t_string_list	*start;

	start = tokens;
	while (tokens)
	{
		if (ft_strchr(tokens->string, '$') && ft_strlen(tokens->string) > 1)
		{
			temp = get_env_value(tokens->string);
			if (temp == NULL)
			{
				temp = malloc(1);
				*temp = '\0';
			}
			else
				temp = strdup(temp);
			free(tokens->string);
			tokens->string = ft_strdup(temp);
			free(temp);
		}
		tokens = tokens->next;
	}
	return (start);
}
