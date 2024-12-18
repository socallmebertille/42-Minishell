/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:09:38 by kepouliq          #+#    #+#             */
/*   Updated: 2024/12/18 16:19:28 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_longlong(const char *str)
{
	int					i;
	int					sign;
	unsigned long long	result;
	unsigned long long	limit;

	i = 0;
	sign = 1;
	result = 0;
	limit = (unsigned long long)LLONG_MAX + 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i++] - '0');
		if ((sign == 1 && result > (unsigned long long)LLONG_MAX)
			|| (sign == -1 && result > limit))
			return (EXIT_FAILURE);
	}
	if (str[i] != '\0')
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static void	exit_numeric_error(t_token *tok, t_data *data)
{
	ft_putstr_fd("exit\n", STDERR_FILENO);
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(tok->next->value, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	exit_prog(data, ft_atoi("2"));
}

static int	handle_too_many_args(t_data *data)
{
	ft_putstr_fd("exit\n", STDERR_FILENO);
	ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
	return (data->exit_status = 1);
}

void	handle_exit(t_data *data, t_token *tok, int fd_out)
{
	if (!tok->next)
	{
		ft_putstr_fd("exit\n", fd_out);
		exit_prog(data, EXIT_SUCCESS);
	}
	if (tok->next && is_valid_longlong(tok->next->value)
		&& !tok->next->next)
		exit_numeric_error(tok, data);
	if (tok->next && tok->next->next
		&& !is_valid_longlong(tok->next->value)
		&& !is_valid_longlong(tok->next->next->value))
	{
		handle_too_many_args(data);
		return ;
	}
	if (tok->next && tok->next->next)
		exit_numeric_error(tok, data);
	ft_putstr_fd("exit\n", fd_out);
	exit_prog(data, ft_atoi(tok->next->value));
}
