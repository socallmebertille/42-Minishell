/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kepouliq <kepouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:41:46 by saberton          #+#    #+#             */
/*   Updated: 2024/11/20 17:09:24 by kepouliq         ###   ########.fr       */
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

}					t_enum;

typedef struct s_env
{
	char			*type;
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
	char			*line;
	t_token			*token;
	char			**env;
	t_env			*cpy_env;
}					t_data;

//----------------- signal.c ---------------------
void				signal_handlers(void);

//----------------- env.c ------------------------
void				add_cpy_env(char *type, char *value, t_env **env,
						t_data *data);
void				get_env(char **env, t_data *data);

//----------------- token.c ----------------------
void				ft_strtok(char *line, t_data *data);
void				tokenize(char *line, t_data *data);

//----------------- split_charset.c --------------
char				**split_charset(char *str, char *charset);

#endif