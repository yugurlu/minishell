/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:18:33 by yugurlu           #+#    #+#             */
/*   Updated: 2023/03/20 15:50:43 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_there_quotes(char *c)
{
	if (c[0] == '\'' || c[0] == '\"')
		return (1);
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

char	*remove_quotes(char *file, char *dest)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (file[i] && file[i] != '\'' && file[i] != '\"')
		dest[j++] = file[i++];
	dest[j] = '\0';
	return (dest);
}

int	quotes(char *s)
{
	int		i;
	char	type;
	int		flag;

	if (!s)
		return (0);
	i = 0;
	flag = 0;
	while (s[i])
	{
		if ((s[i] == '\'' || s[i] == '\"') && !flag)
		{
			type = s[i];
			flag = 1;
		}
		else if (flag && s[i] == type)
			flag = 0;
		i++;
	}
	if (flag)
		printf("Unclosed quotes, please try again without it\n");
	return (flag);
}

int	empty(char *input)
{
	char	c;

	if (input[0] && (input[0] == '\'' || input[0] == '\"'))
	{
		c = input[0];
		if (input[1] && c == input[1])
		{
			printf("bash: : command not found\n");
			return (1);
		}
	}
	return (0);
}