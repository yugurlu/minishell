/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   correct_syntax.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 12:05:10 by yugurlu           #+#    #+#             */
/*   Updated: 2023/03/26 10:23:43 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_pipe(t_string_list *tokens)
{
	return (tokens->string[0] == '|');
}

int	end_pipe(t_string_list *tokens)
{
	int	i;

	i = 0;
	while (tokens->string[i])
		i++;
	i--;
	return (tokens->string[i] == '|');
}

int	more_then_1_pipe(t_string_list *tokens)
{
	while (tokens)
	{
		if (tokens->next)
		{
			if (is_pipe(tokens) && is_pipe(tokens->next))
				return (1);
		}
		else if (!tokens->next && end_pipe(tokens))
			return (1);
		tokens = tokens->next;
	}
	return (0);
}

int	redirection_control(t_string_list *tokens)
{
	if (!tokens->next)
		return (0);
	if (redirect_token_type(tokens->next->string) != NO_REDIR)
		return (0);
	return (1);
}

int	correct_syntax(t_string_list *tokens)
{
	if (is_pipe(tokens) || more_then_1_pipe(tokens))
	{
		ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
		return (0);
	}
	while (tokens)
	{
		if (redirect_token_type(tokens->string) != NO_REDIR)
		{
			if (!redirection_control(tokens))
			{
				ft_putstr_fd("syntax error near unexpected token `newline'\n",
								2);
				return (0);
			}
		}
		tokens = tokens->next;
	}
	return (1);
}
