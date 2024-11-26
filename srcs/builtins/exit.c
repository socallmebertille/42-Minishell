/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kepouliq <kepouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:09:38 by kepouliq          #+#    #+#             */
/*   Updated: 2024/11/26 17:01:17 by kepouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	only_numeric(char *code)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	if (code[i] == '-' || code[i] == '+')
		i++;
	if (code[0] == '-')
		n = 1;
	while (code[i])
	{
		if (!ft_isdigit(code[i]))
			return (2);
		i++;
	}
	return (0);
}

static void	exit_with_exit_code(t_data *data)
{
	int	exit_code;

	exit_code = 0;
	if (!only_numeric(data->token->next->value))
	{
		exit_code = ft_atoi(data->token->next->value);
		write(0, "exit\n", 6);
		exit_prog(data, exit_code);
	}
}

static void	exit_too_many_args(void)
{
	ft_putstr_fd("minishell: exit: too many arguments\n", 2);
}

static void	exit_num_arg_required(t_data *data)
{
	ft_putstr_fd("exit\nminishell: exit: ", 2);
	ft_putstr_fd(data->token->next->value, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	exit_prog(data, 2);
}

void	handle_exit(t_data *data)
{
	if (data->token->next && data->token->next->next)
	{
		if (!only_numeric(data->token->next->value))
			return (exit_too_many_args());
		return (exit_num_arg_required(data));
	}
	if (data->token->next)
	{
		printf("ici\n");
		exit_with_exit_code(data);
	}
	if (!data->token->next)
	{
		write(0, "exit\n", 6);
		exit_prog(data, 0);
	}
}
