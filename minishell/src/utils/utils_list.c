/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 19:04:30 by yugurlu           #+#    #+#             */
/*   Updated: 2023/03/26 19:05:08 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_parsed_cmd	*create_init_parsed_cmd(void)
{
	t_parsed_cmd	*parsed_cmd;

	parsed_cmd = (t_parsed_cmd *)malloc(sizeof(t_parsed_cmd));
	parsed_cmd->arguments = (t_string_list *)(NULL);
	parsed_cmd->redirections = (t_redirect_list *)(NULL);
	parsed_cmd->is_piped = 0;
	return (parsed_cmd);
}

void	manage_variable(t_string_list **start_token, t_string_list **tokens,
		t_parsed_cmd **parsed_cmd, t_parsed_cmd_list **parsed_cmd_list)
{
	*start_token = *tokens;
	*parsed_cmd_list = NULL;
	*parsed_cmd = create_init_parsed_cmd();
}
