/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 14:06:53 by yugurlu           #+#    #+#             */
/*   Updated: 2023/03/12 17:12:28 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

void	env(void)
{
	int	i;

	i = 0;
	while (g_myenv.env[i])
		printf("%s\n", g_myenv.env[i++]);
	g_myenv.ret_exit = 0;
}
