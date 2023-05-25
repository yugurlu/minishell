/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusufugurlu <yusufugurlu@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 20:47:58 by yugurlu           #+#    #+#             */
/*   Updated: 2023/05/25 10:36:34 by yusufugurlu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *lft_str, char *buff)
{
	int		i;
	int		j;
	char	*str;

	if (!lft_str)
	{
		lft_str = malloc(1);
		lft_str[0] = '\0';
	}
	if (!buff)
		return (0);
	str = malloc(sizeof(char) * ((ft_strlen(lft_str) + ft_strlen(buff)) + 1));
	if (!str)
		return (0);
	i = -1;
	while (lft_str[++i] != '\0')
		str[i] = lft_str[i];
	j = 0;
	while (buff[j] != '\0')
		str[i++] = buff[j++];
	str[i] = '\0';
	if (lft_str)
		free(lft_str);
	return (str);
}

char	*join_but_no_free(char *lft_str, char *buff)
{
	int		i;
	int		j;
	char	*str;

	if (!lft_str)
	{
		lft_str = malloc(1);
		lft_str[0] = '\0';
	}
	if (!buff)
		return (0);
	str = malloc(ft_strlen(lft_str) + ft_strlen(buff) + 1);
	if (!str)
		return (0);
	i = -1;
	while (lft_str[++i] != '\0')
		str[i] = lft_str[i];
	j = 0;
	while (buff[j] != '\0')
		str[i++] = buff[j++];
	str[i] = '\0';
	return (str);
}
