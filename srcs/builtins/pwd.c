/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 17:35:01 by kepouliq          #+#    #+#             */
/*   Updated: 2024/12/18 19:11:27 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_flag(t_token *tok)
{
	if (tok->next && tok->next->type == WORD)
	{
		if (tok->next->value[0] == '-' && tok->next->value[1] == '\0')
			return (0);
		else if (tok->next->value[0] == '-' && tok->next->value[1] == '-'
			&& tok->next->value[2] == '\0')
			return (0);
		else if (tok->next->value[0] == '-')
			return (1);
	}
	return (0);
}

void	handle_pwd(t_data *data, t_token *tok, int fd_out)
{
	char	*pwd;

	if (tok->next && check_flag(tok))
	{
		ft_putstr_fd("minishell: pwd: ", fd_out);
		ft_putstr_fd(data->token->next->value, fd_out);
		ft_putstr_fd(" : invalid option \n", fd_out);
		return ;
	}
	pwd = getcwd(NULL, 0);
	if (pwd != NULL)
	{
		if (!data->err)
			write_str_fd(data, "pwd", pwd, fd_out);
		if (!data->err)
			write_str_fd(data, "pwd", "\n", fd_out);
		free(pwd);
	}
	else
		perror("getcwd malloc failed");
}
