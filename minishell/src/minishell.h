/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 20:06:22 by yugurlu           #+#    #+#             */
/*   Updated: 2023/02/22 15:50:14 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
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
	PIPE,               // |
	INPUT_FILE,         // <
	INPUT_NEXT_LINE,    // <<
	OUTPUT_FILE_CREATE, // >
	OUTPUT_FILE_APPEND, // >>
	NO_REDIR            // no redirection
}							t_io_direction;

typedef struct s_string_list
{
	char					*string;
	struct s_string_list	*next;
}							string_list;

//parsing
t_parsed_cmd_managed_list	*parsing(char *input);
int							escape_space(char *input);
string_list					*extract_tokens(char *input);
int							redirect_token_type(char *c);
char						*rm_extern_quotes(char *input);
int							ft_strchr_i(const char *s, int c);
int							spaceparse(char *input, char *command);
int	only_token_len(int flag,
					t_io_direction type);

//exit
int							ft_exit(char *input);
int							exit_condition(char *input);
void						numeric(char *input, char **split);

//quotes
int							quotes(char *s);
int							empty(char *input);

//utils
int							ispace(char *s);
int							strisdigit(char *s);
void						free_split(char **split);
int							ft_strcmp(char *s1, char *s2);
char						*strncopy(char *dest, char *src, int n);

#endif
