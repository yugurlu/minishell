/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusufugurlu <yusufugurlu@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 12:12:08 by yugurlu           #+#    #+#             */
/*   Updated: 2023/05/29 18:25:08 by yusufugurlu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	dollar_counter(char *c)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (c[i])
	{
		if (c[i] == '$')
			counter++;
		i++;
	}
	return (counter);
}

int	ft_strchr_i(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	if (c == '\0')
		return (i);
	return (-1);
}

int	only_token_len(int flag, t_direction type)
{
	int	token_l;
	int	redir_len;

	redir_len = 1;
	if (type == INPUT_NEXT_LINE || type == OUTPUT_FILE_APPEND)
		redir_len = 2;
	if (flag == 0)
		token_l = redir_len;
	else
		token_l = flag;
	return (token_l);
}

int	redirect_type(char *c)
{
	if (*c)
	{
		if (*c == '<' && *(c + 1) != '<')
			return (INPUT_FILE);
		if (*c == '>' && *(c + 1) != '>')
			return (OUTPUT_FILE_CREATE);
	}
	if (*c && *(c + 1))
	{
		if ((*c == '<') && *(c + 1) == '<')
			return (INPUT_NEXT_LINE);
		if ((*c == '>') && *(c + 1) == '>')
			return (OUTPUT_FILE_APPEND);
	}
	return (NO_REDIR);
}

int	redirect_token_type(char *c, t_string_list *token)
{
	if (*c && !*(c + 1))
	{
		if (*c == '<' && token->quotes == 2)
			return (INPUT_FILE);
		if (*c == '>' && token->quotes == 2)
			return (OUTPUT_FILE_CREATE);
	}
	if (*c && *(c + 1))
	{
		if ((*c == '<') && *(c + 1) == '<' && token->quotes == 2)
			return (INPUT_NEXT_LINE);
		if ((*c == '>') && *(c + 1) == '>' && token->quotes == 2)
			return (OUTPUT_FILE_APPEND);
	}
	return (NO_REDIR);
}
