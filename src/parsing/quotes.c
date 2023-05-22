/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusufugurlu <yusufugurlu@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:18:33 by yugurlu           #+#    #+#             */
/*   Updated: 2023/05/22 19:29:14 by yusufugurlu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	no_quote_len(char *c)
{
	int		i;
	int		len;
	char	head;
	int		in_quote;

	i = -1;
	len = 0;
	in_quote = 0;
	while (c[++i])
	{
		if ((c[i] == '\'' || c[i] == '\"'))
		{
			if (in_quote == 0)
			{
				head = c[i];
				in_quote = 1;
			}
			else if (in_quote == 1)
				if (help_quotes(&i, &len, c, head))
					break ;
		}
		else
			len++;
	}
	return (len);
}

char	*remove_quotes(char *input)
{
	int		i;
	int		j;
	char	head;
	int		in_quotes;

	norm(&i, &j, &in_quotes);
	while (input[i])
	{
		if ((input[i] == '\'' || input[i] == '\"'))
		{
			if (in_quotes == 1 && head != input[i])
				g_myenv.quotes[j++] = input[i];
			else if (in_quotes == 0)
				head = input[i];
			else if (in_quotes == 1)
				if (help_quotes2(&i, &j, input, head))
					break ;
			in_quotes = 1;
			help_quotes3(&i, input);
		}
		else
			g_myenv.quotes[j++] = input[i++];
	}
	return (g_myenv.quotes);
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
