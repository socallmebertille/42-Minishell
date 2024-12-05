/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:15:36 by saberton          #+#    #+#             */
/*   Updated: 2024/12/05 17:54:59 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	error_env(char *str)
{
	ft_putstr_fd("env: ‘", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("’: No such file or directory\n", 2);
}

static void	print_env(t_data *data, int fd)
{
	t_env	*tmp;

	tmp = data->cpy_env;
	while (tmp)
	{
		ft_putstr_fd(tmp->type, fd);
		ft_putstr_fd("=", fd);
		ft_putstr_fd(tmp->value, fd);
		ft_putstr_fd("\n", fd);
		tmp = tmp->next;
	}
}

static void	check_only_env(t_data *data, t_token *tok, int fd)
{
	t_token	*tmp;
	int		err;

	err = 0;
	tmp = tok;
	if (tmp->next->type == WORD)
		err = 1;
	if (err == 0)
		print_env(data, fd);
	else
		error_env(tmp->value);
}

void	handle_env(t_data *data, t_token *tok)
{
	int	fd;

	fd = 1;
	// if (data->pipe->nb_pipe > 0)
	// 	fd = data->pipe->pipe_fd[1];
	ft_putstr_fd("je suis DANS LE BUILTINS\n", 1);
	if (!tok->next)
		print_env(data, fd);
	else
		check_only_env(data, tok, fd);
}
