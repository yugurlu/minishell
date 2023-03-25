/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocess.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:36:34 by yugurlu           #+#    #+#             */
/*   Updated: 2023/03/25 12:26:04 by yugurlu          ###   ########.fr       */
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

t_parsed_cmd_managed_list	*append_new_cmd(t_parsed_cmd_managed_list **headle)
{
	t_parsed_cmd_managed_list	*new;
	t_parsed_cmd_managed_list	*temp;

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
