/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 14:06:53 by yugurlu           #+#    #+#             */
/*   Updated: 2023/03/30 11:28:11 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	env(void)
{
	int	i;

	i = 0;
	while (g_myenv.env[i])
		ft_putendl_fd(g_myenv.env[i++], 1);
	g_myenv.ret_exit = 0;
}
