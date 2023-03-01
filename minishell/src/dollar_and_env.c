/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_and_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:06:03 by yugurlu           #+#    #+#             */
/*   Updated: 2023/02/28 22:01:07 by yugurlu          ###   ########.fr       */
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
	int len;
	char	*value;

	len = 0;
	value = NULL;
	if (ft_strlen(env) == 1)
		return (env);
	if (env[0] == '$')
	{
		if(search_env(env + 1, g_myenv.env))
		{
			value = malloc(ft_strlen(search_env(env + 1, g_myenv.env)));
			printf("   %zu   ", ft_strlen(search_env(env + 1, g_myenv.env)));
			value = search_env(env + 1, g_myenv.env);
		}
			getchar();
	}
	else
	{
		while (env[len] != '$')
			len++;
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
	return (value);
}

/*t_string_list	*dollar_and_env(t_string_list *tokens)
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
}*/



t_string_list	*dollar_and_env(t_string_list *tokens)
{
	char *temp;
	t_string_list *start;

	start = tokens;
	while (tokens)
	{
		if (ft_strchr(tokens->string, '$'))
		{
			temp = ft_strdup(get_env_value(tokens->string));
			free(tokens->string);
			tokens->string = ft_strdup(temp);
			free(temp);
		}
		if(tokens->next)
			tokens = tokens->next;
		else
			break;
	}
	return (start);
}
