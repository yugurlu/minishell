/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:17:15 by yugurlu           #+#    #+#             */
/*   Updated: 2023/03/20 18:22:52 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ctrl_d(int signal) // düzelt
{
	(void)signal;
	printf("exit");
	exit(0);
}

void	ctrl_c(int signal)
{
	(void)signal;
	printf("\n");
}

void	signal_control(void)
{
	signal(SIGINT, ctrl_c);
	signal(SIGSEGV, ctrl_d);
	signal(SIGQUIT, SIG_IGN);
}
