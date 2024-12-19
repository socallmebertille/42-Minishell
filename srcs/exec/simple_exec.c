/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 14:00:04 by saberton          #+#    #+#             */
/*   Updated: 2024/12/19 14:04:24 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	simple_exec_build(t_data *data, t_token *tmp)
{
	exec_dup2_simple(data);
	handle_builtins(data, tmp, STDOUT_FILENO);
	if (dup2(data->pipe->orig_fds[0], STDIN_FILENO) == -1
		|| dup2(data->pipe->orig_fds[1], STDOUT_FILENO) == -1)
		return (failed_mess(data, "dup2 failed", 1));
}

static void	simple_exec_cmd(t_data *data, t_token *tmp, pid_t pid)
{
	if (pid == -1)
		return (failed_mess(data, "malloc failed", 1));
	if (pid == 0)
	{
		exec_dup2_simple(data);
		free_close_fds(data, 0);
		exec_choice(data, tmp);
	}
	else
		get_end_exec(data, 0, pid);
}

void	simple_exec(t_data *data, t_token *tmp)
{
	pid_t	pid;

	if (data->err || tmp->type == NOT_FOUND)
		return ;
	tmp = check_if_cmd_after_redir(data, tmp);
	if (tmp->type == BUILD)
		simple_exec_build(data, tmp);
	else if (tmp->type == CMD)
	{
		pid = fork();
		simple_exec_cmd(data, tmp, pid);
	}
}
