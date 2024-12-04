/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:54:11 by saberton          #+#    #+#             */
/*   Updated: 2024/12/04 17:57:19 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_change_word_to_cmd(t_data *data)
{
	t_token	*tmp;

	tmp = data->token;
	if (!tmp->next)
		return ;
	while (tmp->next)
	{
		if (tmp->type == PIPE)
			tmp->next->type = CMD;
		if (tmp->next->type == APPEND || tmp->next->type == INFILE
			|| tmp->next->type == HEREDOC || tmp->next->type == OUTFILE)
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
		if (tmp->type == CMD && is_builtins(data) != 1)
		{
			exist = valid_cmd(data, tmp->value);
			if (!exist)
				return (perror("malloc failed"), exit_prog(data, 12));
			if (!*exist)
			{
				free(exist);
				exist = ft_strdup(tmp->value);
				if (!exist)
					return (perror("malloc failed"), exit_prog(data, 12));
			}
			cmd = recup_cmd(data, tmp);
			if (access(exist, F_OK | X_OK) != 0)
			{
				free(exist);
				ft_putstr_fd(tmp->value, 2);
				ft_putstr_fd(": command not found\n", 2);
				data->err_quote = 1;
				ft_free_tab(cmd);
				return ;
			}
			ft_free_tab(cmd);
			free(exist);
		}
		tmp = tmp->next;
	}
	return ;
}
