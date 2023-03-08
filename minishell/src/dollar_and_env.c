/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_and_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:06:03 by yugurlu           #+#    #+#             */
/*   Updated: 2023/03/08 23:52:02 by yugurlu          ###   ########.fr       */
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

char	*ft_getenv(char *str)
{
	int		i;
	int		j;
	int		k;
	char	*temp;

	i = 0;
	j = 0;
	k = 0;
	while (g_myenv.env[i])
	{
		while (g_myenv.env[i][j] && g_myenv.env[i][j] != '=')
			j++;
		temp = malloc(sizeof(char) * (j + 1));
		while (g_myenv.env[i][k] && g_myenv.env[i][k] != '=')
		{
			temp[k] = g_myenv.env[i][k];
			k++;
		}
		temp[k] = '\0';
		if (!ft_strcmp(temp, str))
		{
			free(temp);
			return (g_myenv.env[i] + j + 1);
		}
		free(temp);
		j = 0;
		k = 0;
		i++;
	}
	return (NULL);
}

char *$value(char *str)
{
	int		i;
	int		j;
	int		k;
	char	*temp;
	char	*temp2;
	char	*result;

	i = 0;
	j = 0;
	k = 0;
	while (str[i] != '$')
		i++;
	temp2 = malloc(i + 1);
	i = 0;
	while (str[i] != '$')
	{
		temp2[i] = str[i];
		i++;
	}
	temp2[i] = '\0';
	i++;
	while (str[i] && str[i] != ' ' && str[i] != '$')
		i++;
	temp = malloc(sizeof(char) * (i + 1));
	while (str[j] != '$')
		j++;
	j++;
	while (str[j] && str[j] != ' ' && str[j] != '$')
	{
		temp[k] = str[j];
		j++;
		k++;
	}
	temp[k] = '\0';
	result = ft_strjoin(temp2, ft_getenv(temp));
	printf("%s\n", result);
	free(temp);
	free(temp2);
	return (result);
}

char	*get_env_value(char *str)
{
	int		i;
	int 	j;
	int 	k;
	char	*back;
	char	*result;
	char	*front;

	i = 0;
	j = 0;
	(void)result;
	if (str[i] != '$')
	{
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
	}
	k = i;
	while (dollar_counter(str + k) > 0)
	{
		i++;
		k++;
		while (str[i] && str[i] != '$')
			i++;
		front = malloc(i);
		i = k;
		while (str[i] != '$')
		{
			front[j++] = str[i++];
			k++;
		}
		front[j] = '\0';
		j = 0;
		printf("front: %s\n", front);
		printf("%d\n", k);
		getchar();
	}
	return (NULL);
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
			if (!temp)
			{
				temp = malloc(1);
				temp[0] = '\0';
			}
			else
				temp = ft_strdup(temp);
			free(tokens->string);
			tokens->string = ft_strdup(temp);
			free(temp);
		}
		tokens = tokens->next;
	}
	return (start);
}
