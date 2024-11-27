/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kepouliq <kepouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:05:45 by kepouliq          #+#    #+#             */
/*   Updated: 2024/11/27 15:27:22 by kepouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	is_builtins(t_data *data)
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
	}		
}

void	parse(t_data *data)
{
	is_builtins(data);
}
