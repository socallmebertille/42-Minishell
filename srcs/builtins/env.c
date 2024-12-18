/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:15:36 by saberton          #+#    #+#             */
/*   Updated: 2024/12/18 09:05:22 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_env(t_data *data, int fd)
{
	t_env	*tmp;

	tmp = data->cpy_env;
	while (tmp)
	{
		write_str_fd(data, "env", tmp->type, fd);
		write_str_fd(data, "env", "=", fd);
		write_str_fd(data, "env", tmp->value, fd);
		write_str_fd(data, "env", "\n", fd);
		tmp = tmp->next;
	}
}

void	handle_env(t_data *data, t_token *tok, int fd_out)
{
	if (tok->next && tok->next->type == WORD)
		return (data->exit_status += 1, ft_putstr_fd(INVALID_ARG_ENV, 2));
	else
		return (print_env(data, fd_out));
}
