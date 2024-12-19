/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:41:46 by saberton          #+#    #+#             */
/*   Updated: 2024/12/19 18:14:36 by saberton         ###   ########.fr       */
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
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef enum e_enum
{
	CMD,
	WORD,
	APPEND,
	HEREDOC,
	DELIM,
	REDIR_INFILE = '<',
	REDIR_OUTFILE = '>',
	PIPE = '|',
	INFILE,
	OUTFILE,
	BUILD,
	NOT_FOUND,
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
	int				orig_fds[2];
	int				**fds;
	pid_t			*pid;
	struct s_data	*data;
}					t_pipe;

typedef struct s_redir
{
	int				infile;
	int				outfile;
	int				here_tmp;
	char			*heredoc;
	struct s_data	*data;
}					t_redir;

typedef struct s_data
{
	int				exit_code;
	int				err_quote;
	int				err_export;
	int				err;
	int				exit_status;
	char			wich_quote_err;
	char			*expanded_str;
	char			*line;
	char			**env;
	t_redir			*redir;
	t_token			*token;
	t_env			*cpy_env;
	t_env			*cpy_env2;
	t_pipe			*pipe;
}					t_data;

//================== builtins =====================================//

//----------------- cd.c ------------------------
void				handle_cd(t_data *data, t_token *tok, int fd_out);

//----------------- cd_utils.c ------------------------
void				change_old_env_pwd(t_data *data, char *path);
void				change_env_pwd(t_data *data);
char				*get_actual_env_path(t_data *data);
char				*get_home_env(t_data *data);

//----------------- echo.c ------------------------
void				handle_echo(t_data *data, t_token *tok, int fd_out);

//----------------- env.c ------------------------
void				handle_env(t_data *data, t_token *tok, int fd_out);

//----------------- exit.c ------------------------
void				handle_exit(t_data *data, t_token *tok, int fd_out);

//----------------- export.c ------------------------
void				handle_export(t_data *data, t_token *tok, int fd_out);

//----------------- export_utils.c ------------------------
void				modif_env_node(t_data *data, char *value, int j);
void				add_env_node(t_data *data, char *value);
void				display_export_order(t_data *data, int fd_out);
int					find_if_env_exist(t_env *env, char *value);
int					is_valid_name(char *name);

//----------------- export_utils.c ------------------------
void				modif_env_node(t_data *data, char *value, int j);
void				add_env_node(t_data *data, char *value);
void				display_export_order(t_data *data, int fd_out);
int					find_if_env_exist(t_env *env, char *value);
int					is_valid_name(char *name);

//----------------- get_env.c ------------------------
void				get_shlvl_env(t_data *data);
void				get_env(char **env, t_data *data);
void				add_cpy_env(char *type, char *value, t_env **env,
						t_data *data);
t_env				*last_value(t_env *env);

//----------------- get_export_env.c.c ----------------------
void				add_cpy_env2(char *type, char *value, t_env **env,
						t_data *data);
void				get_shlvl_export(t_data *data);
void				get_env2(char **env, t_data *data);

//----------------- pwd.c ----------------------
void				handle_pwd(t_data *data, t_token *tok, int fd_out);

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

//----------------- remove_quote.c ----------------------
void				remove_quote(char *str, t_token *tok);

//----------------- parse.c ----------------------
void				parse(t_data *data);
void				syntaxe_line(char *line, t_data *data);
int					is_builtins(t_token *token);
int					handle_builtins(t_data *data, t_token *tok, int fd_out);

//================== exec =====================================//

//----------------- env_to_send.c ---------------------
char				**env_to_tab(t_env *env);

//----------------- exec_dup2.c ---------------------
void				exec_dup2_pipe(t_data *data, t_token *tmp, int i);
void				exec_dup2_simple(t_data *data);

//----------------- exec_pipes.c ----------------------
void				ft_pipes(t_data *data);

//----------------- exec_utils.c ----------------------
int					pipe_in_line(t_data *data);
char				**recup_cmd(t_data *data, t_token *tok);
t_token				*recup_tok_after_pipe(t_token *tmp);

//----------------- exec.c ----------------------
void				update_last_cmd(t_data *data, char *cmd_path);
void				exec_cmd(t_data *data, char **env, char **cmd,
						t_token *tok);
void				exec_choice(t_data *data, t_token *tok);
void				wich_exec(t_data *data, t_token *tmp);

//----------------- heredoc.c ----------------------
void				ft_heredoc(t_data *data, t_token *tok);

//----------------- open_file.c ----------------------
void				open_file(t_data *data, t_token *tok);
t_token				*check_if_cmd_after_redir(t_data *data, t_token *tok);

//----------------- simple_exec.c ----------------------
void				simple_exec(t_data *data, t_token *tmp);

//================== expand =====================================//

//----------------- expand_dollars.c ----------------------
int					dollar_in_str(char *str, t_data *data);
char				*expand_dollar_sequence(char **str, int *i);

//----------------- expand_utils.c ----------------------
size_t				get_var_len(char *str);
int					is_exist_in_env(char *var, t_data *data);
int					is_in_single_quotes(char *str, int index);
char				*ft_strjoin_char(char *str, char c);

//----------------- expand_utils2.c ----------------------
int					is_in_double_quotes(char *str, int index);
char				*give_me_inside_var(char *var, t_data *data);
char				*extract_var(char *str, int *i);
char				*ft_concate(char *before, char *in_var);

//----------------- expand.c ----------------------
char				*extract_var(char *str, int *i);
void				expand(t_data *data);

//================== token =====================================//

//----------------- add_token.c ----------------------
void				add_token_word(char *line, t_token **tok, t_data *data,
						int *i);
void				add_token_pipe(t_token **tok, t_data *data, int *i);
void				add_token_operateur(char *line, t_token **tok, t_data *data,
						int *i);
t_token				*last_token(t_token *tok);

//----------------- check_token_type2.c ----------------------
int					is_word(char c);
int					is_word_and_space(char c);

//----------------- check_token_type.c ----------------------
int					is_quote(char c);
int					is_pipe(char c);
int					is_operateur(char c);
int					ft_isspace(char c);

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
void				ft_change_word_to_type(t_data *data);
void				ft_check_access_cmd(t_data *data, int step);

//----------------- tokenize.c ----------------------
void				tokenize(char *line, t_data *data);
char				*ft_enum_to_char(int num);

//================== main =====================================//

//----------------- exit_status.c ----------------------
void				free_close_fds(t_data *data, int sous_process);
void				get_end_exec(t_data *data, int i, pid_t pid);

//----------------- free_data.c ----------------------
void				free_tok(t_data *data);
void				free_env(t_data *data, t_env *env, int cpy);
void				free_pipe(t_data *data);
void				quit_pipe(t_data *data, int i);
void				failed_mess(t_data *data, char *mess, int code);

//----------------- signal.c --------------------------
void				signal_handlers(void);
void				reset_signal_handler(t_data *data);
void				child_signal_handler(void);

//----------------- write_str.c --------------------------
void				write_char_fd(t_data *data, char *str_err, char c, int fd);
void				write_str_fd(t_data *data, char *str_err, char *s, int fd);

//----------------- main.c ----------------------
void				exit_prog(t_data *data, int code);

#endif