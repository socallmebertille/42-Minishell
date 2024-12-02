/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:05:45 by kepouliq          #+#    #+#             */
/*   Updated: 2024/12/02 18:01:18 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_builtins(t_data *data)
{
	if (data->token && data->token->value != NULL)
	{
		if (ft_strcmp(data->token->value, "exit") == 0)
			handle_exit(data);
		else if (ft_strcmp(data->token->value, "env") == 0)
			handle_env(data);
		else if (ft_strcmp(data->token->value, "echo") == 0)
			handle_echo(data);
		else if (ft_strcmp(data->token->value, "pwd") == 0)
			handle_pwd(data);
		else if (ft_strcmp(data->token->value, "unset") == 0)
			handle_unset(data);
		else if (ft_strcmp(data->token->value, "export") == 0)
			handle_export(data);
		return (1);
	}
	return (0);
}

void	parse(t_data *data)
{
	if (!good_syntaxe(data))
		return ;
	else if (is_builtins(data))
		return ;
	// else if (is_cmd(data))
	// 	return ;
}
