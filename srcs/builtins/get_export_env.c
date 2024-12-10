/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_export_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 16:00:00 by kepouliq          #+#    #+#             */
/*   Updated: 2024/12/10 19:30:54 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_cpy_env2(char *type, char *value, t_env **env, t_data *data)
{
	t_env	*node;
	t_env	*new_last_node;

	new_last_node = (t_env *)malloc(sizeof(t_env));
	if (!new_last_node)
		return ;
	new_last_node->type = type;
	new_last_node->equal = '=';
	new_last_node->value = value;
	new_last_node->next = NULL;
	if (!*env)
	{
		*env = new_last_node;
		if (data != NULL)
			data->cpy_env2 = *env;
	}
	else
	{
		node = last_value(*env);
		node->next = new_last_node;
	}
	return ;
}

static void	get_shlvl(t_data *data)
{
	t_env	*export;
	int		lvl;

	export = data->cpy_env2;
	lvl = 0;
	if (data->env)
	{
		int i = 0;
		while (data->env[i])
		{
			if (!ft_strcmp(data->env[i], "SHLVL"))
			{
				if (!lvl)
					lvl = ft_atol(data->env[i] + 7) + 1;
				// data->env[i] + 7 = ft_itoa(lvl);
				break ;
			}
			i++;
		}
	}
	while (export)
	{
		// if (!ft_strcmp(export->type, "_") && !ft_strcmp(export->value, "./minishell"))
		// 	lvl = ft_atol(export->value) + 1;
		if (!ft_strcmp(export->type, "SHLVL"))
		{
			if (!lvl)
				lvl = ft_atol(export->value) + 1;
			free(export->value);
			export->value = ft_strdup(ft_itoa(lvl));
			break ;
		}
		export = export->next;
	}
	return ;
}

void	get_env2(char **env, t_data *data)
{
	int		i;
	int		j;
	t_env	*cpy_env2;

	cpy_env2 = NULL;
	data->env = env;
	if (!*env)
	{
		add_cpy_env2(ft_strdup("OLDPWD"), ft_strdup(""), &cpy_env2, data);
		add_cpy_env2(ft_strdup("PWD"), getcwd(NULL, 0), &cpy_env2, data);
		add_cpy_env2(ft_strdup("SHLVL"), ft_strdup("1"), &cpy_env2, data);
		get_shlvl(data);
		return ;
	}
	i = 0;
	while (env[i])
	{
		if (!(env[i][0] == '_' && env[i][1] == '='))
		{
			j = 0;
			while (env[i][j] != '=')
				j++;
			add_cpy_env2(ft_substr(env[i], 0, j), ft_substr(env[i], j + 1,
					ft_strlen(env[i])), &cpy_env2, data);
		}
		i++;
	}
	get_shlvl(data);
	return ;
}
