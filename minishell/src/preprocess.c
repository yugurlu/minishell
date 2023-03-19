/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocess.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:36:34 by yugurlu           #+#    #+#             */
/*   Updated: 2023/03/19 12:46:42 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int *open_input_ouput_files(t_redirect_list *redirections)
{
	int *fd;

	fd = malloc(sizeof(int) * 2);
	fd[0] = 0; // stdin
	fd[1] = 0; // stdout
	while (redirections)
	{
		if(redirections->direction == OUTPUT_FILE_CREATE)
		{
			if (fd[1] != 0)
				close(fd[1]);
			//sistem tarafından oluşturulan dosyaların izinleri 0644'dır.
			fd[1] = open(redirections->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd[1] == -1)
			{
				error_redirections(redirections->file, 1);
				fd[1] = -404;
			}
			return (fd);
		}
		if (redirections->direction == OUTPUT_FILE_APPEND)
		{
			if (fd[1] != 0)
				close(fd[1]);
			fd[1] = open(redirections->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd[1] == -1)
			{
				error_redirections(redirections->file, 1);
				fd[1] = -404;
			}
			return (fd);
		}
		if(redirections->direction == INPUT_FILE)
		{
			if (fd[0] != 0)
				close(fd[0]);
			fd[0] = open(redirections->file, O_RDONLY);
			if (fd[0] == -1)
			{
				error_redirections(redirections->file, 1);
				fd[0] = -404;
			}
			return (fd);
		}
		/*if(redirections->direction == INPUT_NEXT_LINE)
		{
			if (fd[0] != 0)
				close(fd[0]);
		}*/
		redirections = redirections->next;
	}
	return (fd);
}

char **create_argv(t_string_list *arguments, int *argc)
{
	int i;
	char **argv;
	t_string_list *temp;

	i = 0;
	*argc = 0;
	temp = arguments;
	while (temp)
	{
		*argc += 1;
		temp = temp->next;
	}
	argv = malloc(sizeof(char *) * (*argc + 1));
	temp = arguments;
	while (temp)
	{
		argv[i] = ft_strdup(temp->string);
		i++;
		temp = temp->next;
	}
	argv[i] = NULL;
	return (argv);
}

t_parsed_cmd_managed_list *append_new_cmd(t_parsed_cmd_managed_list **headle)
{
	t_parsed_cmd_managed_list *new;
	t_parsed_cmd_managed_list *temp;

	new = malloc(sizeof(t_parsed_cmd_managed_list));
	new->next = NULL;
	new->previous = NULL;
	new->command = NULL;
	if (*headle == NULL)
	{
		*headle = new;
		return (new);
	}
	temp = *headle;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	return (new);
}

t_parsed_cmd_managed_list	*preprocess(t_parsed_cmd_list *command_line)
{
	int							*fd;
	t_parsed_cmd				*cmd;
	t_parsed_cmd_managed_list	*ptr;
	t_parsed_cmd_managed_list	*prev;
	t_parsed_cmd_managed_list	*parsed_cmd_managed_list;

	ptr = NULL;
	parsed_cmd_managed_list = NULL;
	while (command_line)
	{
		cmd = command_line->command;
		prev = ptr;  // previous command
		ptr = append_new_cmd(&parsed_cmd_managed_list);
		ptr->previous = prev;
		ptr->command = malloc(sizeof(t_parsed_cmd_managed));
		fd = open_input_ouput_files(cmd->redirections);
		ptr->command->in_desc = fd[0];
		ptr->command->out_desc = fd[1];
		free(fd);
		ptr->command->argv = create_argv(cmd->arguments, &ptr->command->argc);
		ptr->command->is_piped = cmd->is_piped;
		command_line = command_line->next;
	}
	return (parsed_cmd_managed_list);
}
