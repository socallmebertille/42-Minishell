/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:54:11 by saberton          #+#    #+#             */
/*   Updated: 2024/12/14 22:21:44 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*check_err_messages(t_data *data, t_token *tok, char *exist,
		int err)
{
	if (err == 2)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(tok->value, 2);
		ft_putstr_fd(": command not found\n", 2);
		tok->type = NOT_FOUND;
		data->exit_status = 127;
	}
	else if (err == 1)
	{
		if (!exist)
			return (failed_mess(data, "malloc failed", 1), NULL);
		if (exist[0] == '\0')
		{
			free(exist);
			exist = ft_strdup(tok->value);
			if (!exist)
				return (failed_mess(data, "malloc failed", 1), NULL);
		}
	}
	return (exist);
}

void	ft_change_word_to_type(t_data *data)
{
	t_token	*tmp;

	tmp = data->token;
	if (!tmp || !tmp->next)
		return ;
	while (tmp->next)
	{
		if (!is_builtins(tmp) && tmp->type == PIPE)
			tmp->next->type = CMD;
		if (tmp->type == REDIR_INFILE && tmp->next->type == WORD)
			tmp->next->type = INFILE;
		if (tmp->type == HEREDOC && tmp->next->type == WORD)
			tmp->next->type = DELIM;
		if ((tmp->type == REDIR_OUTFILE || tmp->type == APPEND) && tmp->next->type == WORD)
			tmp->next->type = OUTFILE;
		tmp = tmp->next;
	}
}

void	ft_check_access_cmd(t_data *data, int step)
{
	t_token	*tmp;
	char	*exist;
	char	**cmd;

	tmp = data->token;
	while (tmp)
	{
		if (((tmp->type == CMD && !is_builtins(tmp)) && step == 1)
			|| ((tmp->type == INFILE || tmp->type == OUTFILE) && step == 2))
		{
			exist = valid_cmd(data, tmp->value);
			exist = check_err_messages(data, tmp, exist, 1);
			if (!exist)
				return ;
			cmd = recup_cmd(data, tmp);
			if (access(exist, F_OK | X_OK) != 0)
				(void)check_err_messages(data, tmp, NULL, 2);
			ft_free_tab(cmd);
			free(exist);
		}
		tmp = tmp->next;
	}
	return ;
}
