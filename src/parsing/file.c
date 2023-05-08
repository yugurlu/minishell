/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 12:25:20 by yugurlu           #+#    #+#             */
/*   Updated: 2023/05/08 18:56:52 by yugurlu          ###   ########.fr       */
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

void	heredoc_signal(int sig)
{
	if (sig == SIGINT)
		g_myenv.heredoc_signal = 1;
}

void	heredoc(t_redirect_list *redirections, int *fd)
{
	int		pid;
	char	*line;
	int		fd_pipe[2];

	if (fd[0] != 0)
		close(fd[0]);
	pipe(fd_pipe);
	pid = fork();
	if (pid == 0)
	{
		while (1)
		{
			signal(SIGINT, heredoc_signal);
			if (g_myenv.heredoc_signal == 1)
				exit(1);
			line = readline("> ");
			if (ft_strcmp(line, redirections->file) == 0 || !line)
			{
				free(line);
				break ;
			}
			write(fd_pipe[1], line, ft_strlen(line));
			write(fd_pipe[1], "\n", 1);
			free(line);
		}
	}
	else
		waitpid(pid, &g_myenv.heredoc_signal, 0);
	close(fd_pipe[1]);
	fd[0] = fd_pipe[0];
}

int	*open_input_ouput_files(t_redirect_list *redirections)
{
	int	*fd;

	g_myenv.heredoc_signal = 0;
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
			heredoc(redirections, fd);
		redirections = redirections->next;
	}
	return (fd);
}
