/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:24:40 by yugurlu           #+#    #+#             */
/*   Updated: 2023/03/16 18:37:29 by yugurlu          ###   ########.fr       */
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

int	is_there_quotes(char *c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		if (c[i] == '\'' || c[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

int	no_quote_len(char *c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (c[i])
	{
		if (c[i] == '\'' || c[i] == '\"')
			i++;
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

char	*remove_quotes(char *source, char *dest)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (source[i])
	{
		if (source[i] != '\'' || source[i] != '\"')
		{
			dest[j] = source[i];
			j++;
		}
		i++;
	}
	dest[j] = '\0';
	return (dest);
}
