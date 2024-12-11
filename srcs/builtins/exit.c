/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kepouliq <kepouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:09:38 by kepouliq          #+#    #+#             */
/*   Updated: 2024/12/11 17:54:09 by kepouliq         ###   ########.fr       */
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

static void	check_overflow(t_data *data, char *nb)
{
	int                    i;
    int                    sign;
    unsigned long long    result;
    unsigned long long    limit;

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
        if ((sign == 1 && result > (unsigned long long)LLONG_MAX) ||
            (sign == -1 && result > limit))
        {
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(nb, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit_prog(data, 2);
		}
    }
}

void	handle_exit(t_data *data, t_token *tok, int fd_out)
{
	if (tok->next)
		check_overflow(data, tok->next->value);
	if (tok->next && tok->next->next)
	{
		if (!only_numeric(tok->next->value))
			return (ft_putstr_fd("minishell: exit: too many arguments\n", 2));
		return (exit_num_arg_required(data, tok));
	}
	if (tok->next)
	{
		exit_with_exit_code(data, tok);
	}
	if (!tok->next)
	{
		ft_putstr_fd("exit\n", fd_out);
		exit_prog(data, 0);
	}
}
