/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:37:42 by yugurlu           #+#    #+#             */
/*   Updated: 2023/06/03 12:17:16 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	help2(char **new, int *i)
{
	*new = ft_itoa(g_myenv.ret_exit);
	*i += 1;
}

void	help3(int *is_env, char *str, int *i, int *len)
{
	*len = 0;
	if (*is_env)
	{
		while (str[*i] != '$' && str[*i] != '\0' && str[*i] != '?'
			&& str[*i] != '=' && str[*i] != '.' && str[*i] != ','
			&& str[*i] != '/' && str[*i] != '*' && str[*i] != '-'
			&& str[*i] != '+' && str[*i] != ':' && str[*i] != '%'
			&& str[*i] != '#' && str[*i] != '@' && str[*i] != ' ')
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

void	help(char **new, char *str, int *i, int *len)
{
	int	j;
	int	is_env;

	j = 0;
	is_env = 0;
	is_envv(str, &is_env, i);
	if (!str[*i])
	{
		*new = ft_strdup("$");
		return ;
	}
	if (str[*i] == '?' && str[*i - 1] == '$')
	{
		help2(new, i);
		return ;
	}
	help3(&is_env, str, i, len);
	*new = malloc(*len + 1);
	while (j < *len)
	{
		(*new)[j] = str[*i];
		j++;
		*i += 1;
	}
	(*new)[j] = '\0';
}

int	dollar_true(char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (str[i] == '$')
			{
				if (str[i + 1] && str[i + 1] != ' ')
					return (1);
			}
			i++;
		}
	}
	return (0);
}
