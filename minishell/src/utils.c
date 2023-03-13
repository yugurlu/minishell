/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:39:03 by yugurlu           #+#    #+#             */
/*   Updated: 2023/03/13 17:12:58 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ispace(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	strisdigit(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

int	spaceparse(char *input, char *command)
{
	size_t	i;
	size_t	j;

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
