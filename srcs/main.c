/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kepouliq <kepouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:42:36 by saberton          #+#    #+#             */
/*   Updated: 2024/11/15 14:57:56 by kepouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_prog(t_env *env, int code)
{
	t_env	*tmp;
	
	tmp = env->next;
	while(tmp)
	{
		printf("%s = %s\n", env->type, env->value);
		tmp = env->next;
		free(env->type);
		free(env->value);
		free(env);
		env = tmp;
	}
	if (code == 130)
		write(2, "exit\n", 5);
	rl_clear_history();
	exit(code);
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_env	*cpy_env;

	(void)av;
	if (ac != 1)
		return (1);
	signal_handlers();
	get_env(env, &cpy_env);
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			exit_prog(cpy_env, 130);
		if (*input)
			add_history(input);
		// 	parse(input);
		free(input);
	}
	rl_clear_history();
	return (0);
}
