/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kepouliq <kepouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:41:46 by saberton          #+#    #+#             */
/*   Updated: 2024/12/10 17:28:31 by kepouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include "colors.h"
# include "define.h"
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
	FICHIER,
	BUILD,
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

typedef struct s_pipe
{
	int				nb_pipe;
	int				i;
	int				**fds;
	pid_t			*pid;
	struct s_data	*data;
}					t_pipe;

typedef struct s_data
{
	int				exit_code;
	int				nb_pipe;
	int				err_quote;
	int				err_export;
	int				infile;
	int				outfile;
	char			wich_quote_err;
	char			*line;
	char			**env;
	t_token			*token;
	t_env			*cpy_env;
	t_env			*cpy_env2;
	t_pipe			*pipe;
}					t_data;

//================== builtins =====================================//

//----------------- cd.c ------------------------
void				handle_cd(t_data *data, int fd_out);

//----------------- cd_utils.c ------------------------
void				change_old_env_pwd(t_data *data, char *path);
void				change_env_pwd(t_data *data);
char				*get_actual_env_path(t_data *data);
char				*get_home_env(t_data *data);

//----------------- echo.c ------------------------
void				handle_echo(t_token *tok, int fd_out);

//----------------- env.c ------------------------
void				handle_env(t_data *data, t_token *tok, int fd_out);

//----------------- exit.c ------------------------
void				handle_exit(t_data *data, t_token *tok, int fd_out);

//----------------- export.c ------------------------
int					find_if_env_exist(t_env *env, char *value);
void				handle_export(t_data *data, t_token *tok, int fd_out);

//----------------- get_env.c ------------------------
void				get_env(char **env, t_data *data);
void				add_cpy_env(char *type, char *value, t_env **env,
						t_data *data);
int					len_env(char **env);
t_env				*last_value(t_env *env);

//----------------- get_export_env.c.c ----------------------
void				add_cpy_env2(char *type, char *value, t_env **env,
						t_data *data);
void				get_env2(char **env, t_data *data);

//----------------- pwd.c ----------------------
void				handle_pwd(int fd_out);
char				*get_pwd(char **env);

//----------------- syntaxe_export.c ----------------------
int					check_syntax_export(char *value, t_data *data);
int					find_if_env_exist(t_env *env, char *value);
void				no_equal_in_export(t_data *data, char *value);
void				modif_export_node(t_data *data, char *value, int exist);
void				modif_export(t_data *data, char *value);
t_env				*sort_list(t_env *cpy, int (*cmp)(const char *,
							const char *));

//----------------- unset.c ----------------------
void				handle_unset(t_data *data, t_token *tok);

//================== parse =====================================//

//----------------- syntaxe.c ----------------------
int					good_syntaxe(t_data *data);

//----------------- parse.c ----------------------
void				parse(t_data *data);
void				clean_line(char *line, t_data *data);
int					is_builtins(t_token *token);
int					handle_builtins(t_data *data, t_token *tok, int fd_out);

//================== exec =====================================//

//----------------- exec_pipes.c ----------------------
void				ft_pipes(t_data *data);

//----------------- exec_utils.c ----------------------
int					pipe_in_line(t_data *data);
char				**recup_cmd(t_data *data, t_token *tok);
t_enum				wich_type_exec(t_data *data);
t_token				*recup_tok_after_pipe(t_token *tmp);

//----------------- exec.c ----------------------
void				exec_choice(t_data *data, t_token *tok);
void				wich_exec(t_data *data);

//================== token =====================================//

//----------------- add_token.c ----------------------
void				add_token_word(char *line, t_token **tok, t_data *data,
						int *i);
void				add_token_pipe(t_token **tok, t_data *data, int *i);
void				add_token_operateur(char *line, t_token **tok, t_data *data,
						int *i);
t_token				*last_token(t_token *tok);

//----------------- check_token_type.c ----------------------
int					is_quote(char c);
int					is_pipe(char c);
int					is_operateur(char c);
int					ft_isspace(char c);
int					is_word(char c);

//----------------- get_path.c ----------------------
char				**recup_path(t_env *env);
char				*valid_cmd(t_data *data, char *cmd);

//----------------- token_copy_word.c ----------------------
void				open_quote_exit(t_data *data);
int					len_in_quote(char *line, int *j, char quote);
int					word_size(char *line, int *i);
int					handle_quote(char *line, char *dup, int *i, int *j);
char				*ft_copy_word(char *line, int *i, t_data *data);

//----------------- token_copy.c ----------------------
int					find_operateur(char *line, int *i);
char				*ft_copy_pipe(int *i);
char				*ft_copy_operateur(int *i, int j);

//----------------- token_utils.c ----------------------
void				ft_change_word_to_cmd(t_data *data);
void				ft_check_access_cmd(t_data *data);

//----------------- tokenize.c ----------------------
void				tokenize(char *line, t_data *data);
char				*ft_enum_to_char(int num);

//================== main =====================================//

//----------------- free_data.c ----------------------
void				free_tok(t_token *tok);
void				free_env(t_env *env);
void				free_pipe(t_data *data);

//----------------- signal.c ----------------------
void				signal_handlers(void);

//----------------- main.c ----------------------
void				exit_prog(t_data *data, int code);

#endif