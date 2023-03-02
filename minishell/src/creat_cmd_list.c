/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_cmd_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 15:04:53 by yugurlu           #+#    #+#             */
/*   Updated: 2023/03/02 15:25:12 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_pipe(t_string_list *tokens)
{
	return (tokens->string[0] == '|');
}


t_parsed_cmd	*create_init_parsed_cmd(void)
{
	t_parsed_cmd	*parsed_cmd;

	parsed_cmd = (t_parsed_cmd *)malloc(sizeof(t_parsed_cmd));
	parsed_cmd->arguments = NULL;
	parsed_cmd->redirections = NULL;
	parsed_cmd->is_piped = 0;
	return (parsed_cmd);
}

void new_pcl(t_parsed_cmd_list *put_pcl, t_parsed_cmd *parsed_cmd)
{
	t_parsed_cmd_list *temp;
	t_parsed_cmd_list *new_pcl;

	new_pcl = (t_parsed_cmd_list *)malloc(sizeof(t_parsed_cmd_list));
	new_pcl->command = parsed_cmd;
	new_pcl->next = NULL;
	if (!put_pcl)
	{
		put_pcl = new_pcl;
		return ;
	}
	temp = put_pcl;
	while (temp->next)
		temp = temp->next;
	temp->next = new_pcl;
}


void	new_arg(t_string_list *put_arg, char *arg)
{
	t_string_list *temp;
	t_string_list *neww_arg;

	neww_arg = (t_string_list *)malloc(sizeof(t_string_list));
	neww_arg->string = ft_strdup(arg);
	neww_arg->next = NULL;
	if (!put_arg)
	{
		put_arg = neww_arg;
		return ;
	}
	temp = put_arg;
	while (temp->next)
		temp = temp->next;
	temp->next = neww_arg;
}

void new_redirect(redirect_list *put_redir, char *source, int type)
{
	redirect_list *temp;
	redirect_list *new_redir;

	new_redir = (redirect_list *)malloc(sizeof(redirect_list));
	new_redir->source = ft_strdup(source);
	new_redir->direction = type;
	new_redir->next = NULL;
	if (!put_redir)
	{
		put_redir = new_redir;
		return ;
	}
	temp = put_redir;
	while (temp->next)
		temp = temp->next;
	temp->next = new_redir;
}


void parse_fill_cmd(t_parsed_cmd *parsed_cmd, t_string_list *start_token, t_string_list *check_token)
{
	while (start_token)
	{
		if (redirect_token_type(start_token->string) == NO_REDIR)
			new_arg(parsed_cmd->arguments, start_token->string);
		else
			new_redirect(parsed_cmd->redirections, start_token->next->string, redirect_token_type(start_token->string));
		if (start_token == check_token)
			break ;
		start_token = start_token->next;
	}
}


t_parsed_cmd_list	*create_parsed_cmd_list(t_string_list *tokens)
{
	t_parsed_cmd *parsed_cmd;
	t_string_list *start_token;
	t_parsed_cmd_list *parsed_cmd_list;

	if (!tokens)
		return (NULL);
	/*if (!correct_syntax(tokens))
		return (NULL);*/
	parsed_cmd_list = NULL;
	start_token = tokens;
	parsed_cmd = create_init_parsed_cmd();
	while (tokens)
	{
		if (tokens->next != NULL)
		{
			if (is_pipe(tokens->next))
			{
				parsed_cmd->is_piped = 1;
				parse_fill_cmd(parsed_cmd, start_token, tokens);
				new_pcl(parsed_cmd_list, parsed_cmd);
				tokens = tokens->next;
				if (tokens->next == NULL)
				{
					parsed_cmd = create_init_parsed_cmd();
					start_token = tokens->next;
				}
			}
		}
		else
		{
			printf("control\n");
			parse_fill_cmd(parsed_cmd, start_token, tokens);
			new_pcl(parsed_cmd_list, parsed_cmd);
			break ;
		}
		tokens = tokens->next;
	}
	return (parsed_cmd_list);
}
