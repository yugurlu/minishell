/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:37:42 by yugurlu           #+#    #+#             */
/*   Updated: 2023/03/10 18:20:26 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	help_getenv(int *i, int *k, char *temp)
{
	while (g_myenv.env[*i][*k] && g_myenv.env[*i][*k] != '=')
	{
		temp[*k] = g_myenv.env[*i][*k];
		(*k)++;
	}
	temp[*k] = '\0';
}

void	help(int *is_env, char *str, int *i, int *len)
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
	if (str[*i] == '$')
	{
		*is_env = 1;
		*i += 1;
	}
	else
		*is_env = 0;
	if (!str[*i] && (*new = ft_strdup("$")))
		return ;
	if (str[*i] == '?' && str[*i - 1] == '$'
		&& ((*new) = ft_itoa(g_myenv.ret_exit)) && (*i += 1))
		return ;
	help(is_env, str, i, len);
	*new = malloc(*len + 1);
	while (j < *len)
	{
		(*new)[j] = str[*i];
		j++;
		*i += 1;
	}
	(*new)[j] = '\0';
}
