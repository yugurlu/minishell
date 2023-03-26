/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 10:03:45 by yugurlu           #+#    #+#             */
/*   Updated: 2023/03/26 10:04:41 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	get_path(void)
{
	int	line;

	line = find_line("PATH");
	if (line != -1)
		g_myenv.path = ft_split(g_myenv.env[line], ':');
	else
		g_myenv.path = NULL;
}

char	*path_finder(char *cmd)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	if (g_myenv.path)
	{
		while (g_myenv.path[i])
		{
			path = join_but_no_free(g_myenv.path[i], "/");
			path = ft_strjoin(path, cmd);
			if (access(path, F_OK) == 0)
			{
				free(cmd);
				return (path);
			}
			free(path);
			i++;
		}
	}
	error_command(cmd, 1);
	return (NULL);
}
