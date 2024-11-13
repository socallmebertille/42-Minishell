/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertille <bertille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:42:36 by saberton          #+#    #+#             */
/*   Updated: 2024/11/13 20:23:25 by bertille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_env	*cpy_env;

	(void)av;
	if (ac != 1)
		return (1);
	signal_handlers();
	get_env(env, &cpy_env);//ft_bzero(cpy_env, sizeof(cpy_env)));
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			write(2, "exit\n", 5);
			rl_clear_history();
			exit(130);
		}
		if (*input)
			add_history(input);
		// 	parse(input);
		free(input);
	}
	rl_clear_history();
	return (0);
}
