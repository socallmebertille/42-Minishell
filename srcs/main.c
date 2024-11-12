/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:42:36 by saberton          #+#    #+#             */
/*   Updated: 2024/11/12 16:04:26 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char *input;
	printf("%d args for %s call\n", ac, av[0]);
	(void)env;
	while (1)
	{
		input = readline("minishell$");
		// if (ctrl + C)
		//     break ;
		if (!input)
			break ;
		if (*input)
			add_history(input);
		// printf("%s\n", input);
		// parse(input);
		free(input);
	}
	return (0);
}