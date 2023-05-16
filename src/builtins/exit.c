/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusufugurlu <yusufugurlu@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:11:47 by yugurlu           #+#    #+#             */
/*   Updated: 2023/05/16 16:48:44 by yusufugurlu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	exit_pipe(t_prsd_mng_l *parsed_cmd_managed_list)
{
	int	i;

	while (parsed_cmd_managed_list)
	{
		i = 0;
		while (parsed_cmd_managed_list->command->argv[0][i])
		{
			if (parsed_cmd_managed_list->command->argv[0][i] == '|')
				return (1);
			i++;
		}
		parsed_cmd_managed_list = parsed_cmd_managed_list->next;
	}
	return (0);
}

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

int	exit_condition(t_prsd_mng_l *parsed_cmd_managed_list)
{
	if ((ft_strcmp(parsed_cmd_managed_list->command->argv[0], "exit") == 0)
		&& !exit_pipe(parsed_cmd_managed_list))
		return (1);
	return (0);
}

long	custom_strtol(const char *str)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	if (str[0] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[0] == '+')
	{
		i++;
	}
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
		{
			break ;
		}
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

void	ft_exit(t_prsd_mng_l *parsed_cmd_managed_list)
{
	long	number;

	if (parsed_cmd_managed_list->command->argv[1])
	{
		if (!isnumeric(parsed_cmd_managed_list->command->argv[1]))
			error_exit(parsed_cmd_managed_list->command->argv[1], 2);
		if (parsed_cmd_managed_list->command->argv[2])
		{
			error_exit(NULL, 1);
			return ;
		}
		number = ft_atoi(parsed_cmd_managed_list->command->argv[1]);
		if (number < LLONG_MIN)
			error_exit(NULL, 2);
		else if (number > LLONG_MAX)
			error_exit(NULL, 2);
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
