/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocess.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:36:34 by yugurlu           #+#    #+#             */
/*   Updated: 2023/03/28 13:25:10 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**create_argv(t_string_list *arguments, int *argc)
{
	int				i;
	char			**argv;
	t_string_list	*temp;

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

t_prsd_mng_l	*append_new_cmd(t_prsd_mng_l **headle)
{
	t_prsd_mng_l	*new;
	t_prsd_mng_l	*temp;

	new = malloc(sizeof(t_prsd_mng_l));
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

t_prsd_mng_l	*preprocess(t_prsd_cmd_l *command_line)
{
	int				*fd;
	t_parsed_cmd	*cmd;
	t_prsd_mng_l	*ptr;
	t_prsd_mng_l	*prev;
	t_prsd_mng_l	*parsed_cmd_managed_list;

	ptr = NULL;
	parsed_cmd_managed_list = NULL;
	while (command_line)
	{
		cmd = command_line->command;
		prev = ptr;
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
