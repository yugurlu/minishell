/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusufugurlu <yusufugurlu@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:30:19 by yugurlu           #+#    #+#             */
/*   Updated: 2023/05/22 18:19:03 by yusufugurlu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_option(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-' || !str[1])
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	echo_option(char **arg)
{
	int	i;
	int	returnn;

	i = 1;
	returnn = 0;
	while (arg[i])
	{
		if (is_option(arg[i]))
			returnn++;
		else
			return (returnn);
		i++;
	}
	return (returnn);
}

void	echo(char **arg)
{
	int	i;
	int	option;

	i = 1;
	option = 0;
	if (arg)
	{
		if (echo_option(arg))
		{
			option = echo_option(arg);
			i = option + 1;
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
