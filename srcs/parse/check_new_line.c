/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_new_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 18:30:41 by saberton          #+#    #+#             */
/*   Updated: 2024/12/03 18:36:12 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	check_new_line(char *line, t_data *data)
{
	int	i;
	int	open_quote;

	i = 0;
	open_quote = 0;
	if (!line)
		return ;
	while (line[i])
	{
		if ((line[i] == '\"' || line[i] == '\'') && !open_quote)
			open_quote = 1;
		else if ((line[i] == '\"' || line[i] == '\'') && open_quote)
			open_quote = 0;
		if (((line[i] == '&' && line[i + 1] == '&') || (line[i] == '|'
					&& line[i + 1] == '|')) && !open_quote)
			print_err_syntaxe(data, line[i], 2);
		if ((line[i] == ';' || line[i] == '\\' || line[i] == '&')
			&& !open_quote)
			print_err_syntaxe(data, line[i], 1);
		if (data->err_quote == 1)
			return ;
		i++;
	}
}

void	clean_line(char *line, t_data *data)
{
	char	*newline_pos;

	if (!line)
		return ;
	newline_pos = ft_strchr(line, '\n');
	while (newline_pos)
	{
		if (newline_pos)
			*newline_pos = '&';
		newline_pos = ft_strchr(line, '\n');
	}
	check_new_line(line, data);
}
