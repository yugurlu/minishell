/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:17:15 by yugurlu           #+#    #+#             */
/*   Updated: 2023/03/31 12:19:57 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ctrl_d(char *line)
{
	if (!line)
	{
		ft_putstr_fd("exit\n", 1);
		free(line);
		free_env_list();
		exit(0);
	}
}

void	ctrl_c(int sig)
{
	(void)sig;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	write(1, "\033[A", 3);
}

void	signal_control(void)
{
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}
