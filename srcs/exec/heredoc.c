/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 19:10:37 by uzanchi           #+#    #+#             */
/*   Updated: 2024/12/20 19:46:10 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_in_file(t_data *data, int fd, char *delim)
{
	while (g_signal_received != 3)
	{
		if (g_signal_received == 3)
			return (0);
		data->redir->heredoc = readline("> ");
		if (g_signal_received == 3)
			return (free(data->redir->heredoc), 0);
		if (!data->redir->heredoc)
		{
			ft_putstr_fd("minishell: warning: here-document at line 1 ", 2);
			ft_putstr_fd("delimited by end-of-file (wanted `", 2);
			ft_putstr_fd(delim, 2);
			ft_putstr_fd("')\n", 2);
			break ;
		}
		if (ft_strcmp(delim, data->redir->heredoc) == 0)
		{
			free(data->redir->heredoc);
			break ;
		}
		ft_putstr_fd(data->redir->heredoc, fd);
		ft_putstr_fd("\n", fd);
	}
	return (1);
}

static void	init_tok_for_cmd(t_data *data, t_token *tok)
{
	t_token	*tmp;

	data->redir->here_tmp += 1;
	free(tok->value);
	tok->value = ft_strdup("heredoc.tmp");
	tok->type = WORD;
	if (tok->next)
	{
		tmp = tok->next;
		tok->next = tok->next->next;
		if (tok->next)
			tok->next->prev = tok;
		if (tmp->value)
		{
			free(tmp->value);
			tmp->value = NULL;
		}
		free(tmp);
		tmp = NULL;
	}
}

static int	no_cmd(t_data *data)
{
	t_token	*tok;

	tok = data->token;
	if (!tok)
		return (0);
	while (tok)
	{
		if (tok->type == CMD || tok->type == BUILD)
			return (1);
		tok = tok->next;
	}
	return (0);
}

void	ft_heredoc(t_data *data, t_token *tok)
{
	int		fd;

	g_signal_received = 2;
	fd = open("heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (failed_mess(data, "open failed", 1));
	child_signal_handler();
	if (!print_in_file(data, fd, tok->next->value))
	{
		close(fd);
		data->exit_status = 130;
		data->err = 1;
		return ;
	}
	close(fd);
	if (!no_cmd(data))
		return ;
	init_tok_for_cmd(data, tok);
	return ;
}
