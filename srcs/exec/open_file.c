/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:56:52 by saberton          #+#    #+#             */
/*   Updated: 2024/12/19 21:33:21 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_file_exist(t_data *data, char *file, t_enum type)
{
	if (access(file, F_OK) && type == INFILE)
	{
		ft_putstr_fd("minishell : ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		data->err = 1;
		data->exit_status = 1;
		return (0);
	}
	if (!access(file, R_OK) && type == INFILE)
		return (1);
	if (((!access(file, W_OK) && !access(file, F_OK)) || (access(file, W_OK)
				&& access(file, F_OK))) && type == OUTFILE)
		return (1);
	ft_putstr_fd("minishell : ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": Permission denied\n", 2);
	data->err = 1;
	data->exit_status = 1;
	return (0);
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
		return (failed_mess(data, INVALID_NEXT_REDIR, 2), -1);
	if (token->next->type == INFILE || token->next->type == OUTFILE)
	{
		if (!is_file_exist(data, token->next->value, token->next->type))
			return (-1);
		fd = open(token->next->value, oflag, 0644);
		if (fd < 0)
			return (failed_mess(data, "open failed", 2), -1);
		return (fd);
	}
	return (-1);
}

void	open_file(t_data *data, t_token *tok)
{
	t_token	*tmp;

	data->redir->infile = -1;
	data->redir->outfile = -1;
	tmp = tok;
	while (tmp)
	{
		if (tmp->type == PIPE || !tmp || g_signal_received == 3
			|| (data->err && data->exit_status != 1))
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
	if (data->err && data->exit_status != 1)
		return (NULL);
	return (tok);
}
