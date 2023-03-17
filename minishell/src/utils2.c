/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:24:40 by yugurlu           #+#    #+#             */
/*   Updated: 2023/03/17 12:54:23 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*strncopy(char *dest, char *src, int n)
{
	int	i;

	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	isnumeric(char *str)
{
	int i;

	i = 0;
	if (str[0] == '\'' || str[0] == '\"')
		i++;
	if (str[1] == '\'' || str[1] == '\"')
		return (0);
	while (str[i] && (str[i] != '\'' && str[i] != '\"'))
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
