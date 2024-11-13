/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertille <bertille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:57:40 by bertille          #+#    #+#             */
/*   Updated: 2024/11/13 20:21:15 by bertille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	**ft_addenv(char *type, char *value, t_env **env)
{
	t_env	*new;
	t_env	*node;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->type = type;
	new->value = value;
	new->next = NULL;
	if (!new || !*env)
		return (NULL);
	if (!*env)
		*env = new;
	else if (env && new)
	{
		node = *env;
		while (node)
			node = node->next;
		node->next = new;
	}
	return (env);
}

t_env	**get_env(char **env, t_env **cpy_env)
{
	int		i;
	int		j;

	i = 0;
	if (!env)
	{
		ft_addenv(ft_strdup("PWD"), ft_strdup("get_cwd()"), cpy_env);
		ft_addenv(ft_strdup("SHLVL"), ft_strdup("1"), cpy_env);
		ft_addenv(ft_strdup("_"), ft_strdup("chemin de last commande"), cpy_env);
		return (cpy_env);
	}
	while (env[i])
	{
		while (env[i][j] != '=')
			j++;
		ft_addenv(ft_substr(env[i], 0, j), ft_substr(env[i], j + 1, ft_strlen(env[i]) + j), cpy_env);
		i++;
	}
	return (cpy_env);
}
