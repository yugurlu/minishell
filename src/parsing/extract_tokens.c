/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:30:32 by yugurlu           #+#    #+#             */
/*   Updated: 2023/06/02 17:19:12 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_string_list	*create_token(char *input, int token_l)
{
	char			*dest;
	t_string_list	*new_token;

	new_token = (t_string_list *)malloc(sizeof(t_string_list));
	if (is_there_quotes(new_token, input, token_l))
	{
		g_myenv.quotes = NULL;
		remove_quotes(input);
		new_token->string = ft_strdup(g_myenv.quotes);
		free(g_myenv.quotes);
		return (new_token);
	}
	new_token->quotes = 2;
	dest = malloc(token_l + 1);
	new_token->string = ft_strdup(strncopy(dest, input, token_l));
	free(dest);
	return (new_token);
}

int	token_len(char *c, int len, int flag)
{
	t_direction	type;

	while (c[len] && c[len] != ' ' && flag == -1)
	{
		type = redirect_type(&c[len]);
		if (type != NO_REDIR)
			flag = len;
		if (c[len + 1] == '|' || c[len] == '|')
		{
			if (c[len] == '|')
				return (len + 1);
			if (c[++len] == '|' && c[len + 1] != '\'' && c[len + 1] != '"')
				break ;
		}
		else if (c[len] == '\'' || c[len] == '"')
		{
			len += ft_strchr_i(&c[len + 1], c[len]) + 1;
			if (c[len + 1] == '|')
				return (len + 1);
		}
		len++;
	}
	if (flag != -1)
		len = only_token_len(flag, type);
	return (len);
}

t_string_list	*extract_tokens(char *input)
{
	int				token_l;
	t_string_list	*token;

	input += escape_space(input);
	if (!*input)
		return (NULL);
	token_l = token_len(input, 0, -1);
	token = create_token(input, token_l);
	token->next = extract_tokens(input + token_l);
	return (token);
}
