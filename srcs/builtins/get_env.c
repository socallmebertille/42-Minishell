/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:57:40 by bertille          #+#    #+#             */
/*   Updated: 2024/12/02 13:32:02 by saberton         ###   ########.fr       */
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

int	len_env(char **env)
{
	int	len;

	len = 0;
	while (env[len])
		len++;
	return (len);
}

void	get_env(char **env, t_data *data)
{
	int		i;
	int		j;
	t_env	*cpy_env;

	cpy_env = NULL;
	data->env = env;
	if (len_env(env) == 5) //(!env || !*env) // launch "env -i bash" then "env"
	{
		add_cpy_env(ft_strdup("PWD"), get_pwd(env), &cpy_env, data);
		add_cpy_env(ft_strdup("SHLVL"), ft_strdup("1"), &cpy_env, data);
		add_cpy_env(ft_strdup("_"), ft_strdup("chemin de last commande"),
			&cpy_env, data);
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
	return ;
}
