/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:11:47 by yugurlu           #+#    #+#             */
/*   Updated: 2023/03/18 19:05:09 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

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
	if ((ft_strncmp(input, "exit", 4) == 0 || ft_strncmp(input, "\"exit\"",
				6) == 0 || ft_strncmp(input, "\'exit\'", 6) == 0
			|| spaceparse(input, "exit")) && inside_the_space(input))
		return (1);
	return (0);
}

int	last_exit_before_the_bridge(char **split)
{
	int		number;
	char	*clear;

	if (split[0][0] == '\'' || split[0][0] == '\"')
		clear = malloc(no_quote_len(split[0]));
	else
		clear = malloc(ft_strlen(split[0]));
	remove_quotes(split[0], clear);
	number = ft_atoi(clear);
	if (number > 255)
		number %= 256;
	//FREE ALL
	free_split(split);
	ft_putstr_fd("exit\n", 1);
	exit(number);
}

void	ft_exit(char *input)
{
	char	**split;

	if (input[0] == '\'' || input[0] == '\"')
		split = ft_split(input + 6, ' ');
	else
		split = ft_split(input + 4, ' ');
	if (split[0])
	{
		if (!isnumeric(split[0]))
			error_exit(split, 2);
		if (split_len(split) > 1)
		{
			error_exit(split, 1);
			return ;
		}
		last_exit_before_the_bridge(split);
	}
	else
	{
		ft_putstr_fd("exit\n", 1);
		exit(g_myenv.ret_exit);
	}
}
