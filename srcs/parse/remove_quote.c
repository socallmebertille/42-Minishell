/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 14:36:32 by kepouliq          #+#    #+#             */
/*   Updated: 2024/12/20 19:11:13 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	replace_in_tok(t_token *tok, char *expanded_str)
{
	free(tok->value);
	tok->value = ft_strdup(expanded_str);
}

static void	handle_double_quote(char *str, char **no_quote_str, int *i)
{
	char	*tmp;

	if (is_in_single_quotes(str, *i))
	{
		tmp = *no_quote_str;
		*no_quote_str = ft_strjoin_char(tmp, str[*i]);
		free(tmp);
		(*i)++;
	}
	else
		(*i)++;
}

static void	handle_single_quote(char *str, char **no_quote_str, int *i)
{
	char	*tmp;

	if (is_in_double_quotes(str, *i))
	{
		tmp = *no_quote_str;
		*no_quote_str = ft_strjoin_char(tmp, str[*i]);
		free(tmp);
		(*i)++;
	}
	else
		(*i)++;
}

static void	append_char(char **no_quote_str, char c)
{
	char	*tmp;

	tmp = *no_quote_str;
	*no_quote_str = ft_strjoin_char(tmp, c);
	free(tmp);
}

void	remove_quote(char *str, t_token *tok)
{
	int		i;
	char	*no_quote_str;

	if (!str)
		return ;
	no_quote_str = ft_strdup("");
	if (!no_quote_str)
		return ;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			handle_double_quote(str, &no_quote_str, &i);
		else if (str[i] == '\'')
			handle_single_quote(str, &no_quote_str, &i);
		else
		{
			append_char(&no_quote_str, str[i]);
			i++;
		}
	}
	replace_in_tok(tok, no_quote_str);
	free(no_quote_str);
}
