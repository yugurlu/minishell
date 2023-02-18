/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 20:06:22 by yugurlu           #+#    #+#             */
/*   Updated: 2023/02/18 17:06:11 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/stat.h>
# include "./libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>

typedef struct s_data
{
	char	*input;
	char	*command;
}	t_data;

char	**get_command(t_data data);
void free_split(char **split);
int spaceparse(char *input, char *command);

#endif
