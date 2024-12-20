/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kepouliq <kepouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:42:36 by saberton          #+#    #+#             */
/*   Updated: 2024/12/20 16:37:48 by kepouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal_received = 0;

static int	is_line_empty_or_need_continue(t_data *data)
{
	int	i;

	i = 0;
	if (!data->line[0])
		return (69);
	while (ft_isspace(data->line[i]))
		i++;
	if (data->line[i] == '\0')
		return (69);
	if (data->line[0] == ':' && !data->line[1])
		return (69);
	if (data->line[0] == '!' && !data->line[1])
	{
		data->exit_status = 1;
		return (69);
	}
	return (0);
}

static void	clean_loop(t_data *data)
{
	if (access("heredoc.tmp", F_OK) == 0)
		unlink("heredoc.tmp");
	data->err_quote = 0;
	data->err = 0;
	free_tok(data);
	data->token = NULL;
	free(data->line);
	free(data->keep_line);
	reset_signal_handler(data);
}

static void	loop(t_data *data)
{
	while (1)
	{
		g_signal_received = 0;
		data->line = readline("minishell$ ");
		if (g_signal_received == 1)
			data->exit_status = 130;
		if (!data->line)
			return (write(2, "exit\n", 5), exit_prog(data, 0));
		data->keep_line = ft_strdup(data->line);
		if (is_line_empty_or_need_continue(data))
			continue ;
		syntaxe_line(data->line, data);
		if (*data->line)
			add_history(data->line);
		if (!data->err_quote && !data->err)
			tokenize(data->line, data);
		if (!data->err_quote && !data->err)
			parse(data);
		clean_loop(data);
	}
}

void	exit_prog(t_data *data, int code)
{
	free_env(data, data->cpy_env, 1);
	free_env(data, data->cpy_env2, 2);
	free_tok(data);
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
	data.pipe = NULL;
	loop(&data);
	rl_clear_history();
	return (0);
}
