/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:30:06 by saberton          #+#    #+#             */
/*   Updated: 2024/12/11 13:46:19 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	malloc_failed_mess(t_data *data)
{
	ft_putstr_fd("malloc failed\n", 2);
	data->err = 1;
	data->exit_status = 1;
}

void	dup2_failed_mess(t_data *data)
{
	ft_putstr_fd("malloc failed\n", 2);
	data->err = 1;
	data->exit_status = 12;
}

void	failed_mess(t_data *data, char *mess, int code)
{
    ft_putstr_fd(mess, 2);
	ft_putstr_fd("\n", 2);
	data->err = 1;
	data->exit_status = code;
}