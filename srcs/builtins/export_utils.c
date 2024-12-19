/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 14:08:13 by saberton          #+#    #+#             */
/*   Updated: 2024/12/19 14:18:37 by saberton         ###   ########.fr       */
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

void	modif_env_node(t_data *data, char *value, int j)
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

void	add_env_node(t_data *data, char *value)
{
	int	i;

	(void)data;
	i = check_syntax_export(value, data);
	if (!i)
		return ;
	add_cpy_env(ft_substr(value, 0, i - 1), ft_substr(value, i,
			ft_strlen(value)), &data->cpy_env, data);
}

void	display_export_order(t_data *data, int fd_out)
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

int	is_valid_name(char *name)
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
