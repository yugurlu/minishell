/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macos <macos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 19:04:30 by yugurlu           #+#    #+#             */
/*   Updated: 2023/05/23 15:36:05 by macos            ###   ########.fr       */
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
		t_parsed_cmd **parsed_cmd, t_prsd_cmd_l **parsed_cmd_list)
{
	while (ft_strlen((*tokens)->string) == 0)
		*tokens = (*tokens)->next;
	*start_token = *tokens;
	*parsed_cmd_list = NULL;
	*parsed_cmd = create_init_parsed_cmd();
}

void	llong_check(long number)
{
	if (number < LLONG_MIN)
		error_exit(NULL, 2);
	else if (number > LLONG_MAX)
		error_exit(NULL, 2);
	if (number > 255)
		number %= 256;
}
