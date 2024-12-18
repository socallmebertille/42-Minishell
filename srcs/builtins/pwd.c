/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 17:35:01 by kepouliq          #+#    #+#             */
/*   Updated: 2024/12/18 09:01:31 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_pwd(t_data *data, int fd_out)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd != NULL)
	{
		if (!data->err)
			write_str_fd(data, "pwd", pwd, fd_out);
		if (!data->err)
			write_str_fd(data, "pwd", "\n", fd_out);
		free(pwd);
	}
	else
		perror("getcwd malloc failed");
}
