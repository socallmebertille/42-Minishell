/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 17:50:46 by saberton          #+#    #+#             */
/*   Updated: 2024/12/18 09:03:29 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_char_fd(t_data *data, char *str_err, char c, int fd)
{
	if (fd > -1 && !data->err)
	{
		if (write(fd, &c, 1) == -1)
		{
            write_str_fd(data, str_err, str_err, 2);
            write_str_fd(data, str_err, ": write error : no space left on device\n", 2);
			data->err = 1;
			return ;
		}
	}
}

void	write_str_fd(t_data *data, char *str_err, char *s, int fd)
{
	if (!s && !data->err)
		return ;
	while (*s)
	{
		write_char_fd(data, str_err, *s++, fd);
		if (data->err)
			return ;
	}
}