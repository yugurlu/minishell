/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 21:51:21 by yugurlu           #+#    #+#             */
/*   Updated: 2023/03/28 13:20:39 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	splitlen(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			count++;
			while (s[i] != '\0' && s[i] != c)
				i++;
		}
	}
	return (count);
}

static char	*copy(char *array, const char *s, int i, int len)
{
	int	j;

	j = 0;
	while (len > 0)
	{
		array[j] = s[i - len];
		len--;
		j++;
	}
	array[j] = '\0';
	return (array);
}

static void	*spliit(char **str, char const *s, char c)
{
	int	i;
	int	indx;
	int	count;

	i = 0;
	indx = 0;
	count = 0;
	while (indx < splitlen(s, c))
	{
		while (s[i] != 0 && s[i] == c)
			i++;
		while (s[i] != 0 && s[i] != c)
		{
			i++;
			count++;
		}
		str[indx] = (char *)malloc(sizeof(char) * (count + 1));
		if (!str[indx])
			return (NULL);
		copy(str[indx], s, i, count);
		count = 0;
		indx++;
	}
	str[indx] = 0;
	return (str[indx]);
}

char	**ft_split(char const *s, char c)
{
	char	**str;

	if (s)
	{
		str = malloc((sizeof(char *) * (splitlen(s, c) + 1)));
		if (!str)
			return (NULL);
		spliit(str, s, c);
		return (str);
	}
	return (0);
}
