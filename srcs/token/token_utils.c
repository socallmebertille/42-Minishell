/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:54:11 by saberton          #+#    #+#             */
/*   Updated: 2024/12/10 12:46:21 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	err_messages(t_data *data, t_token *tok, char *exist, int err)
{
	if (err == 2)	
	{
		ft_putstr_fd(tok->value, 2);
		ft_putstr_fd(": command not found\n", 2);
		data->err_quote = 1;
	}
	else if (err == 12)
	{
		if (!exist)
			return (perror("malloc failed"), exit_prog(data, 12));
		// re display une newline au lieu de exit prog
	}
}

void	ft_change_word_to_cmd(t_data *data)
{
	t_token	*tmp;

	tmp = data->token;
	if (!tmp->next)
		return ;
	while (tmp->next)
	{
		if (!is_builtins(tmp) && tmp->type == PIPE)
			tmp->next->type = CMD;
		if (!is_builtins(tmp) && (tmp->next->type == APPEND
				|| tmp->next->type == INFILE || tmp->next->type == HEREDOC
				|| tmp->next->type == OUTFILE))
			tmp->type = CMD;
		tmp = tmp->next;
	}
}

void	ft_check_access_cmd(t_data *data)
{
	t_token	*tmp;
	char	*exist;
	char	**cmd;

	tmp = data->token;
	while (tmp)
	{
		if (tmp->type == CMD && !is_builtins(tmp))
		{
			exist = valid_cmd(data, tmp->value);
			err_messages(data, tmp, exist, 12);
			if (!*exist)
			{
				free(exist);
				exist = ft_strdup(tmp->value);
				return (err_messages(data, tmp, exist, 12));
			}
			cmd = recup_cmd(data, tmp);
			if (access(exist, F_OK | X_OK) != 0)
				return (free(exist), ft_free_tab(cmd), err_messages(data, tmp, NULL, 2)) ;
			ft_free_tab(cmd);
			free(exist);
		}
		tmp = tmp->next;
	}
	return ;
}
