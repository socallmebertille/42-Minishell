/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:19:57 by saberton          #+#    #+#             */
/*   Updated: 2024/12/10 19:34:13 by saberton         ###   ########.fr       */
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
			return ;
		}
	}
	if (dup2(data->pipe->fds[0][1], STDOUT_FILENO) == -1)
		return ;
}

static void	mid_pipe(t_data *data, int pipe_num)
{
	if (dup2(data->pipe->fds[pipe_num - 1][0], STDIN_FILENO) == -1)
		return ;
	if (dup2(data->pipe->fds[pipe_num][1], STDOUT_FILENO) == -1)
		return ;
}

static void	last_pipe(t_data *data, int pipe_num)
{
	if (dup2(data->pipe->fds[pipe_num - 1][0], STDIN_FILENO) == -1)
		return ;
	if (data->outfile)
	{
		if (dup2(data->pipe->fds[pipe_num][1], STDOUT_FILENO) == -1)
		{
			data->outfile = 0;
			return ;
		}
	}
}

static void	init_fds(t_pipe *data_pipe)
{
	int	i;

	data_pipe->fds = malloc(sizeof(int *) * (data_pipe->nb_pipe + 1));
	ft_bzero(data_pipe->fds, sizeof(int *));
	if (!data_pipe->fds)
		return ; // exit_&_redisplay
	i = 0;
	while (i < data_pipe->nb_pipe)
	{
		data_pipe->fds[i] = malloc(sizeof(int) * 2);
		if (!data_pipe->fds[i])
		{
			perror("pipe allocation failed");
			exit_prog(data_pipe->data, EXIT_FAILURE);
		} // exit_&_redisplay
		if (pipe(data_pipe->fds[i]) == -1)
		{
			perror("pipe allocation failed");
			exit_prog(data_pipe->data, EXIT_FAILURE);
		} // exit_&_redisplay
		i++;
	}
	data_pipe->fds[data_pipe->nb_pipe] = NULL;
	// i = 0;
	// while (i < data_pipe->nb_pipe)
	// {
	// 	printf("fd %d [%d][%d]\n", i, data_pipe->fds[i][0],
	// 		data_pipe->fds[i][1]);
	// 	i++;
	// }
}

void	ft_pipes(t_data *data)
{
	int		i;
	t_token	*tmp;
	int		orig_fds[2];
	int		status;

	tmp = data->token;
	i = 0;
	data->pipe->pid = (pid_t *)ft_calloc(data->nb_pipe + 1, sizeof(pid_t));
	if (!data->pipe->pid)
		return ; // exit_&_redisplay
	orig_fds[0] = dup(STDIN_FILENO);
	orig_fds[1] = dup(STDOUT_FILENO);
	if (orig_fds[0] == -1 || orig_fds[1] == -1)
		return ; // exit_&_redisplay
	init_fds(data->pipe);
	if (!data->pipe || !data->pipe->fds)
		exit_prog(data, EXIT_FAILURE);
	data->pipe->i = i;
	while (tmp)
	{
		if (tmp->type == CMD)
		{
			data->pipe->pid[i] = fork();
			if (data->pipe->pid[i] < 0)
				exit_prog(data, EXIT_FAILURE);
			else if (data->pipe->pid[i] == 0)
			{
				if (i == 0)
					first_pipe(data);
				else if (!recup_tok_after_pipe(tmp))
					last_pipe(data, i);
				else
					mid_pipe(data, i);
				for (int j = 0; j < data->pipe->nb_pipe; j++)
				{
					if (data->pipe->fds[j][0] >= 1)
						close(data->pipe->fds[j][0]);
					if (data->pipe->fds[j][1] >= 1)
						close(data->pipe->fds[j][1]);
				}
				exec_choice(data, tmp);
			}
		}
		else
		{
			// if (dup2(data->pipe->fds[i][0], STDIN_FILENO) == -1
			// 	|| dup2(data->pipe->fds[i][1], STDOUT_FILENO) == -1)
			// 	return ; // exit_&_redisplay
			data->pipe->pid[i] = -1;
			if (i == 0)
				first_pipe(data);
			else if (!recup_tok_after_pipe(tmp))
				last_pipe(data, i);
			else
				mid_pipe(data, i);
			exec_choice(data, tmp);
			if (dup2(orig_fds[0], STDIN_FILENO) == -1 || dup2(orig_fds[1],
					STDOUT_FILENO) == -1)
				return ;
		}
		i++;
		data->pipe->i = i;
		tmp = recup_tok_after_pipe(tmp);
	}
	for (int j = 0; j < data->pipe->nb_pipe; j++)
	{
		if (data->pipe->fds[j][0] >= 1)
			close(data->pipe->fds[j][0]);
		if (data->pipe->fds[j][1] >= 1)
			close(data->pipe->fds[j][1]);
	}
	close(orig_fds[0]);
	close(orig_fds[1]);
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
