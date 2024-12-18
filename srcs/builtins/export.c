/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/12/18 19:31:22 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"

int	find_if_env_exist(t_env *env, char *value)
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

static void	display_export_order(t_data *data, int fd_out)
{
	t_env	*sort_tmp;

	sort_tmp = data->cpy_env2;
	while (sort_tmp)
	{
		write_str_fd(data, "export", "declare -x ", fd_out);
		write_str_fd(data, "export", sort_tmp->type, fd_out);
		if (sort_tmp->equal)
			write_str_fd(data, "export", "=\"", fd_out);
		if (sort_tmp->value)
			write_str_fd(data, "export", sort_tmp->value, fd_out);
		if (sort_tmp->equal)
			write_str_fd(data, "export", "\"", fd_out);
		write_str_fd(data, "export", "\n", fd_out);
		sort_tmp = sort_tmp->next;
	}
}

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

static int	is_valid_name(char *name)
{
	int	i;

	if (!name || (!ft_isalpha(name[0]) && name[0] != '_'))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		free(name);
		return (0);
	}
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(name, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			free(name);
			return (0);
		}
		i++;
	}
	free(name);
	return (1);
}

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

static int	is_valid_name(char *name)
{
	int	i;

	if (!name || (!ft_isalpha(name[0]) && name[0] != '_'))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		free(name);
		return (0);
	}
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(name, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			free(name);
			return (0);
		}
		i++;
	}
	free(name);
	return (1);
}

void	handle_export(t_data *data, t_token *tok, int fd_out)
{
	t_token	*tmp_tok;
	t_token *tmp_tiktok;
	t_token *tmp_tiktok;
	int		exist;

	exist = 0;
	tmp_tiktok = data->token->next;
	tmp_tiktok = data->token->next;
	tmp_tok = tok->next;
	if (!data->cpy_env2)
	{
		get_env2(data->env, data);
		data->cpy_env2 = sort_list(data->cpy_env2, ft_strcmp);
	}
	if (!tmp_tok)
		return (display_export_order(data, fd_out));
	if (tmp_tok->value[0] == '\0')
		return (ft_putstr_fd(INVALID_VAL_EXPORT, 2));
	while (tmp_tok && tmp_tok->type == WORD)
	{
		if (!is_valid_name(export_key(tmp_tiktok->value)))
		{
			tmp_tiktok = tmp_tok->next;
			tmp_tok = tmp_tok->next;
			continue; ;
		}
		tmp_tiktok = tmp_tok->next;
		if (!is_valid_name(export_key(tmp_tiktok->value)))
		{
			tmp_tiktok = tmp_tok->next;
			tmp_tok = tmp_tok->next;
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
