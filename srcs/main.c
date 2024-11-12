/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:42:36 by saberton          #+#    #+#             */
/*   Updated: 2024/11/12 18:53:57 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char *input;
	(void)ac;
	(void)av;
	(void)env;
	while (1)
	{
		
		input = readline("minishell$ ");
		if (*input)
			add_history(input);
		// printf("%s\n", input);
		// if (input)
		// 	parse(input);
		// free(input);
		
	}	
	return (0);
}