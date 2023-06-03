/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:17:15 by yugurlu           #+#    #+#             */
/*   Updated: 2023/06/03 14:21:57 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	heredoc_signal(int sig)
{
	if (sig == SIGINT)
		g_myenv.heredoc_signal = 1;
}

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

void	ctrl_backs(int sig)
{
	(void)sig;
	g_myenv.ret_exit = 131;
	g_myenv.ctrl_signal = 1;
	if (sig == SIGQUIT)
	{
		if (rl_line_buffer && *rl_line_buffer)
		{
			ft_putstr_fd("Quit : 3\n", 2);
			printf("%d\n", g_myenv.ret_exit);
			if (g_myenv.t_pid == 1)
				exit(131);
		}
	}
}

void	ctrl_c(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	write(1, "\033[A", 3);
	g_myenv.ret_exit = 1;
}

void	signal_control(void)
{
	g_myenv.t_pid = 1;
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, ctrl_backs);
}
