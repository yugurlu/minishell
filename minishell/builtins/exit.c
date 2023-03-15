/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:11:47 by yugurlu           #+#    #+#             */
/*   Updated: 2023/03/15 15:07:23 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

void	numeric(char *input, char **split)
{
	(void)input;
	error_exit(split[0]);
	ft_putstr_fd("exit\n", 2);
	//free
	exit(255); // exit status out of range
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

int	exit_condition(char *input)
{
	if (!input || ft_strcmp(input, "exit") == 0 || ft_strncmp(input, "\"exit\"",
		6) == 0 || ft_strncmp(input, "\'exit\'", 6) == 0
		|| (spaceparse(input, "exit")) || search_exit(input))
		return (1);
	return (0);
}

int	ft_exit(char *input)
{
	int		i;
	char	**split;
	printf("%s", input);
	getchar();
	//free
	i = 0;
	if (input && !ispace(input + 4))
	{
		i = 0;
		split = ft_split(input + 4, ' ');
		while (split[i])
			i++;
		if (split[0] && !strisdigit(split[0]))
			numeric(input, split);
		if (i >= 2)
		{
			printf("bash: exit: too many arguments\n");
			return (1);
		}
		if (input)
			free(input);
		free_split(split);
	}
	printf("exit\n");
	exit(0);
	return (0);
}
