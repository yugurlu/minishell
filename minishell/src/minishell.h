/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 20:06:22 by yugurlu           #+#    #+#             */
/*   Updated: 2023/02/28 17:01:35 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <unistd.h>

typedef struct s_string_list
{
	char								*string;
	struct s_string_list				*next;
}										t_string_list;

typedef enum
{
	PIPE,               // |
	INPUT_FILE,         // <
	INPUT_NEXT_LINE,    // <<
	OUTPUT_FILE_CREATE, // >
	OUTPUT_FILE_APPEND, // >>
	NO_REDIR            // no redirection
}										t_io_direction;

typedef struct s_myenv
{
	char								**env;
	int									ret_exit;
}										t_myenv;

t_myenv									g_myenv;

typedef struct s_redirect_list
{
	t_io_direction						direction;
	char								*source;
	struct s_redirect_list				*next;
}										redirect_list;

typedef struct s_parsed_cmd
{
	//char *name;
	int									is_piped;
	t_string_list						*arguments;
	redirect_list						*redirections;
}										t_parsed_cmd;

typedef struct s_parsed_cmd_managed
{
	char								*path;
	char								**argv;
	int									argc;
	int									in_desc;
	int									out_desc;
	int									is_piped;
}										t_parsed_cmd_managed;

typedef struct s_command_line
{
	t_parsed_cmd						*command;
	struct s_command_line				*next;

}										t_parsed_cmd_list;

typedef struct s_parsed_cmd_managed_list
{
	t_parsed_cmd_managed				*command;
	int									fd[2];
	char								**cmd;
	char								*env_path;
	pid_t								pid;
	struct s_parsed_cmd_managed_list	*next;
	struct s_parsed_cmd_managed_list	*previous;
}										t_parsed_cmd_managed_list;

//parsing
void									init_env(char **env);
t_parsed_cmd_managed_list				*parsing(char *input);
int										escape_space(char *input);
char									*get_env_value(char *env);
t_string_list							*extract_tokens(char *input);
int										redirect_token_type(char *c);
char									*rm_extern_quotes(char *input);
int										ft_strchr_i(const char *s, int c);
char									*search_env(char *value, char **env);
t_string_list							*dollar_and_env(t_string_list *tokens);
int										spaceparse(char *input, char *command);
int	only_token_len(int flag,
					t_io_direction type);

//exit
int										ft_exit(char *input);
int										exit_condition(char *input);
void									numeric(char *input, char **split);

//quotes
int										quotes(char *s);
int										empty(char *input);

//utils
int										ispace(char *s);
int										strisdigit(char *s);
void									free_split(char **split);
int										ft_strcmp(char *s1, char *s2);
char									*ft_strcpy(char *dest, char *src);
char									*strncopy(char *dest, char *src, int n);

#endif