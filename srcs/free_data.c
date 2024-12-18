/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:11:39 by saberton          #+#    #+#             */
/*   Updated: 2024/12/18 14:28:39 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tok(t_data *data)
{
	t_token	*tok;
	t_token	*tmp;

	if (!data->token)
		return ;
	tok = data->token;
	tmp = tok;
	while (tmp)
	{
		if (tmp->value)
		{
			free(tmp->value);
			tmp->value = NULL;
		}
		tok = tok->next;
		free(tmp);
		tmp = tok;
	}
	data->token = NULL;
}

void	free_env(t_data *data, t_env *env, int cpy)
{
	t_env	*tmp;

	if (cpy == 1 && !data->cpy_env)
		return ;
	if (cpy == 2 && !data->cpy_env2)
		return ;
	tmp = env;
	while (env)
	{
		tmp = env->next;
		if (env->type)
			free(env->type);
		if (env->value)
			free(env->value);
		env->type = NULL;
		env->value = NULL;
		free(env);
		env = tmp;
	}
	if (cpy == 1)
		data->cpy_env = NULL;
	else if (cpy == 2)
		data->cpy_env2 = NULL;
}

void	free_pipe(t_data *data)
{
	if (!data || !data->pipe)
		return ;
	if (data->pipe->pid)
	{
		free(data->pipe->pid);
		data->pipe->pid = NULL;
	}
	data->pipe = NULL;
}

void	quit_pipe(t_data *data, int i)
{
	free_close_fds(data, 0);
	get_end_exec(data, i, -1);
	free_pipe(data);
}

void	failed_mess(t_data *data, char *mess, int code)
{
	ft_putstr_fd(mess, 2);
	if (*mess)
		ft_putstr_fd("\n", 2);
	data->err = 1;
	data->exit_status += code;
}
