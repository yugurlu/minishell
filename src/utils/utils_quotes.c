/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusufugurlu <yusufugurlu@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:02:11 by yugurlu           #+#    #+#             */
/*   Updated: 2023/05/15 17:06:16 by yusufugurlu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	norm(int *i, int *j, int *in_quotes)
{
	*i = 0;
	*j = 0;
	*in_quotes = 0;
}

int	help_quotes(int *i, int *len, char *c, char head)
{
	if (c[*i] == head && c[*i + 1] == '|')
		return (1);
	if (c[*i] == head)
		*i += 1;
	while (c[*i] && c[*i] != head && c[*i] != ' ')
	{
		*i += 1;
		*len += 1;
	}
	if (c[*i] == ' ' || (c[*i] == head && c[*i + 1] == ' '))
		return (1);
	return (0);
}

int	help_quotes2(int *i, int *j, char *dest, char *c, char head)
{
	if (c[*i] == head && c[*i + 1] == '|')
		return (1);
	while (c[*i] && c[*i] != head && c[*i] != ' ')
	{
		dest[*j] = c[*i];
		*j += 1;
		*i += 1;
	}
	if (c[*i] == ' ' || (c[*i] == head && c[*i + 1] == ' '))
		return (1);
	return (0);
}

void	help_quotes3(int *i, char *input)
{
	if (input[*i])
		*i += 1;
}
