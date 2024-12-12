/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kepouliq <kepouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:20:10 by kepouliq          #+#    #+#             */
/*   Updated: 2024/12/12 18:30:02 by kepouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*give_me_inside_var(char *var, t_data *data)
{
	char	*in_var;
	t_env	*tmp;

	in_var = NULL;
	tmp = data->cpy_env;
	while (tmp)
	{
		if (ft_strcmp(tmp->type, var) == 0)
		{
			in_var = ft_strdup(tmp->value);
			return (in_var);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

static char	*extract_var(char *str, int *i)
{
	char	*var;
	size_t	var_len;

	if (!str)
		return (NULL);
	var_len = 0;
	var = NULL;
	var_len = get_var_len(str);
	if (!var_len)
		return (NULL);
	(*i)++;
	var = ft_substr(str, 1, var_len);
	(*i) += var_len;
	return (var);
}

static char	*ft_concate(char *before, char *in_var)
{
	char	*result;
	size_t	total_len;

	total_len = strlen(before) + strlen(in_var);
	result = malloc(sizeof(char) * (total_len + 1));
	if (!result)
		return (NULL);
	ft_strcpy(result, before);
	ft_strcat(result, in_var);
	return (result);
}

static void	expan_var(char *str, t_data *data, t_token *tok)
{
	int		i;
	char	*before;
	char	*var;
	char	*in_var;
	char	*expanded_str;
	char	*tmp;

	tmp = NULL;
	i = 0;
	expanded_str = ft_strdup("");
	if (!expanded_str)
		return ;
	while (str[i])
	{
		if (str[i] == '$' && !is_in_single_quotes(str, i))
		{
			before = ft_substr(expanded_str, 0, ft_strlen(expanded_str));
			var = extract_var(str + i, &i);
			if (is_exist_in_env(var, data))
				in_var = give_me_inside_var(var, data);
			else
				in_var = ft_strdup("");
			tmp = expanded_str;
			expanded_str = ft_concate(before, in_var);
			free(tmp);
			free(before);
			free(var);
			free(in_var);
		}
		else
		{
			tmp = expanded_str;
			expanded_str = ft_strjoin_char(tmp, str[i]);
			free(tmp);
			i++;
		}
	}
	replace_in_tok(tok, expanded_str);
	free(expanded_str);
}

void	expand(t_data *data)
{
	t_token	*tok;
	char	*var_in_str;

	var_in_str = NULL;
	tok = data->token;
	while (tok)
	{
		if (dollar_in_str(tok->value))
			expan_var(tok->value, data, tok);
		tok = tok->next;
	}
}
