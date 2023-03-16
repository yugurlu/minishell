/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:11:47 by yugurlu           #+#    #+#             */
/*   Updated: 2023/03/16 18:35:00 by yugurlu          ###   ########.fr       */
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

int isnumeric(char *str)
{
	int i;

	i = 0;
	if(str[0] == '\'' || str[0] == '\"')
		i++;
	if(str[1] == '\'' || str[1] == '\"')
		return(0);
	while(str[i] && (str[i] != '\'' && str[i] != '\"'))
	{
		if(!ft_isdigit(str[i]))
			return(0);
		i++;
	}
	return(1);

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

int	exit_condition(char *input)
{
	if ((ft_strncmp(input, "exit", 4) == 0 || ft_strncmp(input, "\"exit\"",
		6) == 0 || ft_strncmp(input, "\'exit\'", 6) == 0
		|| spaceparse(input, "exit") || search_exit(input))
		&& inside_the_space(input))
		return (1);
	return (0);
}

int	ft_exit(char *input)
{
	int		i;
	char	**split;

	printf("%s", input);
	getchar();
	//free8
	i = 0;
	if (input[0] == '\'' || input[0] == '\"')
		split = ft_split(input + 6, ' ');
	else
		split = ft_split(input + 4, ' ');
	if (split_len(split) > 1)
		error_exit(NULL, 1);
	if (isnumeric(split[0]))
	{
		error_exit(split[0], 2);
		g_myenv.ret_exit = 255;

	}
	printf("exit\n");
	exit(0);
	return (0);
}
