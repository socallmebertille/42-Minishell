/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:05:45 by kepouliq          #+#    #+#             */
/*   Updated: 2024/11/26 18:17:54 by saberton         ###   ########.fr       */
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
	}
}

void	parse(t_data *data)
{
	is_builtins(data);
}
