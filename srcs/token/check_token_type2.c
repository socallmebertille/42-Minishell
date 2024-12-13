/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token_type2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:03:55 by saberton          #+#    #+#             */
/*   Updated: 2024/12/13 13:04:20 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
