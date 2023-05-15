/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusufugurlu <yusufugurlu@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:24:35 by yugurlu           #+#    #+#             */
/*   Updated: 2023/05/15 13:41:37 by yusufugurlu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	all_close_file(t_prsd_mng_l *parse)
{
	t_prsd_mng_l	*tmp;

	tmp = parse;
	while (tmp->previous)
		tmp = tmp->previous;
	while (tmp)
	{
		while (tmp->next)
		{
			close(tmp->fd[0]);
			close(tmp->fd[1]);
			if (tmp->command->in_desc != 0)
				close(tmp->command->in_desc);
			if (tmp->command->out_desc != 0)
				close(tmp->command->out_desc);
			tmp = tmp->next;
		}
		break ;
	}
}
