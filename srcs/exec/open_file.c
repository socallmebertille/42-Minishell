/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:56:52 by saberton          #+#    #+#             */
/*   Updated: 2024/12/19 14:09:52 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_heredoc(t_data *data, t_token *tok)
{
	char	*heredoc;

	if (pipe(data->redir->fds_doc) == -1)
		return (failed_mess(data, "pipe failed", 1));
	child_signal_handler();
	while (1)
	{
		heredoc = readline("> ");
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
	signal_handlers();
	data->redir->infile = data->redir->fds_doc[0];
}

static int	open_redirection_fd(t_data *data, int fd, t_token *token, int oflag)
{
	if (fd == 1 && data->redir->infile != -1)
	{
		close(data->redir->infile);
		data->redir->infile = -1;
	}
	if (fd == 2 && data->redir->outfile != -1)
	{
		close(data->redir->outfile);
		data->redir->outfile = -1;
	}
	if (!token->next)
		return (failed_mess(data, INVALID_NEXT_REDIR, 2), 0);
	if (token->next->type == INFILE || token->next->type == OUTFILE)
	{
		fd = open(token->next->value, oflag, 0644);
		if (fd < 0)
			return (failed_mess(data, "open failed", 2), 0);
		return (fd);
	}
	return (0);
}

void	open_file(t_data *data, t_token *tok)
{
	t_token	*tmp;

	data->redir->infile = -1;
	data->redir->outfile = -1;
	data->redir->heredoc = -1;
	data->redir->fds_doc[0] = -1;
	data->redir->fds_doc[1] = -1;
	tmp = tok;
	while (tmp)
	{
		if (tmp->type == PIPE || !tmp || data->err)
			return ;
		if (tmp->type == REDIR_INFILE && tmp->next->type == INFILE)
			data->redir->infile = open_redirection_fd(data, 1, tmp, O_RDONLY);
		else if (tmp->type == REDIR_OUTFILE && tmp->next->type == OUTFILE)
			data->redir->outfile = open_redirection_fd(data, 2, tmp,
					O_WRONLY | O_TRUNC | O_CREAT);
		else if (tmp->type == APPEND && tmp->next->type == OUTFILE)
			data->redir->outfile = open_redirection_fd(data, 2, tmp,
					O_WRONLY | O_APPEND | O_CREAT);
		else if (tmp->type == HEREDOC && tmp->next->type == DELIM)
			ft_heredoc(data, tmp);
		tmp = tmp->next;
	}
}

t_token	*check_if_cmd_after_redir(t_data *data, t_token *tok)
{
	if (tok->type == CMD || tok->type == BUILD || !tok)
		return (tok);
	while (tok)
	{
		if (!tok)
			break ;
		if (tok->type == CMD || tok->type == BUILD)
			break ;
		if (is_builtins(tok))
			tok->type = BUILD;
		else if (tok->type == WORD)
			tok->type = CMD;
		else
			tok = tok->next;
	}
	ft_check_access_cmd(data, 1);
	if (data->err)
		return (NULL);
	return (tok);
}
