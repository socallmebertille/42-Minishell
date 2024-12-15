/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 12:53:43 by kepouliq          #+#    #+#             */
/*   Updated: 2024/12/15 08:43:47 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_flag(const char *line)
{
	int	j;

	if (line[0] != '-' || line[1] != 'n')
		return (0);
	j = 1;
	while (line[j] == 'n')
		j++;
	if (line[j] == '\0')
		return (1);
	return (0);
}

static int	flag_detector(t_token *tok)
{
	t_token	*tmp;
	int		i;

	i = 1;
	tmp = tok->next;
	while (tmp && is_valid_flag(tmp->value))
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

void	handle_echo(t_token *tok, int fd_out)
{
	int		flag;
	int		flag_start;
	t_token	*tmp;

	tmp = tok;
	flag = flag_detector(tok);
	flag_start = flag;
	while (flag)
	{
		tmp = tmp->next;
		flag--;
	}
	while (tmp)
	{
		if (tmp->type != WORD || !tmp->value)
			break ;
		ft_putstr_fd(tmp->value, fd_out);
		if (tmp->next)
			ft_putstr_fd(" ", fd_out);
		tmp = tmp->next;
	}
	if (flag_start == 1)
		ft_putstr_fd("\n", fd_out);
}
