/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:09:38 by kepouliq          #+#    #+#             */
/*   Updated: 2024/12/18 09:06:13 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	only_numeric(char *code)
{
	int	i;

	i = 0;
	if (code[i] == '-' || code[i] == '+')
		i++;
	while (code[i])
	{
		if (!ft_isdigit(code[i]))
			return (2);
		i++;
	}
	return (0);
}

static void	exit_with_exit_code(t_data *data, t_token *tok)
{
	int	exit_code;

	exit_code = 0;
	if (!only_numeric(tok->next->value))
	{
		exit_code = ft_atoi(tok->next->value);
		ft_putstr_fd("exit\n", 2);
		exit_prog(data, exit_code);
	}
}

static void	exit_num_arg_required(t_data *data, t_token *tok)
{
	ft_putstr_fd("exit\nminishell: exit: ", 2);
	ft_putstr_fd(tok->next->value, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	exit_prog(data, 2);
}

static int	check_overflow(char *nb)
{
	int					i;
	int					sign;
	unsigned long long	result;
	unsigned long long	limit;

	i = 0;
	sign = 1;
	result = 0;
	limit = (unsigned long long)LLONG_MAX + 1;
	while (nb[i] == ' ' || (nb[i] >= 9 && nb[i] <= 13))
		i++;
	if (nb[i] == '+' || nb[i] == '-')
		if (nb[i++] == '-')
			sign = -1;
	while (nb[i] >= '0' && nb[i] <= '9')
	{
		result = result * 10 + (nb[i++] - '0');
		if ((sign == 1 && result > (unsigned long long)LLONG_MAX) || (sign == -1
				&& result > limit))
			return (1);
	}
	return (0);
}

void	handle_exit(t_data *data, t_token *tok, int fd_out)
{
	if (tok->next)
	{
		if (check_overflow(tok->next->value))
		{
			ft_putstr_fd("exit\nminishell: exit: ", 2);
			ft_putstr_fd(tok->next->value, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit_prog(data, 2);
		}
	}
	if (tok->next && tok->next->next)
	{
		if (!only_numeric(tok->next->value))
			return (data->exit_status = 1,
				ft_putstr_fd("minishell: exit: too many arguments\n", 2));
		return (exit_num_arg_required(data, tok));
	}
	if (tok->next)
		exit_with_exit_code(data, tok);
	if (!tok->next)
	{
		write_str_fd(data, "exit", "exit\n", fd_out);
		exit_prog(data, 0);
	}
}
