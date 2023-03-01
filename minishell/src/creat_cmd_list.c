/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_cmd_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 15:04:53 by yugurlu           #+#    #+#             */
/*   Updated: 2023/03/01 17:31:29 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_pype(t_string_list *tokens)
{
	return (tokens->string[0] == '|');
}


t_parsed_cmd	*create_init_parsed_cmd(void)
{
	t_parsed_cmd	*parsed_cmd;

	parsed_cmd = (t_parsed_cmd *)malloc(sizeof(t_parsed_cmd));
	parsed_cmd->arguments = NULL;
	parsed_cmd->redirections = NULL;
	parsed_cmd->is_piped = 0;
	return (parsed_cmd);
}

void parse_fill_cmd(t_parsed_cmd *parsed_cmd, t_string_list *start_token, t_string_list *tokens)
{
	while (start_token)
	{
		if (is_redirect_token(start_token->string) != NO_REDIR)
		{

		}
	}
}


t_parsed_cmd_list	*create_parsed_cmd_list(t_string_list *tokens)
{
	t_parsed_cmd *parsed_cmd;
	t_string_list *start_token;
	t_parsed_cmd_list *parsed_cmd_list;

	if (!tokens)
		return (NULL);
	/*if (!correct_syntax(tokens))
		return (NULL);*/
	parsed_cmd_list = (NULL);
	start_token = tokens;
	parsed_cmd = create_init_parsed_cmd();
	while (tokens)
	{
		if(!is_pype(tokens->next))
		{
			parse_fill_cmd(parsed_cmd, start_token, tokens);
		}
		else
		{

		}
	}
}
