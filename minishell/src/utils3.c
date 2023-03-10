/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:24:52 by yugurlu           #+#    #+#             */
/*   Updated: 2023/03/10 12:53:46 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_free(char *str)
{
	free(str);
	return (1);
}

void	skip_dollar(char *str, int *i)
{
	while (str[*i] != '$')
		*i += 1;
}

int	dollar_counter(char *c)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (c[i])
	{
		if (c[i] == '$')
			counter++;
		i++;
	}
	return (counter);
}
