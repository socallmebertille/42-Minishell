/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kepouliq <kepouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:25:39 by kepouliq          #+#    #+#             */
/*   Updated: 2024/12/10 17:26:24 by kepouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_old_env_pwd(t_data *data, char *path)
{
	t_env	*tmp;

	tmp = data->cpy_env;
	while (tmp)
	{
		if (ft_strcmp(tmp->type, "OLDPWD") == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(path);
			break ;
		}
		tmp = tmp->next;
	}
}

void	change_env_pwd(t_data *data)
{
	char	*new_pwd;
	t_env	*tmp;

	new_pwd = NULL;
	tmp = data->cpy_env;
	while (tmp)
	{
		if (ft_strcmp(tmp->type, "PWD") == 0)
		{
			new_pwd = getcwd(NULL, 0);
			free(tmp->value);
			tmp->value = ft_strdup(new_pwd);
			free(new_pwd);
			break ;
		}
		tmp = tmp->next;
	}
}

char	*get_actual_env_path(t_data *data)
{
	t_env	*tmp;

	tmp = data->cpy_env;
	while (tmp)
	{
		if (ft_strcmp(tmp->type, "PWD") == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*get_home_env(t_data *data)
{
	t_env *tmp;

	tmp = data->cpy_env;
	while (tmp)
	{
		if (ft_strcmp(tmp->type, "HOME") == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}
