/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:19:57 by saberton          #+#    #+#             */
/*   Updated: 2024/12/09 19:01:06 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	first_pipe(t_data *data)
{
	printf("je rentre dans la cmd 0 pour ecrire dans %d\n",
		data->pipe->fds[0][1]);
	dup2(data->pipe->fds[0][1], STDOUT_FILENO);
	close(data->pipe->fds[0][0]);
	close(data->pipe->fds[0][1]);
}

static void	mid_pipe(t_data *data, int pipe_num)
{
	printf("je rentre dans la cmd %d pour lire %d & ecrire %d\n", pipe_num,
		data->pipe->fds[pipe_num - 1][0], data->pipe->fds[pipe_num][0]);
	dup2(data->pipe->fds[pipe_num - 1][0], STDIN_FILENO);
	dup2(data->pipe->fds[pipe_num][1], STDOUT_FILENO);
	close(data->pipe->fds[pipe_num - 1][0]);
	close(data->pipe->fds[pipe_num - 1][1]);
	close(data->pipe->fds[pipe_num][0]);
	close(data->pipe->fds[pipe_num][1]);
}

static void	last_pipe(t_data *data, int pipe_num)
{
	printf("je rentre dans la cmd %d pour lire dans %d\n", pipe_num,
		data->pipe->fds[pipe_num - 1][0]);
	dup2(data->pipe->fds[pipe_num - 1][0], STDIN_FILENO);
	close(data->pipe->fds[pipe_num - 1][0]);
	close(data->pipe->fds[pipe_num - 1][1]);
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
			return ; // exit_&_redisplay
		if (pipe(data_pipe->fds[i]) == -1)
			return ; // exit_&_redisplay
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

	// t_token	*prev;
	tmp = data->token;
	i = 0;
	data->pipe->pid = malloc(sizeof(pid_t) * (data->pipe->nb_pipe + 1));
	if (!data->pipe->pid)
		return ; // exit_&_redisplay
	orig_fds[0] = dup(STDIN_FILENO);
	orig_fds[1] = dup(STDOUT_FILENO);
	init_fds(data->pipe);
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
				{
					first_pipe(data);
				}
				else if (!recup_tok_after_pipe(tmp))
					last_pipe(data, i);
				else
					mid_pipe(data, i);
				for (int j = 0; j < data->pipe->nb_pipe; j++)
				{
					if (data->pipe->fds[j][0] >= 0)
						close(data->pipe->fds[j][0]);
					if (data->pipe->fds[j][1] >= 0)
						close(data->pipe->fds[j][1]);
				}
				exec_choice(data, tmp);
			}
		}
		else
		{
			if (i == 0)
			{
				first_pipe(data);
			}
			else if (!recup_tok_after_pipe(tmp))
				last_pipe(data, i);
			else
				mid_pipe(data, i);
			exec_choice(data, tmp);
			if (dup2(orig_fds[0], STDIN_FILENO) == -1 || dup2(orig_fds[1],
					STDOUT_FILENO) == -1)
				return ;
			if (!recup_tok_after_pipe(tmp))
				close(STDOUT_FILENO);
		}
		// for (int j = 0; j < i; j++)
		// {
		// 	waitpid(data->pipe->pid[j], NULL, 0);
		// }
		// }
		// else
		// {
		// 	data->pipe->pid[i] = -1;
		// 	prev = tmp;
		// 	if (i == 0)
		// 	{
		// 		first_pipe(data);
		// 	}
		// 	else if (!recup_tok_after_pipe(tmp))
		// 		last_pipe(data, i);
		// 	else
		// 		mid_pipe(data, i);
		// 	exec_choice(data, tmp);
		// }
		i++;
		data->pipe->i = i;
		tmp = recup_tok_after_pipe(tmp);
	}
	for (int j = 0; j < data->pipe->nb_pipe; j++)
	{
		if (data->pipe->fds[j][0] >= 0)
			close(data->pipe->fds[j][0]);
		if (data->pipe->fds[j][1] >= 0)
			close(data->pipe->fds[j][1]);
	}
	// for (int j = 0; j < i; j++)
	// {
	// 	waitpid(data->pipe->pid[j], NULL, 0);
	// }
	for (int j = 0; j < i; j++)
	{
		waitpid(data->pipe->pid[j], &status, 0);
		if (WIFEXITED(status))
		{
			printf("Child process %d finished with exit status %d\n",
				data->pipe->pid[j], WEXITSTATUS(status));
		}
		else if (WIFSIGNALED(status))
		{
			printf("Child process %d terminated by signal %d\n",
				data->pipe->pid[j], WTERMSIG(status));
		}
	}
	free_pipe(data);
}
