/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsamli <bsamli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 10:03:45 by yugurlu           #+#    #+#             */
/*   Updated: 2023/05/03 18:12:51 by bsamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	get_path(t_prsd_mng_l *parse)
{
	int	line;

	line = find_line("PATH");
	if (line != -1)
		g_myenv.path = ft_split(g_myenv.env[line], ':');
	else
		g_myenv.path = NULL;
	if (!ft_strcmp(parse->command->argv[0], "exit"))
		parse->command->argv[0] = NULL;
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
				g_myenv.command_not_found = 0;
				return (path);
			}
			free(path);
			i++;
		}
	}
	g_myenv.command_not_found = 1;
	error_command(cmd, 1);
	return (NULL);
}
