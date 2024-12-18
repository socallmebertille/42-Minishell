/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kepouliq <kepouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:55:18 by kepouliq          #+#    #+#             */
/*   Updated: 2024/12/18 13:13:50 by kepouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_enum_to_char(int num)
{
	if (num == WORD)
		return ("WORD");
	if (num == PIPE)
		return ("PIPE");
	if (num == HEREDOC)
		return ("HEREDOC");
	if (num == REDIR_OUTFILE)
		return ("REDIR_OUTFILE");
	if (num == REDIR_INFILE)
		return ("REDIR_INFILE");
	if (num == OUTFILE)
		return ("OUTFILE");
	if (num == INFILE)
		return ("INFILE");
	if (num == APPEND)
		return ("APPEND");
	if (num == CMD)
		return ("CMD");
	if (num == BUILD)
		return ("BUILTINS");
	if (num == DELIM)
		return ("DELIM");
	if (num == NOT_FOUND)
		return ("CMD NOT FOUND");
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

	tok = NULL;
	i = 0;
	(void)line;
	expand(data);
	while (data->line[i])
	{
		if (ft_isspace(data->line[i]))
			i++;
		if (data->line[i])
			dispatcheur(data->line, &i, data, &tok);
	}
	tmp = data->token;
	while (tmp)
	{
		if (tmp)
			remove_quote(tmp->value, tmp);
		tmp = tmp->next;
	}
}
