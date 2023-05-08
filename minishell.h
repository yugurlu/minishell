/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 20:06:22 by yugurlu           #+#    #+#             */
/*   Updated: 2023/05/08 18:53:35 by yugurlu          ###   ########.fr       */
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
# include <sys/ioctl.h>
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
	int									quotes;
	struct s_string_list				*next;
}										t_string_list;

typedef struct s_myenv
{
	char								**env;
	char								**path;
	int									ret_exit;
	int									command_not_found;
	int									*is_exit;
	int									heredoc_signal;
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
int				cd(char *arg);
int				cd(char *args);
void			get_path(t_prsd_mng_l *parse);
int				ispace(char *s);
int				quotes(char *s);
void			echo(char **arg);
void			echo(char **args);
int				is_quote(char *c);
void			unset(char **args);
void			ctrl_d(char *line);
void			export(char **arr);
void			ctrl_d(char *line);
int				my_free(char *str);
int				empty(char *input);
void			free_env_list(void);
int				strisdigit(char *s);
void			init_env(char **env);
void			signal_control(void);
void			help_quotes3(int *i, char *input);
int				isnumeric(char *str);
int				find_line(char *str);
int				is_builtin(char *cmd);
int				no_quote_len(char *c);
int				split_len(char **arr);
t_prsd_mng_l	*parsing(char *input);
char			*path_finder(char *cmd);
int				dollar_counter(char *c);
int				only_token_len(int flag,
					t_direction type);
void			free_split(char **split);
int				escape_space(char *input);
char			*get_env_value(char *env);
int				exit_condition(t_string_list *tokens);
void			execution(t_prsd_mng_l *cmd);
t_string_list	*extract_tokens(char *input);
t_parsed_cmd	*create_init_parsed_cmd(void);
int				ft_strcmp(char *s1, char *s2);
int				is_pipe(t_string_list *tokens,
					t_parsed_cmd *parsed_cmd);
void			skip_dollar(char *str, int *i);
void			ft_exit(t_string_list *tokens);
void			error_redirections(char *file,
					int err_type);
char			*rm_extern_quotes(char *input);
int				exec_builtin(t_prsd_mng_l *parse,
					char *cmd);
int				ft_strchr_i(const char *s, int c);
void			help(char **new, char *str, int *i,
					int *len);
char			*ft_strcpy(char *dest, char *src);
void			error_cd(char *file, int err_type);
int				basic_redirect_token_type(char *c);
void			numeric(char *input, char **split);
void			all_close_file(t_prsd_mng_l *parse);
int				single_command(t_prsd_mng_l *parse);
char			*search_env(char *value, char **env);
void			envv(char *str, int *is_env, int *i);
int				is_there_quotes(char *c, int token_l);
int				correct_syntax(t_string_list *tokens);
int				help_quotes(int *i, int *len, char *c);
t_string_list	*dollar_and_env(t_string_list *tokens);
char			*remove_quotes(char *file, char *dest);
char			**set_env(char *env_name, char *value);
void			error_command(char *cmd, int err_type);
void			error_exit(char *string, int err_type);
void			is_envv(char *str, int *is_env, int *i);
t_prsd_mng_l	*preprocess(t_prsd_cmd_l *command_line);
void			help_getenv(int *i, int *k, char *temp);
char			*strncopy(char *dest, char *src, int n);
int				free_string_list(t_string_list *tokens);
int				managed_redirection(t_prsd_mng_l *parse);
void			fuck_norm(int *i, int *j, int *in_quotes);
t_prsd_cmd_l	*create_parsed_cmd_list(t_string_list *tokens);
void			free_redirect_list(t_redirect_list *redirections);
void			free_parsed_cmd_managed_list(t_prsd_mng_l *parse);
int				redirect_token_type(char *c, t_string_list *token);
void			free_parsed_cmd_list(t_prsd_cmd_l *parsed_cmd_list);
int				help_quotes2(int *i, int *j, char *dest, char *input);
int				*open_input_ouput_files(t_redirect_list *redirections);
void			manage_variable(t_string_list **start_token,
					t_string_list **tokens,
					t_parsed_cmd **parsed_cmd,
					t_prsd_cmd_l **parsed_cmd_list);
#endif
