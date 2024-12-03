/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:17:17 by saberton          #+#    #+#             */
/*   Updated: 2024/12/03 14:38:41 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**recup_path(t_env *env)
{
	t_env	*tmp;
	char	*path;
	char	**path_file;

	tmp = env;
	path = NULL;
	while (tmp)
	{
		if (ft_strnstr(tmp->type, "PATH", 4))
		{
			path = ft_strdup(tmp->value + 5);
			if (!path)
				return (NULL);
			break ;
		}
		tmp = tmp->next;
	}
	if (ft_strlen(path) == 0 || path == NULL)
		path_file = ft_split(".", ':');
	else
	{
		path_file = ft_split(path, ':');
		free(path);
	}
	return (path_file);
}

char	*valid_cmd(t_data *data, char *cmd)
{
	char **path;
	char *cmd_path;
	char *sub;
	int i;

	i = 0;
	path = recup_path(data->cpy_env);
	if (!*path || !path)
		return (NULL);
	sub = ft_strjoin("/", cmd);
	if (!cmd || !sub)
		return (ft_free_tab(path), NULL);
	while (path[i] && path)
	{
		cmd_path = ft_strjoin(path[i], sub);
		if (!cmd_path)
			return (ft_free_tab(path), free(sub), NULL);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (ft_free_tab(path), free(sub), cmd_path);
		free(cmd_path);
		i++;
	}
	return (ft_free_tab(path), free(sub), ft_strdup(""));
}
