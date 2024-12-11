/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:30:06 by saberton          #+#    #+#             */
/*   Updated: 2024/12/11 20:29:57 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	loop_end_exec(t_data *data, pid_t pid, int status)
{
	if (pid != -1)
		waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		data->exit_status += WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
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
