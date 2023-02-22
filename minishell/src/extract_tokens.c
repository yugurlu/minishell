/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:30:32 by yugurlu           #+#    #+#             */
/*   Updated: 2023/02/22 15:29:13 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

string_list	*create_token(char *input, int token_l)
{
	char			*dest;
	string_list	*new_token;

	new_token = (string_list *)malloc(sizeof(string_list));
	if (input[0] == '\'' || input[0] == '\"')
	{
		dest = malloc(sizeof(char) * (token_l - 2));
		new_token->string = ft_strdup(strncopy(dest, input + 1, token_l - 2));
		free(dest);
	}
	else
	{
		dest = malloc(sizeof(char) * token_l);
		new_token->string = ft_strdup(strncopy(dest, input, token_l));
		free(dest);
	}
	return (new_token);
}

int	token_len(char *input)
{
	int				flag;
	int				token_l;
	t_io_direction	type;

	flag = -1;
	token_l = 0;
	while (input[token_l] && input[token_l] != ' ' && flag == -1)
	{
		type = redirect_token_type(&input[token_l]);
		if (type != NO_REDIR)
			flag = token_l;
		else if (input[token_l] == '\'' || input[token_l] == '"')
			token_l += ft_strchr_i(&input[token_l + 1], input[token_l]) + 1;
		token_l++;
	}
	if (flag != -1)
		token_l = only_token_len(flag, type);
	return (token_l);
}

string_list	*extract_tokens(char *input)
{
	int			token_l;
	string_list	*token;

	input += escape_space(input);
	if (!*input)
		return (NULL);
	token_l = token_len(input);
	token = create_token(input, token_l);
	token->next = extract_tokens(input + token_l);
	return (token);
}
