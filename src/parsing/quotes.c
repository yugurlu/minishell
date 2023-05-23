/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusufugurlu <yusufugurlu@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:18:33 by yugurlu           #+#    #+#             */
/*   Updated: 2023/05/23 13:29:11 by yusufugurlu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	no_quote_len(char *c)
{
	int		i;
	int		len;
	char	head;

	i = -1;
	len = 0;
	while (c[++i])
	{
		if (c[i] == '\'' || c[i] == '\"')
		{
			head = c[i++];
			while (c[i] && head != c[i])
			{
				i++;
				len++;
			}
		}
		else
			len++;
		if (c[i + 1] && c[i + 1] == ' ')
			break ;
	}
	return (len);
}

void	remove_quotes(char *input)
{
	int		i;
	int		j;
	char	head;
	char	*section;

	norm(&i, &j);
	while (input[++i])
	{
		j = 0;
		section = malloc(1000);
		if (input[i] == '\'' || input[i] == '\"')
		{
			head = input[i++];
			while (input[i] && head != input[i])
				section[j++] = input[i++];
		}
		else
			while (input[i] != '\'' && input[i] != '\"')
				section[j++] = input[i++];
		section[j] = 0;
		g_myenv.quotes = ft_strjoin(g_myenv.quotes, section);
		free(section);
		if (input[i + 1] && input[i + 1] == ' ')
			break ;
	}
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
		ft_putstr_fd("Unclosed quotes, please try again without it\n", 2);
	return (flag);
}

int	empty(char *input)
{
	int		i;
	char	c;

	i = 0;
	if (input[0] && input[1] && (input[0] == '\'' || input[0] == '\"'))
	{
		c = input[0];
		while (input[i])
		{
			if (c != input[i])
				break ;
			i++;
			if (!input[i])
			{
				ft_putstr_fd("bash: : command not found\n", 2);
				g_myenv.ret_exit = 127;
				return (1);
			}
		}
	}
	return (0);
}
