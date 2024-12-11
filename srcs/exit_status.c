/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kepouliq <kepouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:30:06 by saberton          #+#    #+#             */
/*   Updated: 2024/12/11 17:59:24 by kepouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	failed_mess(t_data *data, char *mess, int code)
{
    ft_putstr_fd(mess, 2);
	ft_putstr_fd("\n", 2);
	data->err = 1;
	data->exit_status = code;
}