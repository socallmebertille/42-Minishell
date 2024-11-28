/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kepouliq <kepouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:51:15 by kepouliq          #+#    #+#             */
/*   Updated: 2024/11/28 19:06:28 by kepouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_syntax_export(char *value, t_data *data)
{
	int	i;
	int	digit;

	i = 0;
	digit = 0;
	while (value[i])
	{
		if (ft_isdigit(value[i]))
			digit++;
		i++;
		if (value[i - 1] == '=')
			break ;
	}
	if (digit == i)
		return (ft_putstr_fd("minishell: export: `", 2), ft_putstr_fd(value, 2),
			ft_putstr_fd("': not a valid identifier\n", 2), 0);
	add_cpy_env(ft_substr(value, 0, i), NULL, &data->cpy_env2, data);
	if (value[i - 1] == '=')
		return (i);
	return (0);
}

static void	modif_env_node(t_data *data, char *value, int j)
{
	int		i;
	t_env	*tmp;

	tmp = data->cpy_env;
	i = check_syntax_export(value, data);
	if (!i)
		return ;
	while (j > 0)
	{
		tmp = tmp->next;
		j--;
	}
	free(tmp->value);
	tmp->value = ft_substr(value, i, ft_strlen(value));
}
static void	add_env_node(t_data *data, char *value)
{
	int	i;

	(void)data;
	i = check_syntax_export(value, data);
	if (!i)
		return ;
	add_cpy_env(ft_substr(value, 0, i - 1), ft_substr(value, i,
			ft_strlen(value)), &data->cpy_env, data);
}

static int	find_if_env_exist(t_env *env, char *value)
{
	t_env	*tmp;
	char	*sub;
	int		i;

	tmp = env;
	i = 0;
	while (tmp)
	{
		sub = ft_strjoin(tmp->type, "=");
		if (!ft_strncmp(sub, value, ft_strlen(sub)))
			return (free(sub), i);
		i++;
		free(sub);
		tmp = tmp->next;
	}
	return (-1);
}

static t_env	*sort_list(t_env *env, int (*cmp)(const char *, const char *), t_data *data)
{
	char	*temp;
	t_env	*tmp;
    t_env   *cpy;

	tmp = env;
    while (tmp)
    {
        add_cpy_env(tmp->type, tmp->value, &data->cpy_env2, data);
        // if (!data->cpy_env2)
        // {
        //     data->cpy_env2 = tmp;
        //     data->cpy_env = data->cpy_env2;
        // }
        tmp = tmp->next;
    }
    cpy = data->cpy_env2;
	while (cpy && cpy->next)
	{
		if (cmp(cpy->type, cpy->next->type) > 0)
		{
			temp = cpy->type;
			cpy->type = cpy->next->type;
			cpy->next->type = temp;
			cpy = tmp;
		}
		else
			cpy = cpy->next;
	}
	return (cpy);
}

static void	display_export_order(t_data *data)
{
	t_env	*sort_tmp;

	sort_tmp = data->cpy_env2;
	while (sort_tmp)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(sort_tmp->type, 1);
		if (sort_tmp->value)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(sort_tmp->value, 1);
			ft_putstr_fd("\"", 1);
		}
        ft_putstr_fd("\n", 1);
		sort_tmp = sort_tmp->next;
	}
}

void	handle_export(t_data *data)
{
	t_token *tmp_tok;
	int exist;

	exist = 0;
	tmp_tok = data->token->next;
	if (!data->cpy_env2)
		data->cpy_env2 = sort_list(data->cpy_env, ft_strcmp, data);
	if (!tmp_tok)
		return (display_export_order(data));
	if (tmp_tok->value[0] == '\0')
		return (ft_putstr_fd("minishell: export: `': not a valid identifier\n",
				2));
	while (tmp_tok && tmp_tok->type == WORD)
	{
		if (tmp_tok->value)
			exist = find_if_env_exist(data->cpy_env, tmp_tok->value);
		if (exist != -1)
			modif_env_node(data, tmp_tok->value, exist);
		else
			add_env_node(data, tmp_tok->value);
		tmp_tok = tmp_tok->next;
	}
}