/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:30:19 by yugurlu           #+#    #+#             */
/*   Updated: 2023/03/20 15:51:52 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


void	echo(char **arg)
{
	int	i;
	int	option;

	i = 1;
	option = 0;
	if (arg)
	{
		if (ft_strcmp(arg[1], "-n") == 0 && arg[2] == NULL)
			return ;
		if (ft_strcmp(arg[1], "-n") == 0)
		{
			option = 1;
			i++;
		}
		while (arg[i])
		{
			ft_putstr_fd(arg[i], 1);
			if (arg[i + 1] != NULL)
				ft_putchar_fd(' ', 1);
			i++;
		}
		if (!option)
			ft_putchar_fd('\n', 1);
	}
	g_myenv.ret_exit = 0;
}
