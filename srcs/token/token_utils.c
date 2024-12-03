/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:54:11 by saberton          #+#    #+#             */
/*   Updated: 2024/12/03 14:53:31 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_change_word_to_cmd(t_data *data)
{
	t_token	*tmp;

	tmp = data->token;
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

	tmp = data->token;
	while (tmp)
	{
		if (tmp->type == CMD)
		{
			exist = valid_cmd(data, tmp->value);
			if (!exist)
			{
				ft_putstr_fd(tmp->value, 2);
				ft_putstr_fd(": command not found\n", 2);
				data->err_quote = 1;
				return ;
			}
			free(exist);
		}
		tmp = tmp->next;
	}
	return ;
}
