/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 12:56:33 by yugurlu           #+#    #+#             */
/*   Updated: 2023/03/25 12:20:43 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_parsed_cmd_managed_list	*parsing(char *input)
{
	t_string_list				*tokens;
	t_parsed_cmd_list			*parsed_cmd_list;
	t_parsed_cmd_managed_list	*parsed_cmd_managed_list;

	parsed_cmd_managed_list = NULL;
	tokens = extract_tokens(input);
	if (tokens == NULL)
		return (NULL);
	dollar_and_env(tokens);
	if (!correct_syntax(tokens) && free_string_list(tokens))
		return (NULL);
	if (exit_condition(tokens->string))
	{
		ft_exit(tokens->next);
		free_string_list(tokens);
		return (NULL);
	}
	parsed_cmd_list = create_parsed_cmd_list(tokens);
	free_string_list(tokens);
	if (parsed_cmd_list == NULL)
		return (NULL);
	parsed_cmd_managed_list = preprocess(parsed_cmd_list);
	free_parsed_cmd_list(parsed_cmd_list);
	return (parsed_cmd_managed_list);
}
