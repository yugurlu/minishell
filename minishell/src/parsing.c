/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 12:56:33 by yugurlu           #+#    #+#             */
/*   Updated: 2023/02/28 16:52:29 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_string_list(t_string_list *list)
{
	while (list)
	{
		printf("[@%p][%s]\n", list, list->string);
		list = list->next;
	}
}

t_parsed_cmd_managed_list	*parsing(char *input)
{
	t_string_list				*tokens;
	t_string_list				*clear_token;
	t_parsed_cmd_list			*parsed_cmd_list;
	t_parsed_cmd_managed_list	*parsed_cmd_managed_list;

	tokens = extract_tokens(input);
	if (tokens == NULL)
		return (NULL);
	dollar_and_env(tokens);
	print_string_list(tokens);
	printf("\n");
}
