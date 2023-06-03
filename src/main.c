/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 20:05:27 by yugurlu           #+#    #+#             */
/*   Updated: 2023/06/03 13:20:02 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add(char *input)
{
	if (ft_strlen(input))
		add_history(input);
}

void	init_env(char **env)
{
	int	i;

	i = 0;
	g_myenv.env = malloc(sizeof(char *) * (split_len(env) + 1));
	while (env[i])
	{
		g_myenv.env[i] = ft_strdup(env[i]);
		i++;
	}
	g_myenv.env[i] = NULL;
}

int	main(int ac, char **av, char **env)
{
	char			*input;
	t_prsd_mng_l	*parsed_cmd_managed_list;

	(void)av;
	if (ac == 1)
	{
		init_env(env);
		while (1)
		{
			signal_control();
			input = readline("\033[32m$\033[32m \033[0m");
			ctrl_d(input);
			add(input);
			if (input && (quotes(input) || empty(input)))
				;
			else
			{
				parsed_cmd_managed_list = parsing(input);
				if (parsed_cmd_managed_list && g_myenv.heredoc_signal == 0)
					execution(parsed_cmd_managed_list);
				free_parsed_cmd_managed_list(parsed_cmd_managed_list);
			}
			free(input);
		}
	}
}
