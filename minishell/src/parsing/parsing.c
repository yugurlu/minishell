/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 12:56:33 by yugurlu           #+#    #+#             */
/*   Updated: 2023/03/24 13:18:25 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


void	print_parsing_struct(t_parsed_cmd_list *command_line)
{
	t_parsed_cmd	*cmd;
	t_redirect_list	*ptr_redir;
	t_string_list	*arglist;

	while (command_line != NULL)
	{
		cmd = command_line->command;
		if (cmd->arguments)
		{
			arglist = cmd->arguments;
			if (arglist != NULL)
				printf("executable command : %s\n", arglist->string);
			else
				printf(": NULL\n");
			printf("arguments: ");
			arglist = arglist->next;
			while (arglist != NULL)
			{
				printf("[%s] ", arglist->string);
				arglist = arglist->next;
			}
			printf("\n");
		}
		if (cmd->redirections != NULL)
		{
			ptr_redir = cmd->redirections;
			while (ptr_redir != NULL)
			{
				if (ptr_redir->direction == INPUT_FILE)
					printf("Redirection is [<] file = %s\n",
							ptr_redir->file);
				if (ptr_redir->direction == INPUT_NEXT_LINE)
					printf("Redirection is [<<] file = %s\n",
							ptr_redir->file);
				if (ptr_redir->direction == OUTPUT_FILE_CREATE)
					printf("Redirection is [>] file = %s\n",
							ptr_redir->file);
				if (ptr_redir->direction == OUTPUT_FILE_APPEND)
					printf("Redirection is [>>] file = %s\n",
							ptr_redir->file);
				ptr_redir = ptr_redir->next;
			}
		}
		if (cmd->is_piped)
			printf("Redirection type is PIPE\n");
		command_line = command_line->next;
	}
}

void print_parsed_cmd_managed_list(t_parsed_cmd_managed_list *list)
{
	int i;
	t_parsed_cmd_managed	*cmd;

	while (list)
	{
		i = 0;
		cmd = list->command;
		while (cmd->argc > i)
		{
			if(i == 0)
				printf("executable command : %s\n", cmd->argv[i]);
			else
				printf("arguments : [%s]\n", cmd->argv[i]);
			i++;
		}
		printf("input_fd : %d\n", cmd->in_desc);
		printf("output_fd : %d\n", cmd->out_desc);
		if(cmd->is_piped)
			printf("Redirection type is PIPE\n");
		if(list->next)
			printf("***********************************************\n");
		list = list->next;
	}
}

void	print_string_list(t_string_list *list)
{
	while (list)
	{
		printf("[@%p][%s]\n", list, list->string);
		list = list->next;
	}
}

t_parsed_cmd_managed_list	*parsing(char *input)
{
	t_string_list				*tokens;
	t_parsed_cmd_list			*parsed_cmd_list;
	t_parsed_cmd_managed_list	*parsed_cmd_managed_list;

	parsed_cmd_managed_list = NULL;
	tokens = extract_tokens(input);
	if (tokens == NULL)
		return (NULL);
	//print_string_list(tokens);
	dollar_and_env(tokens);
	if (!correct_syntax(tokens) && free_string_list(tokens))
		return (NULL);
	if(exit_condition(tokens->string))
	{
		getchar	();
		ft_exit(tokens->next);
		free_string_list(tokens);
		return (NULL);
	}
	parsed_cmd_list = create_parsed_cmd_list(tokens);
	free_string_list(tokens);
	if (parsed_cmd_list == NULL)
		return (NULL);
	//printf("\n");
	//print_parsing_struct(parsed_cmd_list);
	parsed_cmd_managed_list = preprocess(parsed_cmd_list);
	free_parsed_cmd_list(parsed_cmd_list);
	//print_parsed_cmd_managed_list(parsed_cmd_managed_list);
	return (parsed_cmd_managed_list);
}
