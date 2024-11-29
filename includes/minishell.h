/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kepouliq <kepouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:41:46 by saberton          #+#    #+#             */
/*   Updated: 2024/11/29 17:13:57 by kepouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include "colors.h"
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef enum e_enum
{
	CMD,
	WORD,
	FLGS,
	APPEND,
	HEREDOC,
	DELIM,
	OPERATEUR,
	INFILE = '<',
	OUTFILE = '>',
	PIPE = '|',
	FICHIER
}					t_enum;

typedef struct s_env
{
	char			*type;
	char			equal;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_token
{
	t_enum			type;
	char			*value;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct s_data
{
	char			wich_quote_err;
	int				err_quote;
	char			*line;
	t_token			*token;
	char			**env;
	t_env			*cpy_env;
	t_env			*cpy_env2;
}					t_data;

//----------------- signal ---------------------
void				signal_handlers(void);

//----------------- env ------------------------
void				add_cpy_env(char *type, char *value, t_env **env,
						t_data *data);
void				get_env(char **env, t_data *data);
int					len_env(char **env);
t_env				*last_value(t_env *env);
void				get_env2(char **env, t_data *data);
void				add_cpy_env2(char *type, char *value, t_env **env,
						t_data *data);

//----------------- token ----------------------
int					is_word(char c);
int					is_quote(char c);
int					ft_isspace(char c);
int					is_operateur(char c);
int					is_pipe(char c);
int					find_operateur(char *line, int *i);
char				*ft_copy_word(char *line, int *i, t_data *data);
char				*ft_copy_pipe(int *i);
char				*ft_copy_operateur(int *i, int j);
void				tokenize(char *line, t_data *data);
void				add_token_pipe(t_token **tok, t_data *data, int *i);
void				add_token_operateur(char *line, t_token **tok, t_data *data,
						int *i);
void				add_token_word(char *line, t_token **tok, t_data *data,
						int *i);

//----------------- builtins ----------------------

void				handle_exit(t_data *data);
void				handle_env(t_data *data);
void				handle_echo(t_data *data);
void				handle_pwd(t_data *data);
void				handle_unset(t_data *data);
void				handle_export(t_data *data);

//----------------- parse ----------------------

void				parse(t_data *data);

//----------------- exit ----------------------

void				exit_prog(t_data *data, int code);
void				open_quote_exit(t_data *data);

#endif