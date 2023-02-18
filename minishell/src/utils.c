/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:39:03 by yugurlu           #+#    #+#             */
/*   Updated: 2023/02/18 17:25:54 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	spaceparse(char *input, char *command)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (input[j] && command[j])
	{
		if (input[i] == command[j])
		{
			while (input[i] == command[j] && command[j])
			{
				j++;
				i++;
			}
			if (ft_strlen(command) == j)
				return (1);
			else
				return (0);
		}
		if (input[i] == ' ')
			i++;
		else
			return (0);
	}
	return (0);
}
