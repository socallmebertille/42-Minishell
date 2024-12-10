/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:39:24 by kepouliq          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/12/10 19:38:40 by saberton         ###   ########.fr       */
=======
/*   Updated: 2024/12/10 15:40:09 by kepouliq         ###   ########.fr       */
>>>>>>> 760bd57 (cd not finish)
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

<<<<<<< HEAD
 static void	cd_go_home(t_data *data)
=======
void	change_old_env_pwd(t_data *data, char *path)
{
	t_env *tmp;

	tmp = data->cpy_env;
	while (tmp)
	{
		if (ft_strcmp(tmp->type, "OLDPWD") == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(path);
			break;
		}
		tmp = tmp->next;
	}
	
}

void	change_env_pwd(t_data *data)
{
	char *new_pwd;
	t_env *tmp;

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
			break;
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
	t_env	*tmp;

	tmp = data->cpy_env;
	while (tmp)
	{
		if (ft_strcmp(tmp->type, "HOME") == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	cd_go_home(t_data *data)
>>>>>>> 760bd57 (cd not finish)
{
	char	*home_path;

	home_path = get_home_env(data);
	change_old_env_pwd(data, get_actual_env_path(data));
	chdir(home_path);
	change_env_pwd(data);
}

<<<<<<< HEAD
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
=======
void	change_directory(t_data *data)
{
	if(access(data->token->next->value, F_OK) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(data->token->next->value, 2);
		ft_putstr_fd(": No such file or directory", 2);
	}
	else
	change_old_env_pwd(data, get_actual_env_path(data));
	chdir(data->token->next->value);
>>>>>>> 760bd57 (cd not finish)
	change_env_pwd(data);
}

void	handle_cd(t_data *data, int fd_out)
{
<<<<<<< HEAD
	if (ft_strcmp(data->token->value, "cd"))
		return ;
=======
>>>>>>> 760bd57 (cd not finish)
	ft_putstr_fd("Je suis dans mon buildtins\n", fd_out);
	if (!data->token->next || ft_strcmp(data->token->next->value, "~") == 0)
		cd_go_home(data);
	else if (data->token->next && data->token->next->next)
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
<<<<<<< HEAD
	else if (ft_strcmp(data->token->next->value, "-") == 0)
		go_old_pwd(data);
	else
		change_directory(data);
}
=======
	else
		change_directory(data);
}

// cd
// cd avec plus de un arg exit=1
// cd avec un chemin faux exit=1
// changement var env
>>>>>>> 760bd57 (cd not finish)
