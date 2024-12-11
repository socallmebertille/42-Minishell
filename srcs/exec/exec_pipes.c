/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kepouliq <kepouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:19:57 by saberton          #+#    #+#             */
/*   Updated: 2024/12/11 18:41:10 by kepouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	first_pipe(t_data *data)
{
	if (data->infile)
	{
		if (dup2(data->pipe->fds[0][1], STDIN_FILENO) == -1)
		{
			data->infile = 0;
			failed_mess(data, "dup2 failed", 1);
		}
	}
	if (dup2(data->pipe->fds[0][1], STDOUT_FILENO) == -1)
		failed_mess(data, "dup2 failed", 1);
}

static void	mid_pipe(t_data *data, int pipe_num)
{
	if (dup2(data->pipe->fds[pipe_num - 1][0], STDIN_FILENO) == -1)
		failed_mess(data, "dup2 failed", 1);
	if (dup2(data->pipe->fds[pipe_num][1], STDOUT_FILENO) == -1)
		failed_mess(data, "dup2 failed", 1);
}

static void	last_pipe(t_data *data, int pipe_num)
{
	if (dup2(data->pipe->fds[pipe_num - 1][0], STDIN_FILENO) == -1)
		failed_mess(data, "dup2 failed", 1);
	if (data->outfile)
	{
		if (dup2(data->pipe->fds[pipe_num][1], STDOUT_FILENO) == -1)
		{
			data->outfile = 0;
			failed_mess(data, "dup2 failed", 1);
		}
	}
}

static int	init_fds(t_pipe *data_pipe)
{
	int	i;

	data_pipe->fds = malloc(sizeof(int *) * (data_pipe->nb_pipe + 1));
	ft_bzero(data_pipe->fds, sizeof(int *));
	if (!data_pipe->fds)
		return (failed_mess(data_pipe->data, "malloc failed", 1), 0);
	i = 0;
	while (i < data_pipe->nb_pipe)
	{
		data_pipe->fds[i] = malloc(sizeof(int) * 2);
		if (!data_pipe->fds[i])
			return (failed_mess(data_pipe->data, "malloc failed", 1), 0);
		if (pipe(data_pipe->fds[i]) == -1)
			return (failed_mess(data_pipe->data, "pipe failed", 1), 0);
		i++;
	}
	data_pipe->fds[data_pipe->nb_pipe] = NULL;
	return (1);
}

void	ft_pipes(t_data *data)
{
	int		i;
	t_token	*tmp;
	int		status;

	tmp = data->token;
	i = 0;
	data->pipe->pid = (pid_t *)ft_calloc(data->nb_pipe + 1, sizeof(pid_t));
	if (!data->pipe->pid)
		return (failed_mess(data, "malloc failed", 1));
	data->pipe->orig_fds[0] = dup(STDIN_FILENO);
	data->pipe->orig_fds[1] = dup(STDOUT_FILENO);
	if (data->pipe->orig_fds[0] == -1 || data->pipe->orig_fds[1] == -1)
		return (failed_mess(data, "dup failed", 1));
	if (!init_fds(data->pipe))
		return ;
	while (tmp)
	{
		if (tmp->type == CMD)
		{
			data->pipe->pid[i] = fork();
			if (data->pipe->pid[i] < 0)
				return (failed_mess(data, "fork failed", 1));
			else if (data->pipe->pid[i] == 0)
			{
				if (i == 0)
					first_pipe(data);
				else if (!recup_tok_after_pipe(tmp))
					last_pipe(data, i);
				else
					mid_pipe(data, i);
				free_close_fds(data, 0);
				exec_choice(data, tmp);
			}
		}
		else
		{
			data->pipe->pid[i] = -1;
			if (i == 0)
				first_pipe(data);
			else if (!recup_tok_after_pipe(tmp))
				last_pipe(data, i);
			else
				mid_pipe(data, i);
			exec_choice(data, tmp);
			if (dup2(data->pipe->orig_fds[0], STDIN_FILENO) == -1
				|| dup2(data->pipe->orig_fds[1], STDOUT_FILENO) == -1)
				return (failed_mess(data, "dup2 failed", 1));
		}
		i++;
		tmp = recup_tok_after_pipe(tmp);
	}
	free_close_fds(data, 0);
	for (int j = 0; j < i; j++)
	{
		if (data->pipe->pid[j] != -1)
			waitpid(data->pipe->pid[j], &status, 0);
		// if (WIFEXITED(status))
		// {
		// 	printf("Child process %d finished with exit status %d\n",
		// 		data->pipe->pid[j], WEXITSTATUS(status));
		// }
		// else if (WIFSIGNALED(status))
		// {
		// 	printf("Child process %d terminated by signal %d\n",
		// 		data->pipe->pid[j], WTERMSIG(status));
		// }
	}
	free_pipe(data);
}
