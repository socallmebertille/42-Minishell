/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 18:30:41 by saberton          #+#    #+#             */
/*   Updated: 2024/12/13 20:14:22 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_err_syntaxe(char err, int i)
{
	int	j;

	j = 0;
	ft_putstr_fd("minishell: operation `", 2);
	while (i > 0)
	{
		ft_putchar_fd(err, 2);
		j++;
		i--;
	}
	ft_putstr_fd("' not handle\n", 2);
}

static int	check_syntaxe_in_quote(char *line, int open_quote, int i,
		char quote)
{
	if (!line)
		return (1);
	while (line[i])
	{
		if (!open_quote && (line[i] == '\'' || line[i] == '\"'))
		{
			quote = line[i];
			open_quote = 1;
		}
		else if ((line[i] == '\"' || line[i] == '\'') && line[i] == quote)
		{
			open_quote = 0;
			quote = '\0';
		}
		if ((line[i] == '\n' || line[i] == ';' || line[i] == '\\')
			&& !open_quote)
			return (print_err_syntaxe(line[i], 1), 1);
		if (((line[i] == '&' && line[i + 1] == '&') || (line[i] == '|' && line[i
					+ 1] == '|')) && !open_quote)
			return (print_err_syntaxe(line[i], 2), 2);
		i++;
	}
	return (0);
}

void	syntaxe_line(char *line, t_data *data)
{
	int	i;

	if (!line)
		return ;
	i = check_syntaxe_in_quote(data->line, 0, 0, '\0');
	if (i)
	{
		data->err_quote = i;
		data->exit_status = 2;
		return ;
	}
}
