/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 20:06:22 by yugurlu           #+#    #+#             */
/*   Updated: 2023/03/27 13:02:35 by yugurlu          ###   ########.fr       */
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

typedef enum s_direction
{
	INPUT_FILE,
	INPUT_NEXT_LINE,
	OUTPUT_FILE_CREATE,
	OUTPUT_FILE_APPEND,
	NO_REDIR
}										t_direction;

typedef struct s_string_list
{
	char								*string;
	struct s_string_list				*next;
}										t_string_list;

typedef struct s_myenv
{
	char								**env;
	char								**path;
	int									ret_exit;
	int									*is_exit;
	struct stat							*stat;
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

}										t_prsd_cmd_l;

typedef struct s_parsed_cmd_managed
{
	char								**argv;
	int									argc;
	int									in_desc;
	int									out_desc;
	int									is_piped;
}										t_parsed_cmd_managed;

typedef struct s_parsed_cmd_managed_list
{
	t_parsed_cmd_managed				*command;
	pid_t								pid;
	int									fd[2];
	struct s_parsed_cmd_managed_list	*next;
	struct s_parsed_cmd_managed_list	*previous;
}										t_prsd_mng_l;

void			env(void);
void			pwd(void);
int				only_token_len(int flag,
					t_direction type);
void			init_env(char **env);
int				escape_space(char *input);
char			*get_env_value(char *env);
int				cd(char *arg);
int				redirect_token_type(char *c);
int				is_pipe(t_string_list *tokens,
					t_parsed_cmd *parsed_cmd);
char			*rm_extern_quotes(char *input);
int				ft_strchr_i(const char *s, int c);
char			*search_env(char *value, char **env);
void			envv(char *str, int *is_env, int *i);
int				correct_syntax(t_string_list *tokens);
int				spaceparse(char *input, char *command);
void			is_envv(char *str, int *is_env, int *i);
int				*open_input_ouput_files(t_redirect_list *redirections);
void			get_path(void);
int				is_builtin(char *cmd);
char			*path_finder(char *cmd);
void			execution(t_prsd_mng_l *cmd);
int				single_command(t_prsd_mng_l *parse);
int				managed_redirection(t_prsd_mng_l *parse);
int				*open_input_ouput_files(t_redirect_list *redirections);
int				exec_builtin(t_prsd_mng_l *parse,
					char *cmd);
void			ft_exit(t_string_list *tokens);
int				exit_condition(char *input);
void			numeric(char *input, char **split);
int				quotes(char *s);
int				empty(char *input);
void			echo(char **arg);
int				cd(char *args);
void			unset(char *args);
void			echo(char **args);
void			export(char **arr);
int				find_line(char *str);
char			**set_env(char *env_name, char *value);
void			error_redirections(char *file,
					int err_type);
void			error_command(char *cmd, int err_type);
void			error_exit(char *string, int err_type);
void			error_cd(char *file, int err_type);
void			signal_control(void);
void			ctrl_d(char *line);
int				ispace(char *s);
int				is_quote(char *c);
int				my_free(char *str);
void			free_env_list(void);
int				strisdigit(char *s);
int				isnumeric(char *str);
int				no_quote_len(char *c);
int				split_len(char **arr);
int				dollar_counter(char *c);
int				is_there_quotes(char *c);
void			free_split(char **split);
int				ft_strcmp(char *s1, char *s2);
void			skip_dollar(char *str, int *i);
char			*ft_strcpy(char *dest, char *src);
void			envv(char *str, int *is_env, int *i);
void			help_getenv(int *i, int *k, char *temp);
void			help_getenv(int *i, int *k, char *temp);
char			*strncopy(char *dest, char *src, int n);
int				free_string_list(t_string_list *tokens);
void			help(char **new, char *str, int *i,
					int *len);
void			free_redirect_list(t_redirect_list *redirections);
void			free_parsed_cmd_list(t_prsd_cmd_l *parsed_cmd_list);
void			free_parsed_cmd_managed_list(t_prsd_mng_l *parse);
char			*remove_quotes(char *file, char *dest);
t_string_list	*extract_tokens(char *input);
t_parsed_cmd	*create_init_parsed_cmd(void);
t_string_list	*dollar_and_env(t_string_list *tokens);
t_prsd_mng_l	*parsing(char *input);
t_prsd_mng_l	*preprocess(t_prsd_cmd_l *command_line);
t_prsd_cmd_l	*create_parsed_cmd_list(t_string_list *tokens);
void			manage_variable(t_string_list **start_token,
					t_string_list **tokens,
					t_parsed_cmd **parsed_cmd,
					t_prsd_cmd_l **parsed_cmd_list);

#endif
