/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:54:46 by saberton          #+#    #+#             */
/*   Updated: 2024/12/15 09:57:22 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_in_line(t_data *data)
{
	t_token	*tmp;
	int		nb_pipe;

	tmp = data->token;
	nb_pipe = 0;
	if (!tmp)
		return (0);
	while (tmp)
	{
		if (tmp->type == PIPE)
			nb_pipe++;
		tmp = tmp->next;
	}
	return (nb_pipe);
}

t_token	*recup_tok_after_pipe(t_token *tmp)
{
	while (tmp)
	{
		if (tmp->type == PIPE && tmp->next)
			return (tmp->next);
		tmp = tmp->next;
	}
	return (NULL);
}

static int	len_cmd(t_token *tok)
{
	t_token	*tmp;
	int		i;

	i = 1;
	tmp = tok->next;
	if (!tmp)
		return (i);
	while (tmp)
	{
		if (tmp->type != WORD)
			break ;
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**recup_cmd(t_data *data, t_token *tok)
{
	char	**cmd;
	t_token	*tmp;
	int		i;

	i = 1;
	(void)data;
	cmd = malloc(sizeof(char *) * (len_cmd(tok) + 1));
	cmd[0] = ft_strdup(tok->value);
	tmp = tok->next;
	if (!tmp || len_cmd(tok) == 1 || !cmd[0])
		return (cmd[i] = NULL, cmd);
	while (tmp)
	{
		if (tmp->type != WORD)
			break ;
		cmd[i] = ft_strdup(tmp->value);
		tmp = tmp->next;
		i++;
	}
	cmd[i] = NULL;
	return (cmd);
}
