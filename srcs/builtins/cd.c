/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:39:24 by kepouliq          #+#    #+#             */
/*   Updated: 2024/12/15 08:43:44 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cd_go_home(t_data *data)
{
	char	*home_path;

	home_path = get_home_env(data);
	change_old_env_pwd(data, get_actual_env_path(data));
	chdir(home_path);
	change_env_pwd(data);
}

static void	handle_cd_dash(t_data *data, int fd_out)
{
	char	*new_path;
	t_env	*tmp;

	tmp = data->cpy_env;
	new_path = NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->type, "OLDPWD") == 0)
		{
			new_path = ft_strdup(tmp->value);
			break ;
		}
		tmp = tmp->next;
	}
	change_old_env_pwd(data, get_actual_env_path(data));
	chdir(new_path);
	change_env_pwd(data);
	ft_putstr_fd(new_path, fd_out);
	ft_putstr_fd("\n", fd_out);
	free(new_path);
}

void	change_directory(t_data *data, int fd_out)
{
	if (access(data->token->next->value, F_OK) == -1
		&& ft_strcmp(data->token->next->value, "-"))
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(data->token->next->value, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		data->exit_status += 1;
		return ;
	}
	else if (!ft_strcmp(data->token->next->value, "-"))
		handle_cd_dash(data, fd_out);
	else
		change_old_env_pwd(data, get_actual_env_path(data));
	chdir(data->token->next->value);
	change_env_pwd(data);
}

void	handle_cd(t_data *data, int fd_out)
{
	if (!data->token->next || ft_strcmp(data->token->next->value, "~") == 0)
		cd_go_home(data);
	else if (data->token->next && data->token->next->next)
		return (data->exit_status += 1, ft_putstr_fd(INVALID_ARG_CD, 2));
	else
		return (change_directory(data, fd_out));
}

// cd
// cd avec plus de un arg exit=1
// cd avec un chemin faux exit=1
// changement var env