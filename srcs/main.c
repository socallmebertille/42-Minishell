/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:42:36 by saberton          #+#    #+#             */
/*   Updated: 2024/12/05 16:12:24 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_tok(t_token *tok)
{
	t_token	*tmp;

	tmp = tok;
	while (tmp)
	{
		if (tmp->value)
		{
			free(tmp->value);
			tmp->value = NULL;
		}
		tok = tok->next;
		free(tmp);
		tmp = tok;
	}
}

static void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->type);
		free(env->value);
		free(env);
		env = tmp;
	}
}

void	exit_prog(t_data *data, int code)
{
	free_env(data->cpy_env);
	free_env(data->cpy_env2);
	free_tok(data->token);
	if (code == 130)
		write(2, "exit\n", 5);
	rl_clear_history();
	exit(code);
}

static void	loop(t_data *data)
{
	data->line = readline("minishell$ ");
	if (!data->line)
		exit_prog(data, 130);
	clean_line(data->line, data);
	if (*data->line)
		add_history(data->line);
	tokenize(data->line, data);
	if (!data->err_quote)
		parse(data);
	data->err_quote = 0;
	free_tok(data->token);
	data->token = NULL;
	free(data->line);
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
		loop(&data);
	rl_clear_history();
	return (0);
}
