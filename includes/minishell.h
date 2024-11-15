/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kepouliq <kepouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:41:46 by saberton          #+#    #+#             */
/*   Updated: 2024/11/15 18:24:12 by kepouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include "colors.h"
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

typedef struct s_env
{
	char			*type;
	char			*value;
	struct s_env	*next;
}		t_env;

//		signal.c
void	signal_handlers(void);

//		env.c
t_env	**add_cpy_env(char *type, char *value, t_env **env);
t_env	**get_env(char **env, t_env **cpy_env);

#endif