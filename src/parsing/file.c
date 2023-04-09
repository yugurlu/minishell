/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 12:25:20 by yugurlu           #+#    #+#             */
/*   Updated: 2023/03/26 08:49:45 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	output_file_create(t_redirect_list *redirections, int *fd)
{
	if (fd[1] != 0)
		close(fd[1]);
	fd[1] = open(redirections->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd[1] == -1)
		error_redirections(redirections->file, 1);
}

void	output_file_append(t_redirect_list *redirections, int *fd)
{
	if (fd[1] != 0)
		close(fd[1]);
	fd[1] = open(redirections->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd[1] == -1)
		error_redirections(redirections->file, 1);
}

void	input_file(t_redirect_list *redirections, int *fd)
{
	if (fd[0] != 0)
		close(fd[0]);
	fd[0] = open(redirections->file, O_RDONLY);
	if (fd[0] == -1)
		error_redirections(redirections->file, 1);
}

void	here_doc(t_redirect_list *redirections, int *fd)
{
	char	*line;
	int		fd_pipe[2];

	if (fd[0] != 0)
		close(fd[0]);
	pipe(fd_pipe);
	while (1)
	{
		line = readline("> ");
		if (ft_strcmp(line, redirections->file) == 0)
			break ;
		write(fd_pipe[1], line, ft_strlen(line));
		write(fd_pipe[1], "\n", 1);
		free(line);
	}
	close(fd_pipe[1]);
	fd[0] = fd_pipe[0];
}

int	*open_input_ouput_files(t_redirect_list *redirections)
{
	int	*fd;

	fd = malloc(sizeof(int) * 2);
	fd[0] = 0;
	fd[1] = 0;
	while (redirections)
	{
		if (redirections->direction == OUTPUT_FILE_CREATE)
			output_file_create(redirections, fd);
		if (redirections->direction == OUTPUT_FILE_APPEND)
			output_file_append(redirections, fd);
		if (redirections->direction == INPUT_FILE)
			input_file(redirections, fd);
		if (redirections->direction == INPUT_NEXT_LINE)
			here_doc(redirections, fd);
		redirections = redirections->next;
	}
	return (fd);
}
