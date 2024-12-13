/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:39:24 by kepouliq          #+#    #+#             */
/*   Updated: 2024/12/13 12:39:28 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_go_home(t_data *data)
{
	char	*home_path;

	home_path = get_home_env(data);
	change_old_env_pwd(data, get_actual_env_path(data));
	chdir(home_path);
	change_env_pwd(data);
}

void	change_directory(t_data *data)
{
	if (access(data->token->next->value, F_OK) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(data->token->next->value, 2);
		ft_putstr_fd(": No such file or directory", 2);
	}
	else
		change_old_env_pwd(data, get_actual_env_path(data));
	chdir(data->token->next->value);
	change_env_pwd(data);
}

void	handle_cd(t_data *data, int fd_out)
{
	ft_putstr_fd("Je suis dans mon buildtins\n", fd_out);
	if (!data->token->next || ft_strcmp(data->token->next->value, "~") == 0)
		cd_go_home(data);
	else if (data->token->next && data->token->next->next)
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
	else
		change_directory(data);
}

// cd
// cd avec plus de un arg exit=1
// cd avec un chemin faux exit=1
// changement var env