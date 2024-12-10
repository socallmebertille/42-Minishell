/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:11:39 by saberton          #+#    #+#             */
/*   Updated: 2024/12/10 12:33:29 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tok(t_token *tok)
{
	t_token	*tmp;

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
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->type);
		free(env->value);
		free(env);
		env = tmp;
	}
}

void	free_pipe(t_data *data)
{
	int	i;

	i = 0;
	if (!data || !data->pipe || !data->nb_pipe)
		return ;
	if (data->pipe->fds)
	{
		while (i < data->pipe->nb_pipe)
		{
			if (data->pipe->fds[i])
			{
				free(data->pipe->fds[i]);
				data->pipe->fds[i] = NULL;
			}
			i++;
		}
		free(data->pipe->fds);
		data->pipe->fds = NULL;
	}
	if (data->pipe->pid)
	{
		free(data->pipe->pid);
		data->pipe->pid = NULL;
	}
	data->pipe = NULL;
}
