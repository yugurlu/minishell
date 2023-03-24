/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 20:05:27 by yugurlu           #+#    #+#             */
/*   Updated: 2023/03/24 16:43:09 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add(char *input)
{
	if (ft_strlen(input))
		add_history(input);
}

int	main(int ac, char **av, char **env)
{
	char						*input;
	t_parsed_cmd_managed_list	*parsed_cmd_managed_list;

	(void)av;
	if (ac == 1)
	{
		init_env(env);
		while (1)
		{
			signal_control();
			input = readline("prompt> ");
			add(input);
			if (input && (quotes(input) || empty(input)))
				continue ;
			else
			{
				parsed_cmd_managed_list = parsing(input);
				execution(parsed_cmd_managed_list);
				free(input);
				free_parsed_cmd_managed_list(parsed_cmd_managed_list);
			}
		}
	}
}
