/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzanchi <uzanchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 19:10:37 by uzanchi           #+#    #+#             */
/*   Updated: 2024/12/18 21:03:17 by uzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	reset_line(int signum)
{
	(void)signum;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(1, "\n", STDERR_FILENO);
	rl_redisplay();
}

static void	signals_interactive(void)
{
	signal(SIGINT, reset_line);
	signal(SIGQUIT, SIG_IGN);
}

static void	display_new_line(int signum)
{
	if (signum == SIGQUIT)
		ft_printf("Quit (core dumped)");
	write(1, "\n", STDERR_FILENO);
	rl_on_new_line();
}

static void	signals_non_interactive(void)
{
	signal(SIGINT, display_new_line);
	signal(SIGQUIT, display_new_line);
}

void	ft_heredoc(t_data *data, t_token *tok)
{
	char	*heredoc;

	if (pipe(data->redir->fds_doc) == -1)
		return (failed_mess(data, "pipe failed", 1));
	while (1)
	{
		signals_interactive();
		heredoc = readline("> ");
		signals_non_interactive();
		if (!heredoc)
			break ;
		if (!ft_strncmp(tok->next->value, heredoc, ft_strlen(tok->value)))
		{
			free(heredoc);
			break ;
		}
		write(data->redir->fds_doc[1], heredoc, ft_strlen(heredoc));
		write(data->redir->fds_doc[1], "\n", 1);
		free(heredoc);
	}
	data->redir->infile = data->redir->fds_doc[0];
	close(data->redir->fds_doc[1]);
	data->redir->fds_doc[1] = -1;
}
