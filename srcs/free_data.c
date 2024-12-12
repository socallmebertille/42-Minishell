/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:11:39 by saberton          #+#    #+#             */
/*   Updated: 2024/12/12 15:00:40 by saberton         ###   ########.fr       */
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
	int	i;

	i = 0;
	if (!data || !data->pipe)
		return ;
	if (data->pipe->pid)
	{
		free(data->pipe->pid);
		data->pipe->pid = NULL;
	}
	data->pipe = NULL;
}

static void	close_one_fd(int fd)
{
	if (fd >= 3)
		close(fd);
}

void	free_close_fds(t_data *data, int sous_process)
{
	int	i;

	i = 0;
	if (!data->pipe->nb_pipe)
		return ;
	while (i < data->pipe->nb_pipe)
	{
		close_one_fd(data->pipe->fds[i][0]);
		close_one_fd(data->pipe->fds[i][1]);
		if (data->pipe->fds[i] && !sous_process)
		{
			free(data->pipe->fds[i]);
			data->pipe->fds[i] = NULL;
		}
		i++;
	}
	close_one_fd(data->pipe->orig_fds[0]);
	close_one_fd(data->pipe->orig_fds[1]);
	if (sous_process)
		return ;
	if (data->pipe->fds)
		free(data->pipe->fds);
	data->pipe->fds = NULL;
	data->pipe->nb_pipe = 0;
}

void	quit_pipe(t_data *data, int i)
{
	free_close_fds(data, 0);
	get_end_exec(data, i, -1);
	free_pipe(data);
}
