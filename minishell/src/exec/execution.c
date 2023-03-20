/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 13:27:42 by yugurlu           #+#    #+#             */
/*   Updated: 2023/03/20 23:03:20 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void child_execution(t_parsed_cmd_managed_list *parse)
{
	parse->pid = fork();
	if(parse->pid == 0)
	{
		//FD MANAGED AND EXECV
	}
}


void execution(t_parsed_cmd_managed_list *parse)
{
	if (single_command(parse))
		return ;
	if (parse && parse->next)
	{
		while (parse && parse->next)
		{
			child_execution(parse);
		}

	}
}
