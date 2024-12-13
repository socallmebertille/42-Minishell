/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_new_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 18:30:41 by saberton          #+#    #+#             */
/*   Updated: 2024/12/13 17:14:02 by saberton         ###   ########.fr       */
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
		if (((line[i] == '&' && line[i + 1] == '&')
				|| (line[i] == '|' && line[i + 1] == '|')) && !open_quote)
			print_err_syntaxe(data, line[i], 2);
		if ((line[i] == ';' || line[i] == '\\' || line[i] == '&')
			&& !open_quote)
			print_err_syntaxe(data, line[i], 1);
		if (data->err_quote == 1)
			return ;
		i++;
	}
}

static int	check_nl_in_quote(char *line, int open_quote, int i, char quote)
{
	if (!line[i])
		return (1);
	while (line[i])
	{
		printf("char [%c]\n", line[i]);
		if (!open_quote && (line[i] == '\'' || line[i] == '\"'))
		{
			quote = line[i];
			open_quote = 1;
		}
		else
		{
			if (line[i] == '\"' && line[i] == quote)
			{
				open_quote = 0;
				quote = '\0';
			}
		}
		if (line[i] == '\n' && !open_quote)
			return (0);
		i++;
	}
	return (1);
}

void	clean_line(char *line, t_data *data)
{
	char	*newline_pos;
	int		nl_in_quote;

	if (!line)
		return ;
	nl_in_quote = check_nl_in_quote(line, 0, 0, '\0');
	if (nl_in_quote)
	{
		printf("no pb\n");
		return ;
	}
	newline_pos = ft_strchr(line, '\n');
	while (newline_pos)
	{
		if (newline_pos && !nl_in_quote)
			*newline_pos = '&';
		newline_pos = ft_strchr(line, '\n');
	}
	// printf("comment je comprends ma line [%s]\n", line);
	check_new_line(line, data);
}
