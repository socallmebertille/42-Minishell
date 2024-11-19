/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:42:36 by saberton          #+#    #+#             */
/*   Updated: 2024/11/19 15:36:59 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		// printf("%s = %s\n", env->type, env->value);
		free(env->type);
		free(env->value);
		free(env);
		env = tmp;
	}
}

void	exit_prog(t_data *data, int code)
{
	free_env(data->cpy_env);
	if (code == 130)
		write(2, "exit\n", 5);
	rl_clear_history();
	exit(code);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void)av;
	if (ac != 1)
		return (1);
	ft_bzero(&data, sizeof(t_data));
	signal_handlers();
	get_env(env, &data);
	while (1)
	{
		data.line = readline(MAGENTA "minishell$ " RESET);
		if (!data.line)
			exit_prog(&data, 130);
		if (*data.line)
			add_history(data.line);
		// ft_strtok(data->line);
		// 	parse(data->line);
		free(data.line);
	}
	rl_clear_history();
	return (0);
}
