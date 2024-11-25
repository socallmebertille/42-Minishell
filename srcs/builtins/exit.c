/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kepouliq <kepouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:09:38 by kepouliq          #+#    #+#             */
/*   Updated: 2024/11/25 19:05:24 by kepouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	only_numeric(char *code)
// {
// 	int	i;
// 	int	n;

// 	i = 0;
// 	n = 0;
// 	if (code[i] == '-' || code[i] == '+')
// 		i++;
// 	if (code[0] == '-')
// 		n = 1;
// 	while (code[i])
// 	{
// 		if (!ft_isdigit(code[i]))
// 			return (2);
// 		i++;
// 	}
// 	return (0);
// }

// static void exit_with_exit_code(t_data *data)
// {
//     int exit_code;
    
//     exit_code = 0;
//     if(only_numeric(data->token->next->value))
//     {
//         exit_code = ft_atoi(data->token->next->value);
//         write(0, "exit\n", 6);
//         exit_prog(data, exit_code);
//     }
// }

void handle_exit(t_data *data)
{
    // if(data->token->next || data->token->next->next)
    // {
    //     //gerer avec trop d'arguments, message different si 
    //     //data->token->next numeric ou non
    // }
    // else if(data->token->next)
    // {
    //     exit_with_exit_code(data);
    //     printf("ici");
    // }
    if (!data->token->next)
    {
        write(0, "exit\n", 6);
        exit_prog(data, 0);
    }
}