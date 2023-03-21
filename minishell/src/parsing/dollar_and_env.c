/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_and_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:06:03 by yugurlu           #+#    #+#             */
/*   Updated: 2023/03/21 12:11:15 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


char	*back_dollar(char *str)
{
	int		i;
	char	*back;

	i = 0;
	while (str[i] != '$')
		i++;
	back = malloc(i + 1);
	i = 0;
	while (str[i] != '$')
	{
		back[i] = str[i];
		i++;
	}
	back[i] = '\0';
	return (back);
}

void	init_env(char **env)
{
	int	i;

	i = 0;
	g_myenv.env = malloc(sizeof(char *) * (split_len(env) + 1));
	while (env[i])
	{
		g_myenv.env[i] = ft_strdup(env[i]);
		i++;
	}
	g_myenv.env[i] = NULL;
	g_myenv.path = ft_split(g_myenv.env[find_line("PATH")], ':');
}

char	*ft_getenv(char *str)
{
	int		i;
	int		j;
	int		k;
	char	*temp;

	i = 0;
	j = 0;
	k = 0;
	if (str[0] == '$' && !str[1])
		return ("$");
	while (g_myenv.env[i])
	{
		while (g_myenv.env[i][j] && g_myenv.env[i][j] != '=')
			j++;
		temp = malloc(j + 1);
		help_getenv(&i, &k, temp);
		if (!ft_strcmp(temp, str) && my_free(temp))
			return (g_myenv.env[i] + j + 1);
		free(temp);
		j = 0;
		k = 0;
		i++;
	}
	return (NULL);
}

char	*get_env_value(char *str)
{
	int		i;
	int		len;
	int		is_env;
	char	*join;
	char	*new_str;

	join = NULL;
	skip_dollar(str, &i);
	while (str[i])
	{
		help_func(&new_str, str, &i, &len, &is_env);
		if (is_env == 1)
		{
			if (ft_isdigit(new_str[0]))
				join = ft_strjoin(join, new_str);
			if (!ft_getenv(new_str))
				;
			else
				join = ft_strjoin(join, ft_getenv(new_str));
			free(new_str);
		}
		else
			join = ft_strjoin(join, new_str);
	}
	return (join);
}

t_string_list	*dollar_and_env(t_string_list *tokens)
{
	char			*env;
	char			*back;
	t_string_list	*start;

	back = NULL;
	start = tokens;
	while (tokens)
	{
		if (ft_strchr(tokens->string, '$') && ft_strlen(tokens->string) > 1)
		{
			if (tokens->string[0] != '$')
				back = back_dollar(tokens->string);
			env = get_env_value(tokens->string);
			free(tokens->string);
			if (!env)
				tokens->string = ft_strdup("");
			else
				tokens->string = ft_strjoin(back, env);
			free(env);
		}
		tokens = tokens->next;
	}
	return (start);
}
