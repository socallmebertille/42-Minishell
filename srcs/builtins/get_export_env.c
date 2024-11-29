/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_export_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kepouliq <kepouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 16:00:00 by kepouliq          #+#    #+#             */
/*   Updated: 2024/11/29 17:14:42 by kepouliq         ###   ########.fr       */
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

void	get_env2(char **env, t_data *data)
{
	int		i;
	int		j;
	t_env	*cpy_env2;

	cpy_env2 = NULL;
	data->env = env;
	if (len_env(env) == 5) //(!env || !*env) // launch "env -i bash" then "env"
	{
		add_cpy_env2(ft_strdup("PWD"), ft_strdup("get_cwd()"), &cpy_env2, data);
		add_cpy_env2(ft_strdup("SHLVL"), ft_strdup("1"), &cpy_env2, data);
		add_cpy_env2(ft_strdup("_"), ft_strdup("chemin de last commande"),
			&cpy_env2, data);
		return ;
	}
	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] != '=')
			j++;
		add_cpy_env2(ft_substr(env[i], 0, j), ft_substr(env[i], j + 1,
				ft_strlen(env[i])), &cpy_env2, data);
		i++;
	}
	return ;
}
