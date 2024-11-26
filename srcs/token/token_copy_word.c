/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_copy_word.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kepouliq <kepouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:32:08 by kepouliq          #+#    #+#             */
/*   Updated: 2024/11/25 17:25:10 by kepouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_in_quote(char *line, int *j, char quote)
{
	int	len;

	len = 1;
	(*j)++;
	while (line[*j] && line[*j] != '\n' && line[*j] != quote)
	{
		len++;
		(*j)++;
	}
	return (len);
}

int	word_size(char *line, int *i)
{
	int	len;
	int	j;

	len = 0;
	j = *i;
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
	return (len);
}

int	handle_quote(char *line, char *dup, int *i, int *j)
{
	char	quote;

	quote = line[*i];
	dup[*j] = line[*i];
	(*j)++;
	(*i)++;
	while (line[*i] && line[*i] != '\n' && line[*i] != quote)
	{
		dup[*j] = line[*i];
		(*j)++;
		(*i)++;
	}
	if (line[*i] != quote)
		return (0);
	dup[*j] = line[*i];
	(*j)++;
	(*i)++;
	return (1);
}

char	*ft_copy_word(char *line, int *i)
{
	int		j;
	char	*dup;

	j = word_size(line, i);
	printf("%d\n", j);
	dup = malloc(sizeof(char) * j + 1);
	if (!dup)
		return (NULL);
	j = 0;
	while (line[*i] && line[*i] != '\n' && is_word(line[*i]))
	{
		if (is_quote(line[*i]))
		{
			if (!handle_quote(line, dup, i, &j))
				return (free(dup), NULL);
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
