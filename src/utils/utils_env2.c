/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 12:23:05 by yugurlu           #+#    #+#             */
/*   Updated: 2023/03/27 12:26:55 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	envv(char *str, int *is_env, int *i)
{
	if (str[*i] == '$')
		*is_env = 1;
	else
		*is_env = 0;
}

void	help_getenv(int *i, int *k, char *temp)
{
	while (g_myenv.env[*i][*k] && g_myenv.env[*i][*k] != '=')
	{
		temp[*k] = g_myenv.env[*i][*k];
		(*k)++;
	}
	temp[*k] = '\0';
}

void	is_envv(char *str, int *is_env, int *i)
{
	if (str[*i] == '$')
	{
		*i += 1;
		*is_env = 1;
	}
	else
		*is_env = 0;
}
