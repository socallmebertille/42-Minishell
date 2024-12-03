/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:05:45 by kepouliq          #+#    #+#             */
/*   Updated: 2024/12/03 13:51:40 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_builtins(t_data *data)
{
	if (data->token && data->token->value != NULL)
	{
		if (ft_strcmp(data->token->value, "exit") == 0)
			handle_exit(data);
		else if (ft_strcmp(data->token->value, "env") == 0)
			handle_env(data);
		else if (ft_strcmp(data->token->value, "echo") == 0)
			handle_echo(data);
		else if (ft_strcmp(data->token->value, "pwd") == 0)
			handle_pwd(data);
		else if (ft_strcmp(data->token->value, "unset") == 0)
			handle_unset(data);
		else if (ft_strcmp(data->token->value, "export") == 0)
			handle_export(data);
		return (1);
	}
	return (0);
}

void	parse(t_data *data)
{
	if (!good_syntaxe(data))
		return ;
	else if (is_builtins(data))
		return ;
	// else if (is_cmd(data))
	// 	return ;
}
static void	print_err_syntaxe(t_data *data, char err, int i)
{
	int	j;

	j = 0;
	data->err_quote = 1;
	ft_putstr_fd("minishell: operation `", 2);
	while (i > 0)
	{
		ft_putchar_fd(err, 2);
		j++;
		i--;
	}
	ft_putstr_fd("' not handle\n", 2);
}

void	clean_line(char *line, t_data *data)
{
	int		i;
	int		open_quote;
	char	*newline_pos;

	i = 0;
	open_quote = 0;
	if (!line)
		return ;
	newline_pos = ft_strchr(line, '\n');
	while (newline_pos)
	{
		if (newline_pos)
			*newline_pos = '&';
		newline_pos = ft_strchr(line, '\n');
	}
	while (line[i])
	{
		if ((line[i] == '\"' || line[i] == '\'') && !open_quote)
			open_quote = 1;
		else if ((line[i] == '\"' || line[i] == '\'') && open_quote)
			open_quote = 0;
		if (((line[i] == '&' && line[i + 1] == '&') || (line[i] == '|' && line[i
					+ 1] == '|')) && !open_quote)
			print_err_syntaxe(data, line[i], 2);
		if ((line[i] == ';' || line[i] == '\\' || line[i] == '&')
			&& !open_quote)
			print_err_syntaxe(data, line[i], 1);
		if (data->err_quote == 1)
			return ;
		i++;
	}
}

