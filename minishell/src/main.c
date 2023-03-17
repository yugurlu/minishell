/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 20:05:27 by yugurlu           #+#    #+#             */
/*   Updated: 2023/03/17 12:03:24 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_d(int sig) // düzelt
{
	(void)sig;
	printf("exit\n");
	exit(0);
}

void	ctrl_c(int sig) // düzelt
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
}

void	signal_control(void)
{
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, ctrl_d);
}

void	add(char *input)
{
	if (ft_strlen(input))
		add_history(input);
}

int	word_count(char *input)
{
	int		i;
	int		count;
	char	temp;

	i = 0;
	count = 0;
	while (input[i] == ' ')
		i++;
	while (input[i])
	{
		if (input[i] == '\"' || input[i] == '\'')
		{
			temp = input[i++];
			while (input[i] && input[i] != temp)
				i++;
			count++;
		}
		else if ((input[i] != ' ' && (input[i + 1] == ' ' || input[i
						+ 1] == 0)))
			count++;
		i++;
	}
	return (count);
}

int	main(int ac, char **av, char **env)
{
	char						*input;
	t_parsed_cmd_managed_list	*parsed_cmd_managed_list;

	(void)av;
	(void)ac;
	init_env(env);
	while (1)
	{
		/*if (ac > 1)
			break ;*/
		signal_control();
		input = readline("prompt> ");
		add(input);
		if (input && (quotes(input) || empty(input)))
			continue ;
		else if (exit_condition(input))
			ft_exit(input);
		else
		{
			parsed_cmd_managed_list = parsing(input);
			(void)parsed_cmd_managed_list;
			free(input);
		}
	}
}
