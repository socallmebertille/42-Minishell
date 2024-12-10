/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kepouliq <kepouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:39:24 by kepouliq          #+#    #+#             */
/*   Updated: 2024/12/10 17:27:08 by kepouliq         ###   ########.fr       */
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

static void	change_directory(t_data *data)
{
	char	*old_pwd;

	old_pwd = get_actual_env_path(data);
	if (chdir(data->token->next->value))
	{
		if (!access(data->token->next->value, F_OK))
		{
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(data->token->next->value, 2);
			ft_putstr_fd(": Not a directory\n", 2);
			return ;
		}
		else
		{
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(data->token->next->value, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			return ;
		}
	}
	change_old_env_pwd(data, old_pwd);
	change_env_pwd(data);
}

static void	go_old_pwd(t_data *data)
{
	t_env	*tmp;
	char	*old_pwd;

	tmp = data->cpy_env;
	old_pwd = get_actual_env_path(data);
	while (tmp)
	{
		if (ft_strcmp(tmp->type, "OLDPWD") == 0)
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 1);
		return ;
	}
	ft_putstr_fd(tmp->value, 1);
	ft_putstr_fd("\n", 1);
	chdir(tmp->value);
	change_old_env_pwd(data, old_pwd);
	change_env_pwd(data);
}

void	handle_cd(t_data *data, int fd_out)
{
	if (ft_strcmp(data->token->value, "cd"))
		return ;
	ft_putstr_fd("Je suis dans mon buildtins\n", fd_out);
	if (!data->token->next || ft_strcmp(data->token->next->value, "~") == 0)
		cd_go_home(data);
	else if (data->token->next && data->token->next->next)
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
	else if (ft_strcmp(data->token->next->value, "-") == 0)
		go_old_pwd(data);
	else
		change_directory(data);
}
