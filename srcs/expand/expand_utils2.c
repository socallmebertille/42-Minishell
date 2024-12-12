/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kepouliq <kepouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:00:33 by kepouliq          #+#    #+#             */
/*   Updated: 2024/12/12 18:29:18 by kepouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_in_tok(t_token *tok, char *expanded_str)
{
	free(tok->value);
	tok->value = ft_strdup(expanded_str);
}
