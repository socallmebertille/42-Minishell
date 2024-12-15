/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:30:06 by saberton          #+#    #+#             */
/*   Updated: 2024/12/15 12:38:29 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_one_fd(int fd)
{
	if (fd >= 3)
		close(fd);
}

static void	close_if_open(t_data *data)
{
	if (data->redir->infile)
		close(data->redir->infile);
	if (data->redir->outfile)
		close(data->redir->outfile);
	if (data->redir->fds_doc[0])
		close(data->redir->fds_doc[0]);
	if (data->redir->fds_doc[1])
		close(data->redir->fds_doc[1]);
	
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
	close_if_open(data);
	if (sous_process)
		return ;
	if (data->pipe->fds)
		free(data->pipe->fds);
	data->pipe->fds = NULL;
	data->pipe->nb_pipe = 0;
}

static void	loop_end_exec(t_data *data, pid_t pid, int status)
{
	if (pid != -1)
		waitpid(pid, &status, 0);
	if (WIFEXITED(status) && !data->err)
		data->exit_status += WEXITSTATUS(status);
	else if (WIFSIGNALED(status) && !data->err)
	{
		if (WTERMSIG(status) == 2)
			data->exit_status += 2;
	}
}

void	get_end_exec(t_data *data, int i, pid_t pid)
{
	int	status;
	int	j;

	status = 0;
	if (pid >= 0 && !i)
	{
		loop_end_exec(data, pid, status);
		return ;
	}
	j = 0;
	if (!i)
		return ;
	while (j < i)
	{
		loop_end_exec(data, data->pipe->pid[j], status);
		j++;
	}
}

void	failed_mess(t_data *data, char *mess, int code)
{
	ft_putstr_fd(mess, 2);
	if (*mess)
		ft_putstr_fd("\n", 2);
	data->err = 1;
	data->exit_status += code;
}
