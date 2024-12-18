/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:56:18 by saberton          #+#    #+#             */
/*   Updated: 2024/12/18 09:07:49 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_append(t_token *tok)
{
	if (tok->type != APPEND)
		return (1);
	if (tok->next)
	{
		if (tok->type == APPEND && tok->next->type == APPEND)
			return (ft_putstr_fd(INVALID_DOUBLE_APPEND, 2), 2);
		else if (tok->type == APPEND && tok->next->type == REDIR_OUTFILE)
			return (ft_putstr_fd(INVALID_SIMPLE_APPEND, 2), 2);
	}
	return (1);
}

static int	check_heredoc(t_token *tok)
{
	if (tok->type != HEREDOC)
		return (1);
	if (tok->next)
	{
		if (tok->next->next)
		{
			if (tok->type == HEREDOC && tok->next->type == HEREDOC
				&& tok->next->next->type == HEREDOC)
				return (ft_putstr_fd(INVALID_TRIPLE_HEREDOC, 2), 2);
			else if (tok->type == HEREDOC && tok->next->type == HEREDOC
				&& tok->next->next->type == REDIR_INFILE)
				return (ft_putstr_fd(INVALID_DOUBLE_HEREDOC, 2), 2);
		}
		if (tok->type == HEREDOC && tok->next->type == HEREDOC)
			return (ft_putstr_fd(INVALID_SIMPLE_HEREDOC, 2), 2);
		if (tok->type == HEREDOC && tok->next->type == REDIR_INFILE)
			return (ft_putstr_fd(INVALID_SIMPLE_HEREDOC, 2), 2);
	}
	return (1);
}

int	good_syntaxe(t_data *data)
{
	t_token	*tmp;

	tmp = data->token;
	while (tmp)
	{
		if (!check_append(tmp) || !check_heredoc(tmp))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}
