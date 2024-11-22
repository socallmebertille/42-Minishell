/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kepouliq <kepouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:55:18 by kepouliq          #+#    #+#             */
/*   Updated: 2024/11/22 17:02:35 by kepouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_enum_to_char(int num)
{
	if (num == 1)
		return ("WORD");
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
	int i;
	t_token *tok;

	tok = NULL;
	i = 0;
	while (line[i] && line[i] != '\0')
	{
		if (ft_isspace(line[i]))
			i++;
		dispatcheur(line, &i, data, &tok);
	}
	t_token *tmp;
	tmp = NULL;
	while (tok)
	{
		tmp = tok->next;
		printf("TOK TYPE = %s / TOK VALUE = %s", ft_enum_to_char(tok->type),
			tok->value);
		if (tok->prev)
			printf(" / PREV = %s", tok->prev->value);
		if (tok->next)
			printf(" / NEXT = %s", tok->next->value);
		printf("\n");
		tok = tmp;
	}
}