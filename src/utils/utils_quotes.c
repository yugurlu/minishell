/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:02:11 by yugurlu           #+#    #+#             */
/*   Updated: 2023/06/02 12:48:45 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	norm(int *i, int *j)
{
	*i = 0;
	*j = 0;
}

void	help_quotes(int *i, int *j, char *input)
{
	if (input[*i] && (input[*i] != '"' || helper(input, *i)))
		*i += 1;
	*j = 0;
}

int	is_there_quotes(t_string_list *new_token, char *c, int token_l)
{
	int	i;

	i = 0;
	while (c[i] && c[i] != ' ' && (token_l > i))
	{
		if (c[i] == '\'' || c[i] == '"')
		{
			new_token->quotes = 0;
			if (c[i] == '\'')
				new_token->quotes = 1;
			g_myenv.head = c[i];
			return (1);
		}
		i++;
	}
	return (0);
}
