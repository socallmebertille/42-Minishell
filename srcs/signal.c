/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:54:47 by bertille          #+#    #+#             */
/*   Updated: 2024/12/12 17:11:28 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static volatile sig_atomic_t	g_signal_received = 0;

static void	handle_sigint(int signum)
{
	(void)signum;
	g_signal_received = 1;
	write(2, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_handlers(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

void	reset_signal_handler(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

void	child_signal_handler(void)
{
	// signal(SIGINT, SIG_DFL);
	// signal(SIGQUIT, SIG_DFL);
}
