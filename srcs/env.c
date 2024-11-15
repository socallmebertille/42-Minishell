/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:57:40 by bertille          #+#    #+#             */
/*   Updated: 2024/11/15 12:39:57 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*last_value(t_env *env)
{
	if (!env)
		return (NULL);
	while (env->next)
		env = env->next;
	return (env);
}

t_env	**add_cpy_env(char *type, char *value, t_env **env)
{
	t_env	*new;
	t_env	*node;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->type = type;
	new->value = value;
	new->next = NULL;
	if (!new)
		return (NULL);
	if (!*env)
		*env = new;
	else if (*env)
	{
		node = last_value(*env);
		node->next = new;
	}
	return (env);
}

t_env	**get_env(char **env, t_env **cpy_env)
{
	int	i;
	int	j;

	ft_bzero(cpy_env, sizeof(t_env));
	if (!env) // launch "env -i bash" then "env"
	{
		add_cpy_env(ft_strdup("PWD"), ft_strdup("get_cwd()"), cpy_env);
		add_cpy_env(ft_strdup("SHLVL"), ft_strdup("1"), cpy_env);
		add_cpy_env(ft_strdup("_"), ft_strdup("chemin de last commande"),
			cpy_env);
		return (cpy_env);
	}
	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] != '=')
			j++;
		add_cpy_env(ft_substr(env[i], 0, j), ft_substr(env[i], j + 1,
				ft_strlen(env[i])), cpy_env);
		i++;
	}
	return (cpy_env);
}
