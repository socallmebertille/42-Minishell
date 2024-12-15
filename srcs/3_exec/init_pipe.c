/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 13:07:11 by saberton          #+#    #+#             */
/*   Updated: 2024/12/15 13:09:23 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*build_pipes(t_data *data, int fd_out, int fd_in, int cmds_num)
{
	int	i;
	int	*fd_pipes;

	if (!cmds_num)
		return (0);
	fd_pipes = ft_calloc((2 * cmds_num) + 3, sizeof(int));
	if (!fd_pipes)
		return (failed_mess(data, "malloc failed", 1), NULL);
	fd_pipes[0] = fd_in;
	fd_pipes[1] = -1;
	fd_pipes[(2 * cmds_num)] = -1;
	fd_pipes[(2 * cmds_num) + 1] = fd_out;
	i = 0;
	while (fd_pipes && ++i < cmds_num)
	{
		if (pipe(&fd_pipes[i * 2]) < 0)
		{
			failed_mess(data, "pipe failed", 1);
			free(fd_pipes);
			return (NULL);
		}
	}
	return (fd_pipes);
}
