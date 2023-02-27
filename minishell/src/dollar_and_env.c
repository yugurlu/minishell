/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_and_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:06:03 by yugurlu           #+#    #+#             */
/*   Updated: 2023/02/27 19:00:58 by yugurlu          ###   ########.fr       */
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
	int i;
	char *valuee;
	char **split;

	i = 0;
	while (env[i])
	{
		split = ft_split(env[i], '=');
		if(ft_strcmp(split[0], value) == 0)
		{
			free_split(split);
			break;
		}
		else
			i++;
		free_split(split);
	}
	if(env[i])
	{
		valuee = ft_strchr(env[i], '=');
		if(valuee + 1)
			return (valuee + 1);
		else
			return (NULL);
	}
	return (NULL);
}

char	*get_env_value(char *env)
{
	int i;
	char	*value;

	i = 0;
	if (ft_strlen(env) == 1)
		return (env);
	if (env[0] == '$')
		value = search_env(env + 1, g_myenv.env);
	else
	{
		while (env[i] != '$')
		{
			value[i] = env[i];
			i++;
		}
		value[i] = 0;
		value = ft_strjoin(value, search_env(env + i + 1, g_myenv.env));
	}
	return (value);
}

t_string_list	*dollar_and_env(t_string_list *tokens)
{
	int i;
	t_string_list	*start;
	t_string_list	*clear_token;

	t_string_list *prev = NULL;
	i = 0;
	while (tokens)
	{
		if(prev == NULL){
			clear_token = malloc(sizeof(t_string_list));
			prev = clear_token;
		}
		if (i == 0)
			start = clear_token;
		if (ft_strchr(tokens->string, '$'))
		{
			clear_token->string = ft_strdup(get_env_value(tokens->string));
			free(tokens->string);
		}
		else
		{
			clear_token->string = ft_strdup(tokens->string);
			free(tokens->string);
		}
		tokens = tokens->next;
		clear_token = clear_token->next;
		i++;
	}
	free(tokens);
	return (start);
}
