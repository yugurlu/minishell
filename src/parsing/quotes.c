/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusufugurlu <yusufugurlu@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:18:33 by yugurlu           #+#    #+#             */
/*   Updated: 2023/05/25 10:43:22 by yusufugurlu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	remove_quotes(char *str)
{
	int		i;
	int		j;
	char	*section;

	norm(&i, &j);
	while (str[i])
	{
		section = malloc(1000);
		if (str[i] == '\'' || str[i] == '\"')
		{
			i++;
			while (str[i] && g_myenv.head != str[i])
				section[j++] = str[i++];
		}
		else
			while (str[i] && str[i] != '\'' && str[i] != '"' && str[i] != ' '
				&& str[i] != '|')
				section[j++] = str[i++];
		section[j] = 0;
		g_myenv.quotes = ft_strjoin(g_myenv.quotes, section);
		if (my_free(section) && str[i] && (str[i] == ' ' || str[i] == '|'
				|| str[i + 1] == ' ' || str[i + 1] == '|'))
			break ;
		help_quotes(&i, &j, str);
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
