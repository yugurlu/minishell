/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:02:11 by yugurlu           #+#    #+#             */
/*   Updated: 2023/05/04 23:02:50 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	fuck_norm(int *i, int *j, int *in_quotes)
{
	*i = 0;
	*j = 0;
	*in_quotes = 0;
}

int	help_quotes(int *i, int *len, char *c)
{
	if (c[*i] == '"' || c[*i] == '\'')
		*i += 1;
	while (c[*i] && c[*i] != '\'' && c[*i] != '\"' && c[*i] != ' ')
	{
		*i += 1;
		*len += 1;
	}
	if (c[*i] == ' ')
		return (1);
	return (0);
}

int	help_quotes2(int *i, int *j, char *dest, char *c)
{
	if (c[*i] == '"' || c[*i] == '\'')
		*i += 1;
	while (c[*i] && c[*i] != '\'' && c[*i] != '\"' && c[*i] != ' ')
	{
		dest[*j] = c[*i];
		*j += 1;
		*i += 1;
	}
	if (c[*i] == ' ')
		return (1);
	return (0);
}

void	help_quotes3(int *i, char *input)
{
	if (input[*i])
		*i += 1;
}
