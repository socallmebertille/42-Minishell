/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:57:40 by bertille          #+#    #+#             */
/*   Updated: 2024/12/10 19:30:47 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*last_value(t_env *env)
{
	if (!env)
		return (NULL);
	while (env->next)
		env = env->next;
	return (env);
}

void	add_cpy_env(char *type, char *value, t_env **env, t_data *data)
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
			data->cpy_env = *env;
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
	t_env	*env;
	int		lvl;

	env = data->cpy_env;
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
				// data->env = ft_itoa(lvl);
				break ;
			}
			i++;
		}
		// return ;
	}
	while (env)
	{
		if (!ft_strcmp(env->type, "SHLVL"))
		{
			if (!lvl)
				lvl = ft_atol(env->value) + 1;
			free(env->value);
			env->value = ft_strdup(ft_itoa(lvl));
			break ;
		}
		env = env->next;
	}
	return ;
}

void	get_env(char **env, t_data *data)
{
	int		i;
	int		j;
	t_env	*cpy_env;

	cpy_env = NULL;
	data->env = env;
	if (!*env)
	{
		add_cpy_env(ft_strdup("PWD"), getcwd(NULL, 0), &cpy_env, data);
		add_cpy_env(ft_strdup("SHLVL"), ft_strdup("1"), &cpy_env, data);
		add_cpy_env(ft_strdup("_"), ft_strdup("chemin de last commande"),
			&cpy_env, data);
		get_shlvl(data);
		return ;
	}
	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] != '=')
			j++;
		add_cpy_env(ft_substr(env[i], 0, j), ft_substr(env[i], j + 1,
				ft_strlen(env[i])), &cpy_env, data);
		i++;
	}
	get_shlvl(data);
	return ;
}
