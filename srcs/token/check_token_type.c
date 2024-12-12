/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kepouliq <kepouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 19:03:07 by kepouliq          #+#    #+#             */
/*   Updated: 2024/12/11 15:31:38 by kepouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quote(char c)
{
	if (c == '"' || c == '\'')
		return (1);
	return (0);
}

int	is_pipe(char c)
{
	if (c == PIPE)
		return (1);
	return (0);
}

int	is_operateur(char c)
{
	if (c == INFILE || c == OUTFILE)
		return (1);
	return (0);
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	is_word(char c)
{
	if (!ft_isspace(c) && !is_operateur(c) && !is_pipe(c))
		return (1);
	return (0);
}

int	is_word_and_space(char c)
{
	if (!is_operateur(c) && !is_pipe(c))
		return (1);
	return (0);
}
