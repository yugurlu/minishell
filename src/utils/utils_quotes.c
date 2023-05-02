/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:02:11 by yugurlu           #+#    #+#             */
/*   Updated: 2023/05/02 14:00:34 by yugurlu          ###   ########.fr       */
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
	while (c[*i] && c[*i] != ' ' && c[*i] != '\'' && c[*i] != '\"')
	{
		*i += 1;
		*len += 1;
	}
	if (c[*i] == ' ')
		return (1);
	return (0);
}

int	help_quotes2(int *i, int *j, char *dest, char *input)
{
	while (input[*i] && input[*i] != ' ' && input[*i] != '\''
		&& input[*i] != '\"')
	{
		dest[*j] = input[*i];
		*j += 1;
		*i += 1;
	}
	if (input[*i] == ' ')
		return (1);
	return (0);
}
