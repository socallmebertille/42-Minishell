/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:19:57 by saberton          #+#    #+#             */
/*   Updated: 2024/12/18 16:22:40 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_fds(t_pipe *data_pipe)
{
	int	i;

	i = 0;
	data_pipe->fds = malloc(sizeof(int *) * (data_pipe->nb_pipe + 1));
	if (!data_pipe->fds)
		return (failed_mess(data_pipe->data, "malloc failed", 1), 0);
	while (i < data_pipe->nb_pipe + 1)
		data_pipe->fds[i++] = NULL;
	i = 0;
	while (i < data_pipe->nb_pipe)
	{
		data_pipe->fds[i] = malloc(sizeof(int) * 2);
		if (!data_pipe->fds[i])
			return (failed_mess(data_pipe->data, "malloc failed", 1), 0);
		data_pipe->fds[i][0] = -1;
		data_pipe->fds[i][1] = -1;
		if (pipe(data_pipe->fds[i]) == -1)
			return (failed_mess(data_pipe->data, "pipe failed", 1), 0);
		i++;
	}
	data_pipe->fds[data_pipe->nb_pipe] = NULL;
	return (1);
}

static void	cmd_in_pipe(t_data *data, t_token *tmp, int i)
{
	if (tmp->type == CMD)
	{
		data->pipe->pid[i] = fork();
		if (data->pipe->pid[i] < 0)
			return (quit_pipe(data, i), failed_mess(data, "fork failed", 1));
		else if (data->pipe->pid[i] == 0)
		{
			exec_dup2_pipe(data, tmp, i);
			free_close_fds(data, i);
			exec_choice(data, tmp);
		}
	}
	else if (tmp->type == BUILD)
	{
		data->pipe->pid[i] = -1;
		exec_dup2_pipe(data, tmp, i);
		if ((!ft_strcmp(tmp->value, "export") && tmp->next->type == WORD)
			|| !ft_strcmp(tmp->value, "exit"))
			;
		else
			exec_choice(data, tmp);
		if (dup2(data->pipe->orig_fds[0], STDIN_FILENO) == -1
			|| dup2(data->pipe->orig_fds[1], STDOUT_FILENO) == -1)
			return (quit_pipe(data, i), failed_mess(data, "dup2 failed", 1));
	}
}

static void	exec_in_pipe(t_data *data, t_token *tmp, int i)
{
	if (tmp->type == CMD || tmp->type == BUILD)
		cmd_in_pipe(data, tmp, i);
	else
		data->err = 1;
}

void	ft_pipes(t_data *data)
{
	int		i;
	t_token	*tmp;

	tmp = data->token;
	i = 0;
	data->pipe->pid = (pid_t *)ft_calloc(data->pipe->nb_pipe + 1,
			sizeof(pid_t));
	if (!data->pipe->pid)
		return (quit_pipe(data, i), failed_mess(data, "malloc failed", 1));
	if (!init_fds(data->pipe))
		return (quit_pipe(data, i));
	while (tmp)
	{
		open_file(data, tmp);
		if (data->err)
			break ;
		exec_in_pipe(data, tmp, i);
		if (data->err)
			break ;
		i++;
		tmp = recup_tok_after_pipe(tmp);
	}
	quit_pipe(data, i);
}
