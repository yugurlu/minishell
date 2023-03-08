/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:24:52 by yugurlu           #+#    #+#             */
/*   Updated: 2023/03/08 15:25:12 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int dollar_counter(char *c)
{
	int i;
	int counter;

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
