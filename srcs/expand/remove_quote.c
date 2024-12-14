/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 14:36:32 by kepouliq          #+#    #+#             */
/*   Updated: 2024/12/14 19:22:59 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	replace_in_tok(t_token *tok, char *expanded_str)
{
	free(tok->value);
	tok->value = ft_strdup(expanded_str);
}

int	is_in_double_quotes(char *str, int index)
{
	int	in_double;
	int	i;

	in_double = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i] && i < index)
	{
		if (!str[i])
			return (in_double);
		if (str[i] == '\"' && (i == 0 || str[i - 1] != '\\'))
			in_double = !in_double;
		i++;
	}
	return (in_double);
}

void	remove_quote(char *str, t_token *tok)
{
	int		i;
	char	*no_quote_str;
	char	*tmp;

	i = 0;
	tmp = NULL;
	no_quote_str = ft_strdup("");
	if (!no_quote_str)
		return ;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (str[i] == '\"')
			{
				if (is_in_single_quotes(str, i))
				{
					tmp = no_quote_str;
					no_quote_str = ft_strjoin_char(tmp, str[i]);
					free(tmp);
					i++;
				}
				else
				{
					i++;
					continue ;
				}
			}
			else if (str[i] == '\'')
			{
				if (is_in_double_quotes(str, i))
				{
					tmp = no_quote_str;
					no_quote_str = ft_strjoin_char(tmp, str[i]);
					free(tmp);
					i++;
				}
				else
				{
					i++;
					continue ;
				}
			}
		}
		else
		{
			tmp = no_quote_str;
			no_quote_str = ft_strjoin_char(tmp, str[i]);
			free(tmp);
			i++;
		}
	}
	replace_in_tok(tok, no_quote_str);
	free(no_quote_str);
}
