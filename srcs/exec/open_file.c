/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:56:52 by saberton          #+#    #+#             */
/*   Updated: 2024/12/15 13:03:14 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	ft_heredoc(t_data *data, t_token *tok, int oflag)
// {
// 	char	*heredoc;

// 	if (pipe(data->redir->fds_doc) == -1)
// 		return (failed_mess(data, "pipe failed", 1));
// 	while (1)
// 	{
// 		heredoc = readline("> ");
// 		if (g_sigint)
// 			return (sigint_heredoc(shell, cmd, buffer, fd));
// 		if (!heredoc)
// 			break ;
// 		return ((void)close(fd), 1);
// 		if (!ft_strncmp(tok->value, heredoc, ft_strlen(tok->value)))
// 		{
// 			free(heredoc);
// 			break ;
// 		}
// 		write(data->redir->fds_doc[1], heredoc, ft_strlen(heredoc));
// 		write(data->redir->fds_doc[1], "\n", 1);
// 		free(heredoc);
// 	}
// 	data->redir->infile = data->redir->fds_doc[0];
// }

static int	open_redirection_fd(t_data *data, int fd, t_token *token, int oflag)
{
	if (fd == 1 && data->redir->infile)
	{
		close(data->redir->infile);
		data->redir->infile = 0;
	}
	if (fd == 2 && data->redir->outfile)
	{
		close(data->redir->outfile);
		data->redir->outfile = 0;
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
	// else if (token->next->type == HEREDOC)
	// 	ft_heredoc(data, token, oflag);
	return (0);
}

void	open_file(t_data *data, t_token *tok)
{
	t_token	*tmp;

	tmp = tok;
	while (tmp)
	{
		if (tmp->type == PIPE || !tmp)
			return ;
		if (tmp->type == REDIR_INFILE && tmp->next->type == INFILE)// || tmp->type == HEREDOC)
			data->redir->infile = open_redirection_fd(data, 1, tmp, O_RDONLY);
		else if (tmp->type == REDIR_OUTFILE && tmp->next->type == OUTFILE)
			data->redir->outfile = open_redirection_fd(data, 2, tmp,
				O_WRONLY | O_TRUNC | O_CREAT);
		else if (tmp->type == APPEND && tmp->next->type == OUTFILE)
			data->redir->outfile = open_redirection_fd(data, 2, tmp,
				O_WRONLY | O_APPEND | O_CREAT);
		// if (tmp->type == HEREDOC && tmp->next->type == DELIM)
		// 	ft_heredoc();
		tmp = tmp->next;
	}
}
