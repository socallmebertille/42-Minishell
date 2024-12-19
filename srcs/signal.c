/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:54:47 by bertille          #+#    #+#             */
/*   Updated: 2024/12/19 14:18:23 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_sigint(int signum)
{
	(void)signum;
	write(2, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_signal_received = 1;
}

void	signal_handlers()
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

void	reset_signal_handler(t_data *data)
{
	if (g_signal_received == 1 && data->exit_code == 130)
	{
		g_signal_received = 0;
		data->exit_status = 0;
	}
}

static void	handle_child_sigint(int signum)
{
	(void)signum;
	write(2, "\n", 1);
	rl_on_new_line();
}

void	child_signal_handler(void)
{
	signal(SIGINT, handle_child_sigint);
	signal(SIGQUIT, SIG_DFL);
}
