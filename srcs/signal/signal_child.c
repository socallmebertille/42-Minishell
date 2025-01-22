/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:39:15 by saberton          #+#    #+#             */
/*   Updated: 2024/12/21 00:26:56 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_child_sigint(int signum)
{
	(void)signum;
	write(2, "\n", 1);
	g_signal_received = 3;
	rl_done = 1;
	return ;
}

static void	handle_child_sigquit(int signum)
{
	(void)signum;
	write(2, "Quit (core dumped)\n", 20);
	g_signal_received = 4;
	rl_done = 1;
	return ;
}

static int	sig_event(void)
{
	return (EXIT_SUCCESS);
}

void	child_signal_handler(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	rl_event_hook = sig_event;
	sa.sa_handler = handle_child_sigint;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, handle_child_sigquit);
	signal(SIGTSTP, SIG_IGN);
}
