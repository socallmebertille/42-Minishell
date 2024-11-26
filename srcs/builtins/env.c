/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:15:36 by saberton          #+#    #+#             */
/*   Updated: 2024/11/26 18:48:18 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void error_env(char *str)
{
    ft_putstr_fd("env: ‘", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("’: No such file or directory\n", 2);
}


static void print_env(t_data *data)
{
    t_env   *tmp;

    tmp = data->cpy_env;
    while (tmp)
    {
        ft_putstr_fd(tmp->type, 1);
        ft_putstr_fd("=", 1);
        ft_putstr_fd(tmp->value, 1);
        ft_putstr_fd("\n", 1);
        tmp = tmp->next;
    }
}

static void check_only_env(t_data *data)
{
    t_token *tmp;
    int err;
    
    err = 0;
    tmp = data->token;
    while (tmp)
    {
        if (ft_strcmp(tmp->value, "env") != 0)
        {
            err = 1;
            break;
        }
        tmp = tmp->next;
    }
    if (err == 0)
        print_env(data);
    else
        error_env(tmp->value);
}

void    handle_env(t_data *data)
{
    if(!data->token->next)
        print_env(data);
    else
        check_only_env(data);
}
