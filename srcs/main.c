/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kepouliq <kepouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:42:36 by saberton          #+#    #+#             */
/*   Updated: 2024/11/25 18:05:25 by kepouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_tok(t_token *tok)
{
	t_token	*tmp;

	while (tok)
	{
		tmp = tok->next;
		if (tok->value)
		{
			free(tok->value);
			tok->value = NULL;
		}
		free(tok);
		tok = tmp;
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
	free_tok(data->token);
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
		tokenize(data.line, &data);
		parse(&data);
		free_tok(data.token);
		data.token = NULL;
		free(data.line);
	}
	rl_clear_history();
	return (0);
}
