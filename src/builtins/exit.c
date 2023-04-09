/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:11:47 by yugurlu           #+#    #+#             */
/*   Updated: 2023/03/31 18:59:17 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	search_exit(char *input)
{
	int	i;

	i = 0;
	if (input[0] == '\'' || input[0] == '\"')
		i++;
	if (input[i] == 'e' && input[i + 1] == 'x' && input[i + 2] == 'i' && input[i
			+ 3] == 't')
		return (1);
	return (0);
}

int	inside_the_space(char *input)
{
	int	i;

	i = 0;
	if (input[i] == '\'' || input[i] == '\"')
		i++;
	else
		return (1);
	if (input[i] == ' ')
		return (0);
	while (input[i] && (input[i] != '\'' && input[i] != '\"'))
	{
		if (input[i] == ' ')
			return (0);
		i++;
	}
	return (1);
}

int	exit_condition(char *input)
{
	if ((ft_strcmp(input, "exit") == 0))
		return (1);
	return (0);
}

void	ft_exit(t_string_list *tokens)
{
	int	number;

	if (tokens)
	{
		if (!isnumeric(tokens->string))
			error_exit(tokens->string, 2);
		if (tokens->next)
		{
			error_exit(NULL, 1);
			return ;
		}
		number = ft_atoi(tokens->string);
		if (number > 255)
			number %= 256;
		ft_putstr_fd("exit\n", 1);
		exit(number);
	}
	else
	{
		ft_putstr_fd("exit\n", 1);
		exit(g_myenv.ret_exit);
	}
}
