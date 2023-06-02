/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:24:52 by yugurlu           #+#    #+#             */
/*   Updated: 2023/06/02 17:21:33 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	free_string_list(t_string_list *tokens)
{
	t_string_list	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->string);
		free(tmp);
	}
	return (1);
}

void	free_redirect_list(t_redirect_list *redirections)
{
	t_redirect_list	*tmp;

	while (redirections)
	{
		tmp = redirections;
		redirections = redirections->next;
		free(tmp->file);
		free(tmp);
	}
}

void	free_parsed_cmd_list(t_prsd_cmd_l *parsed_cmd_list)
{
	t_prsd_cmd_l	*tmp;

	while (parsed_cmd_list)
	{
		tmp = parsed_cmd_list;
		parsed_cmd_list = parsed_cmd_list->next;
		free_string_list(tmp->command->arguments);
		free_redirect_list(tmp->command->redirections);
		free(tmp->command);
		free(tmp);
	}
}

void	free_parsed_cmd_managed_list(t_prsd_mng_l *parse)
{
	t_prsd_mng_l	*tmp;
	t_prsd_mng_l	*start;

	start = parse;
	while (start)
	{
		tmp = start;
		start = start->next;
		free_split(tmp->command->argv);
		free(tmp->command);
		free(tmp);
	}
}

void	free_env_list(void)
{
	free_split(g_myenv.env);
}
