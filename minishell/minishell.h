/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 20:06:22 by yugurlu           #+#    #+#             */
/*   Updated: 2023/03/20 18:18:41 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <unistd.h>

typedef enum
{
	INPUT_FILE,         // <
	INPUT_NEXT_LINE,    // <<
	OUTPUT_FILE_CREATE, // >
	OUTPUT_FILE_APPEND, // >>
	NO_REDIR            // no redirection
}										t_direction;

typedef struct s_string_list
{
	char								*string;
	struct s_string_list				*next;
}										t_string_list;

typedef struct s_myenv
{
	char								**env;
	int									ret_exit;
	int									*is_exit;
}										t_myenv;

t_myenv									g_myenv;

typedef struct s_redirect_list
{
	t_direction							direction;
	char								*file;
	struct s_redirect_list				*next;
}										t_redirect_list;

typedef struct s_parsed_cmd
{
	int									is_piped;
	t_string_list						*arguments;
	t_redirect_list						*redirections;
}										t_parsed_cmd;

typedef struct s_command_line
{
	t_parsed_cmd						*command;
	struct s_command_line				*next;

}										t_parsed_cmd_list;

typedef struct s_parsed_cmd_managed
{
	char								*path;
	char								**argv;
	int									argc;
	int in_desc;  //input descriptor
	int out_desc; //output descriptor
	int									is_piped;
}										t_parsed_cmd_managed;

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
int	only_token_len(int flag,
					t_direction type);
void									init_env(char **env);
t_parsed_cmd_managed_list				*parsing(char *input);
int										escape_space(char *input);
char									*get_env_value(char *env);
t_string_list							*extract_tokens(char *input);
int										redirect_token_type(char *c);
int										is_pipe(t_string_list *tokens);
char									*rm_extern_quotes(char *input);
int										ft_strchr_i(const char *s, int c);
char									*search_env(char *value, char **env);
int										correct_syntax(t_string_list *tokens);
t_string_list							*dollar_and_env(t_string_list *tokens);
int										spaceparse(char *input, char *command);
t_parsed_cmd_managed_list				*preprocess(t_parsed_cmd_list *command_line);
t_parsed_cmd_list						*create_parsed_cmd_list(t_string_list *tokens);

//execution
void									execution(t_parsed_cmd_managed_list *cmd);
int										single_command(t_parsed_cmd_managed_list *cmd);

//exit
void									ft_exit(char *input);
int										exit_condition(char *input);
void									numeric(char *input, char **split);

//quotes
int										quotes(char *s);
int										empty(char *input);

//builtins
void									env(void);
void									pwd(void);
int										cd(char *arg);
void									echo(char **arg);
int										cd(char *args);
void									unset(char *args);
void									echo(char **args);
void									export(char **arr);
int										find_line(char *str);
char									**set_env(char *env_name, char *value);

//error
void									error_exit(char **split, int err_type);
void									error_cd(char *file, int err_type);
void	error_redirections(char *file,
						int err_type);

//signal
void									signal_control(void);

//utils
int										ispace(char *s);
int										is_quote(char *c);
int										my_free(char *str);
int										strisdigit(char *s);
int										isnumeric(char *str);
int										no_quote_len(char *c);
int										split_len(char **arr);
int										dollar_counter(char *c);
int										is_there_quotes(char *c);
void									free_split(char **split);
int										ft_strcmp(char *s1, char *s2);
void									skip_dollar(char *str, int *i);
char									*ft_strcpy(char *dest, char *src);
void									help_getenv(int *i, int *k, char *temp);
char									*strncopy(char *dest, char *src, int n);
void									help_func(char **new, char *str, int *i,
											int *len, int *is_env);
char	*remove_quotes(char *file,
					char *dest);

#endif
