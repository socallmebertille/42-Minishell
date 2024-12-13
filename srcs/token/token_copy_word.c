/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_copy_word.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:32:08 by kepouliq          #+#    #+#             */
/*   Updated: 2024/12/13 12:58:02 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_quote_exit(t_data *data)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(&data->wich_quote_err, 2);
	ft_putstr_fd("'\n", 2);
}

int	len_in_quote(char *line, int *j, char quote)
{
	int	len;

	len = 1;
	(*j)++;
	if (!line[*j])
		return (len);
	while (line[*j] && line[*j] != '\n' && line[*j] != quote)
	{
		len++;
		(*j)++;
	}
	if (!line[*j])
		return (len);
	return (len);
}

int	word_size(char *line, int *i)
{
	int	len;
	int	j;

	len = 0;
	j = *i;
	if (!line || !*line)
		return (0);
	while (line[j] && line[j] != '\n')
	{
		if (is_quote(line[j]))
		{
			len += len_in_quote(line, &j, line[j]);
		}
		if (!line[j])
			break ;
		if (!is_word(line[j]))
			break ;
		else
		{
			j++;
			len++;
		}
	}
	printf("len du mot == %d\n", len);
	return (len);
}

int	handle_quote(char *line, char *dup, int *i, int *j)
{
	char	quote;

	quote = line[*i];
	dup[*j] = line[*i];
	(*i)++;
	(*j)++;
	while (line[*i] && line[*i] != '\n' && line[*i] != quote)
	{
		dup[*j] = line[*i];
		(*j)++;
		(*i)++;
	}
	if (line[*i] != quote)
		return (0);
	dup[*j] = line[*i];
	(*i)++;
	(*j)++;
	return (1);
}

char	*ft_copy_word(char *line, int *i, t_data *data)
{
	int		j;
	char	*dup;

	j = word_size(line, i);
	dup = malloc(sizeof(char) * (j + 1));
	if (!dup)
		return (NULL);
	j = 0;
	while (line[*i] && line[*i] != '\n' && is_word(line[*i]))
	{
		if (is_quote(line[*i]))
		{
			data->wich_quote_err = line[*i];
			if (!handle_quote(line, dup, i, &j))
				return (free(dup), data->err_quote = 1, NULL);
		}
		else
		{
			dup[j] = line[*i];
			(*i)++;
			j++;
		}
	}
	dup[j] = '\0';
	return (dup);
}
