/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusufugurlu <yusufugurlu@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:18:33 by yugurlu           #+#    #+#             */
/*   Updated: 2023/05/29 18:34:35 by yusufugurlu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	remove_quotes(char *s)
{
	int		i;
	int		j;
	char	*section;

	norm(&i, &j);
	while (s[i])
	{
		section = malloc(1000);
		if (s[i] == '\'' || s[i] == '\"')
		{
			i++;
			while (s[i] && g_myenv.head != s[i])
				section[j++] = s[i++];
		}
		else
			while (s[i] && s[i] != '\'' && s[i] != '"' && s[i] != ' '
				&& s[i] != '|' && redirect_type(&s[i]) == NO_REDIR)
				section[j++] = s[i++];
		section[j] = 0;
		g_myenv.quotes = ft_strjoin(g_myenv.quotes, section);
		if (my_free(section) && s[i] && (s[i] == ' ' || s[i] == '|' || s[i + 1]
				== ' ' || s[i + 1] == '|' || redirect_type(&s[i]) != 4))
			break ;
		help_quotes(&i, &j, s);
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
