/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 13:20:06 by yugurlu           #+#    #+#             */
/*   Updated: 2023/03/12 13:49:33 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

void	pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("minishell : pwd :");
		g_myenv.ret_exit = 1;
		return ;
	}
	printf("%s\n", cwd);
	g_myenv.ret_exit = 0;
	free(cwd);
}
