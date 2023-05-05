/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:18:33 by yugurlu           #+#    #+#             */
/*   Updated: 2023/05/05 14:43:38 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_there_quotes(char *c, int token_l)
{
	int	i;

	i = 0;
	while (c[i] && c[i] != ' ' && (token_l > i))
	{
		if (c[i] == '\'' || c[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

int	no_quote_len(char *c)
{
	int	i;
	int	len;
	int	in_quote;

	i = 0;
	len = 0;
	in_quote = 0;
	while (c[i])
	{
		if ((c[i] == '\'' || c[i] == '\"'))
		{
			if (in_quote == 0)
				in_quote = 1;
			else if (in_quote == 1)
				if (help_quotes(&i, &len, c))
					break ;
		}
		else
			len++;
		help_quotes3(&i, c);
	}
	return (len);
}

char	*remove_quotes(char *input, char *dest)
{
	int	i;
	int	j;
	int	in_quotes;

	fuck_norm(&i, &j, &in_quotes);
	while (input[i])
	{
		if ((input[i] != '\'' && input[i] != '\"'))
			dest[j++] = input[i++];
		else
		{
			if (in_quotes == 0)
				in_quotes = 1;
			else if (input[(i++) + 1] != ' ')
			{
				if (help_quotes2(&i, &j, dest, input))
					break ;
			}
			else
				break ;
			help_quotes3(&i, input);
		}
	}
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
		ft_putstr_fd("Unclosed quotes, please try again without it\n", 2);
	return (flag);
}

int	empty(char *input)
{
	char	c;

	if (input[0] && input[1] && !input[2] && (input[0] == '\''
			|| input[0] == '\"'))
	{
		c = input[0];
		if (input[1] && c == input[1])
		{
			ft_putstr_fd("bash: : command not found\n", 2);
			g_myenv.ret_exit = 127;
			return (1);
		}
	}
	return (0);
}
