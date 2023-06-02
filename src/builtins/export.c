/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 15:34:43 by yugurlu           #+#    #+#             */
/*   Updated: 2023/06/02 13:28:46 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_env_with_export(char **env)
{
	int		i;
	char	**split;

	i = -1;
	while (env[++i])
	{
		ft_putstr_fd("declare -x  ", 1);
		split = ft_split(env[i], '=');
		ft_putstr_fd(split[0], 1);
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(split[1], 1);
		ft_putstr_fd("\"\n", 1);
		free_split(split);
	}
}

int	valid_identifier(char *variable, char *input)
{
	int	i;

	i = 0;
	while (variable && variable[i])
	{
		if (variable[i] == '$' || variable[i] == '\0' || variable[i] == '?'
			|| variable[i] == '=' || variable[i] == '.' || variable[i] == ','
			|| variable[i] == '/' || variable[i] == '*' || variable[i] == '-'
			|| variable[i] == '+' || variable[i] == ':' || variable[i] == '%'
			|| variable[i] == '#' || variable[i] == '@' || variable[i] == ' '
			|| only_digit(variable))
			return (1);
		i++;
	}
	if (input[0] == '=')
		return (1);
	return (0);
}

char	**set_env(char *env_name, char *value)
{
	int		i;
	int		line;
	char	**new_env;

	i = -1;
	line = find_line(env_name);
	if (line != -1)
	{
		new_env = malloc(sizeof(char *) * (split_len(g_myenv.env) + 1));
		while (g_myenv.env[++i])
		{
			if (i == line)
				new_env[i] = ft_strjoin(join_but_no_free(env_name, "="), value);
			else
				new_env[i] = ft_strdup(g_myenv.env[i]);
		}
		new_env[i] = NULL;
		return (new_env);
	}
	new_env = malloc(sizeof(char *) * (split_len(g_myenv.env) + 2));
	while (g_myenv.env[++i])
		new_env[i] = ft_strdup(g_myenv.env[i]);
	new_env[i] = ft_strjoin(join_but_no_free(env_name, "="), value);
	new_env[i + 1] = NULL;
	return (new_env);
}

void	export_option(char **new_env, char **split, char **arr, int option)
{
	char	*temp;

	if (option == 1)
	{
		new_env = set_env(split[0], split[1]);
		free_split(g_myenv.env);
		g_myenv.env = new_env;
		return ;
	}
	if (option == 2)
	{
		temp = ft_strdup("");
		new_env = set_env(split[0], temp);
		free_split(g_myenv.env);
		g_myenv.env = new_env;
		free(temp);
		return ;
	}
	if (option == 0)
	{
		print_env_with_export(g_myenv.env);
		g_myenv.ret_exit = 0;
	}
	else if ((arr[1][0] == '=' && ft_strlen(arr[1]) == 1))
		error_export();
}

void	export(char **arr)
{
	int		i;
	char	**split;
	char	**new_env;

	i = 0;
	new_env = NULL;
	if (arr[i] && arr[i][0])
	{
		while (arr[++i] && arr[i][0])
		{
			split = ft_split(arr[i], '=');
			if (!valid_identifier(split[0], arr[i]))
			{
				if (split[0] && split[1])
					export_option(new_env, split, arr, 1);
				else if (ft_strchr(arr[1], '=') && arr[1][0] != '=')
					export_option(new_env, split, arr, 2);
			}
			else
				error_export();
			free_split(split);
		}
	}
	if (!arr[1])
		export_option(NULL, NULL, arr, 0);
}
