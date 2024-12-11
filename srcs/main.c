/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:42:36 by saberton          #+#    #+#             */
/*   Updated: 2024/12/11 20:49:48 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	loop(t_data *data)
{
	while (1)
	{
		data->line = readline("minishell$ ");
		if (!data->line)
			exit_prog(data, 130);
		clean_line(data->line, data);
		if (*data->line)
			add_history(data->line);
		tokenize(data->line, data);
		if (!data->err_quote && !data->err)
			parse(data);
		printf("my final exit status %d\n", data->exit_status);
		data->err_quote = 0;
		data->exit_status = 0;
		data->err = 0;
		free_tok(data);
		data->token = NULL;
		free(data->line);
	}
}

void	exit_prog(t_data *data, int code)
{
	free_env(data, data->cpy_env, 1);
	free_env(data, data->cpy_env2, 2);
	free_tok(data);
	if (code == 130)
		write(2, "exit\n", 5);
	rl_clear_history();
	exit(code);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void) av;
	if (ac != 1)
		return (1);
	ft_bzero(&data, sizeof(t_data));
	signal_handlers();
	get_env(env, &data);
	data.pipe = NULL;
	loop(&data);
	rl_clear_history();
	return (0);
}
