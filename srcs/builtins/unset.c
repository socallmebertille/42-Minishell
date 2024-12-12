/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:58:20 by kepouliq          #+#    #+#             */
/*   Updated: 2024/12/04 16:07:31 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unset_env_node(t_env *delete, t_data *data)
{
	t_env	*start;

	start = data->cpy_env;
	if (delete == start)
	{
		data->cpy_env = data->cpy_env->next;
		free(delete->type);
		free(delete->value);
		free(delete);
		return ;
	}
	while (start->next != delete)
		start = start->next;
	start->next = start->next->next;
	free(delete->type);
	free(delete->value);
	free(delete);
}

static void	unset_export_node(t_env *delete, t_data *data)
{
	t_env	*start;

	start = data->cpy_env2;
	if (delete == start)
	{
		data->cpy_env2 = data->cpy_env2->next;
		free(delete->type);
		free(delete->value);
		free(delete);
		return ;
	}
	while (start->next != delete)
		start = start->next;
	start->next = start->next->next;
	free(delete->type);
	free(delete->value);
	free(delete);
}

static void	find_node_to_unset(t_env *env, t_data *data, char *value)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->type, value))
		{
			unset_env_node(tmp, data);
			break ;
		}
		tmp = tmp->next;
	}
}

static void	find_node_to_unset2(t_env *env, t_data *data, char *value)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->type, value))
		{
			unset_export_node(tmp, data);
			break ;
		}
		tmp = tmp->next;
	}
}

void	handle_unset(t_data *data, t_token *tok)
{
	t_token	*tmp_tok;

	tmp_tok = tok->next;
	while (tmp_tok && tmp_tok->type == WORD)
	{
		if (tmp_tok->value)
		{
			find_node_to_unset(data->cpy_env, data, tmp_tok->value);
			find_node_to_unset2(data->cpy_env2, data, tmp_tok->value);
		}
		tmp_tok = tmp_tok->next;
	}
}
