/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:56:52 by saberton          #+#    #+#             */
/*   Updated: 2024/12/14 21:03:40 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	open_in(t_data *data, t_token *tok)
{
	t_token	*tmp;

	tmp = tok;
	while (tmp)
	{
		if (tmp->type == INFILE)
			break ;
		tmp = tmp->next;
	}
	data->redir->infile = -1;
	data->redir->infile = open(tmp->value, O_RDONLY);
	if (data->redir->infile == -1)
	{
		ft_check_access_cmd(data, 2);
		if (data->exit_status == 127)
			return ;
		return (failed_mess(data, "open failed", 1));
	}
}

static void	open_out(t_data *data, t_token *tok)
{
	t_token	*tmp;

	tmp = tok;
	while (tmp)
	{
		if (tmp->type == OUTFILE)
			break ;
		tmp = tmp->next;
	}
	data->redir->outfile = -1;
	if (tmp->prev->type == REDIR_OUTFILE)
		data->redir->outfile = open(tmp->value, O_WRONLY | O_CREAT | O_TRUNC,
				0777);
	else if (tmp->prev->type == APPEND)
		data->redir->outfile = open(tmp->value, O_WRONLY | O_CREAT | O_APPEND,
				0777);
	if (data->redir->outfile == -1)
	{
		ft_check_access_cmd(data, 2);
		if (data->exit_status == 127)
			return ;
		return (failed_mess(data, "open failed", 1));
	}
}

static void	open_delim(t_data *data, t_token *tok)
{
	t_token	*tmp;
	char	*heredoc;

	tmp = tok;
	while (tmp)
	{
		if (tmp->type == DELIM)
			break ;
		tmp = tmp->next;
	}
	if (pipe(data->redir->fds_doc) == -1)
		return (failed_mess(data, "pipe failed", 1));
	while (1)
	{
		heredoc = readline("> ");
		// if (g_sigint)
		// 	return (sigint_heredoc(shell, cmd, buffer, fd));
		if (!heredoc)
			break ;
		// return ((void)close(fd), 1);
		if (!ft_strncmp(tmp->value, heredoc, ft_strlen(tmp->value)))
		{
			free(heredoc);
			break ;
		}
		write(data->redir->fds_doc[1], heredoc, ft_strlen(heredoc));
		write(data->redir->fds_doc[1], "\n", 1);
		free(heredoc);
	}
}

static t_enum	wich_type_rw(t_token *tok)
{
	int		choice;
	t_token	*tmp;

	choice = 0;
	tmp = tok;
	while (tmp)
	{
		if (tmp->type == REDIR_INFILE)
			return (REDIR_INFILE);
		else if (tmp->type == REDIR_OUTFILE)
			return (REDIR_OUTFILE);
		else if (tmp->type == APPEND)
			return (APPEND);
		else if (tmp->type == HEREDOC)
			return (HEREDOC);
		tmp = tmp->next;
	}
	return (CMD);
}

void	open_file(t_data *data, t_token *tok)
{
	t_enum choice;

	choice = wich_type_rw(tok);
	if (choice == REDIR_INFILE)
		open_in(data, tok);
	else if (choice == REDIR_OUTFILE || choice == APPEND)
		open_out(data, tok);
	else if (choice == HEREDOC)
		open_delim(data, tok);
}