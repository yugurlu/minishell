/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusufugurlu <yusufugurlu@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:24:35 by yugurlu           #+#    #+#             */
/*   Updated: 2023/05/16 14:33:52 by yusufugurlu      ###   ########.fr       */
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
			tmp = tmp->next;
		}
		break ;
	}
}
