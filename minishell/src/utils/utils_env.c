/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:37:42 by yugurlu           #+#    #+#             */
/*   Updated: 2023/03/26 19:26:32 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	help_getenv(int *i, int *k, char *temp)
{
	while (g_myenv.env[*i][*k] && g_myenv.env[*i][*k] != '=')
	{
		temp[*k] = g_myenv.env[*i][*k];
		(*k)++;
	}
	temp[*k] = '\0';
}

void is_envv(char *str, int *is_env, int *i)
{
	if(str[*i] == '$')
	{
		*i += 1;
		*is_env = 1;
	}
	else
		*is_env = 0;
}

void	help2(int *is_env, char *str, int *i, int *len)
{
	if (*is_env)
	{
		while (str[*i] != '$' && str[*i] != '\0' && str[*i] != '?')
		{
			*len += 1;
			*i += 1;
		}
	}
	else
	{
		while (str[*i] != '$' && str[*i] != '\0')
		{
			*len += 1;
			*i += 1;
		}
	}
	*i -= *len;
}

void	help_func(char **new, char *str, int *i, int *len, int *is_env)
{
	int	j;

	j = 0;
	*len = 0;
	is_envv(str, is_env, i);
	if (!str[*i] && (*new = ft_strdup("$")))
		return ;
	if (str[*i] == '?' && str[*i - 1] == '$'
		&& ((*new) = ft_itoa(g_myenv.ret_exit)) && (*i += 1))
		return ;
	help2(is_env, str, i, len);
	*new = malloc(*len + 1);
	while (j < *len)
	{
		(*new)[j] = str[*i];
		j++;
		*i += 1;
	}
	(*new)[j] = '\0';
}
