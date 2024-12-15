/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_dup2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 08:51:10 by saberton          #+#    #+#             */
/*   Updated: 2024/12/15 11:50:30 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	first_pipe(t_data *data)
{
	// if (data->redir->infile != -1)
	// {
	// 	if (dup2(data->redir->infile, STDIN_FILENO) == -1)
	// 		failed_mess(data, "dup2 pfailed", 1);
	// 	return ;
	// }
	if (dup2(data->pipe->fds[0][1], STDOUT_FILENO) == -1)
		failed_mess(data, "dup2 afailed", 1);
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
	if (pipe_num)
	{
		if (dup2(data->pipe->fds[pipe_num - 1][0], STDIN_FILENO) == -1)
			failed_mess(data, "dup2 failed", 1);
	}
	// if (data->redir->outfile != -1)
	// {
	// 	if (dup2(data->redir->outfile, STDOUT_FILENO) == -1)
	// 		failed_mess(data, "dup2 failed", 1);
	// }
}

void	exec_dup2_pipe(t_data *data, t_token *tmp, int i)
{
	if (i == 0)
		first_pipe(data);
	else if (!recup_tok_after_pipe(tmp))
		last_pipe(data, i);
	else
		mid_pipe(data, i);
}

void	exec_dup2_simple(t_data *data)
{
	first_pipe(data);
	last_pipe(data, 0);
}
