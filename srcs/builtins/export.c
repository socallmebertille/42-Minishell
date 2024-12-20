/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:51:15 by kepouliq          #+#    #+#             */
/*   Updated: 2024/12/20 17:14:42 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*export_key(char *arg)
{
	char	*equal;
	char	*key;

	if (arg[0] == '=')
		return (ft_strdup(arg));
	equal = ft_strchr(arg, '=');
	if (!equal)
		key = ft_strdup(arg);
	else
		key = ft_substr(arg, 0, equal - arg);
	return (key);
}

static int	point_dexclamation(t_data *data)
{
	t_token	*tmp;
	int		i;
	char	*error_mess;

	error_mess = NULL;
	tmp = data->token->next;
	while (tmp)
	{
		i = 0;
		while (tmp->value[i])
		{
			if (tmp->value[i] == '!' && tmp->value[i + 1])
			{
				ft_putstr_fd("minishell: ", 2);
				error_mess = ft_substr(tmp->value, i, ft_strlen(tmp->value));
				ft_putstr_fd(error_mess, 2);
				ft_putstr_fd(": event not found\n", 2);
				free(error_mess);
				return (1);
			}
			i++;
		}
		tmp = tmp->next;
	}
	return (0);
}

static int	simple_export(t_data *data, t_token *tmp_tok, int fd_out)
{
	if (!tmp_tok)
		return (display_export_order(data, fd_out), 1);
	if (tmp_tok->value[0] == '\0')
		return (ft_putstr_fd(INVALID_VAL_EXPORT, 2), 0);
	return (1);
}

static void	get_export(t_data *data, t_token *tmp_tok, t_token *tmp_tiktok,
		int exist)
{
	while (tmp_tok && tmp_tok->type == WORD)
	{
		if (point_dexclamation(data))
			return ;
		if (point_dexclamation(data))
			return ;
		if (!is_valid_name(export_key(tmp_tiktok->value)))
		{
			tmp_tiktok = tmp_tok->next;
			tmp_tok = tmp_tok->next;
			continue ;
			continue ;
		}
		tmp_tiktok = tmp_tok->next;
		if (tmp_tok->value)
			exist = find_if_env_exist(data->cpy_env, tmp_tok->value);
		if (exist != -1)
			modif_env_node(data, tmp_tok->value, exist);
		else
			add_env_node(data, tmp_tok->value);
		modif_export(data, tmp_tok->value);
		tmp_tok = tmp_tok->next;
	}
}

void	handle_export(t_data *data, t_token *tok, int fd_out)
{
	t_token	*tmp_tok;
	t_token	*tmp_tiktok;
	int		exist;

	exist = 0;
	tmp_tiktok = tok->next;
	tmp_tok = tok->next;
	if (!data->cpy_env2)
	{
		get_env2(data->env, data);
		data->cpy_env2 = sort_list(data->cpy_env2, ft_strcmp);
	}
	if (!simple_export(data, tmp_tok, fd_out))
		return ;
	get_export(data, tmp_tok, tmp_tiktok, exist);
}
