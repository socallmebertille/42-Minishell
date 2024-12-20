/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kepouliq <kepouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:56:18 by saberton          #+#    #+#             */
/*   Updated: 2024/12/20 15:55:49 by kepouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_next_ope(t_token *tok)
{
	if (tok->type == REDIR_INFILE && tok->next->type != INFILE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(tok->next->value, 2);
		ft_putstr_fd("'\n", 2);
		return (0);
	}
	if (tok->type == REDIR_OUTFILE && tok->next->type != OUTFILE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(tok->next->value, 2);
		ft_putstr_fd("'\n", 2);
		return (0);
	}
	if (tok->type == PIPE && (!tok->next || !tok->prev))
		return (ft_putstr_fd(PIPE_AFTER_PIPE, 2), 0);
	if (tok->type == PIPE
		&& (tok->next->type == PIPE || !ft_strcmp("|", tok->next->value)))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(tok->next->value, 2);
		ft_putstr_fd("'\n", 2);
		return (0);
	}
	return (1);
}

static int	check_append(t_token *tok)
{
	if (tok->type != APPEND)
		return (1);
	if (tok->type == APPEND && tok->next->type != OUTFILE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(tok->next->value, 2);
		ft_putstr_fd("'\n", 2);
		return (0);
	}
	if (tok->type == APPEND && tok->next->type == APPEND)
		return (ft_putstr_fd(INVALID_DOUBLE_APPEND, 2), 0);
	else if (tok->type == APPEND && tok->next->type == REDIR_OUTFILE)
		return (ft_putstr_fd(INVALID_SIMPLE_APPEND, 2), 0);
	return (1);
}

static int	check_heredoc(t_token *tok)
{
	if (tok->type != HEREDOC)
		return (1);
	if (tok->type == HEREDOC && tok->next->type != DELIM)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(tok->next->value, 2);
		ft_putstr_fd("'\n", 2);
		return (0);
	}
	if (tok->next->next)
	{
		if (tok->type == HEREDOC && tok->next->type == HEREDOC
			&& tok->next->next->type == HEREDOC)
			return (ft_putstr_fd(INVALID_TRIPLE_HEREDOC, 2), 0);
		else if (tok->type == HEREDOC && tok->next->type == HEREDOC
			&& tok->next->next->type == REDIR_INFILE)
			return (ft_putstr_fd(INVALID_DOUBLE_HEREDOC, 2), 0);
	}
	if (tok->type == HEREDOC && tok->next->type == HEREDOC)
		return (ft_putstr_fd(INVALID_SIMPLE_HEREDOC, 2), 0);
	if (tok->type == HEREDOC && tok->next->type == REDIR_INFILE)
		return (ft_putstr_fd(INVALID_SIMPLE_HEREDOC, 2), 0);
	return (1);
}

int	good_syntaxe(t_data *data)
{
	t_token	*tmp;

	tmp = data->token;
	while (tmp)
	{
		if ((tmp->type == HEREDOC || tmp->type == APPEND
				|| tmp->type == REDIR_INFILE || tmp->type == REDIR_OUTFILE)
			&& !tmp->next)
			return (ft_putstr_fd(INVALID_NEXT_REDIR, 2), data->exit_status = 2,
				data->err = 1, 0);
		if (!check_append(tmp) || !check_heredoc(tmp) || !check_next_ope(tmp))
			return (data->exit_status = 2, data->err = 1, 0);
		tmp = tmp->next;
	}
	return (1);
}
