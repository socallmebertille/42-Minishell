/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:55:18 by kepouliq          #+#    #+#             */
/*   Updated: 2024/12/13 16:20:29 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_enum_to_char(int num)
{
	if (num == 1)
		return ("FLAG");
	if (num == 124)
		return ("PIPE");
	if (num == HEREDOC)
		return ("HEREDOC");
	if (num == OUTFILE)
		return ("OUT");
	if (num == INFILE)
		return ("IN");
	if (num == APPEND)
		return ("APPEND");
	if (num == CMD)
		return ("CMD");
	if (num == BUILD)
		return ("BUILTINS");
	return ("");
}

static int	dispatcheur(char *line, int *i, t_data *data, t_token **tok)
{
	if (is_word(line[*i]))
		add_token_word(line, tok, data, i);
	else if (is_pipe(line[*i]))
		add_token_pipe(tok, data, i);
	else if (is_operateur(line[*i]))
		add_token_operateur(line, tok, data, i);
	return (0);
}

void	tokenize(char *line, t_data *data)
{
	int		i;
	t_token	*tok;
	t_token	*tmp;

	tmp = NULL;
	tok = NULL;
	i = 0;
	while (line[i])
	{
		if (ft_isspace(line[i]))
			i++;
		if (line[i])
			dispatcheur(line, &i, data, &tok);
	}
}
