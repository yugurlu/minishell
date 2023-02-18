/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 20:05:27 by yugurlu           #+#    #+#             */
/*   Updated: 2023/02/18 17:27:09 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_d(int sig) // düzelt
{
	(void)sig;
	printf("exit\n");
	exit(1);
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

int	quotes(char *s)
{
	int		i;
	char	type;
	int		flag;

	if (!s)
		return (0);
	i = 0;
	flag = 0;
	while (s[i])
	{
		if ((s[i] == '\'' || s[i] == '\"') && !flag)
		{
			type = s[i];
			flag = 1;
		}
		else if (flag && s[i] == type)
			flag = 0;
		i++;
	}
	if (flag)
		printf("Unclosed quotes, please try again without it\n");
	return (flag);
}

int	empty(char *input)
{
	char	c;

	if (input[0] && (input[0] == '\''))
	{
		c = input[0];
		if (input[1] && c == input[1])
		{
			printf("bash: : command not found\n");
			return (1);
		}
	}
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	exit_condition(char *input)
{
	if (!input || ft_strcmp(input, "exit") == 0 || ft_strncmp(input, "\"exit\"",
			6) == 0 || ft_strncmp(input, "\'exit\'", 6) == 0
		|| (spaceparse(input, "exit")))
		return (1);
	return (0);
}

int	ispace(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	strisdigit(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

void	numeric(char *input, char **split)
{
	printf("exit\n");
	printf("bash: exit: %s: numeric argument required\n", split[0]);
	//free
	exit(255); // exit status out of range
}

int	ft_exit(t_data data, char *input)
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

int	main(void)
{
	t_data	data;
	char	*input;

	while (1)
	{
		signal_control();
		input = readline("prompt> ");
		add(input);
		if (input && (quotes(input) || empty(input)))
			continue ;
		else if (exit_condition(input))
			ft_exit(data, input);
	}
}
