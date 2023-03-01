/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:11:47 by yugurlu           #+#    #+#             */
/*   Updated: 2023/03/01 12:31:23 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	numeric(char *input, char **split)
{
	(void)input;
	printf("bash: exit: %s: numeric argument required\n", split[0]);
	//free
	exit(255); // exit status out of range
}

int	exit_condition(char *input)
{
	if (!input || ft_strcmp(input, "exit") == 0 || ft_strncmp(input, "\"exit\"",
			6) == 0 || ft_strncmp(input, "\'exit\'", 6) == 0
		|| (spaceparse(input, "exit")))
		return (1);
	return (0);
}

int	ft_exit(char *input)
{
	int		i;
	char	**split;

	//free
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
}
