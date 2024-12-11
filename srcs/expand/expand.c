/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kepouliq <kepouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:20:10 by kepouliq          #+#    #+#             */
/*   Updated: 2024/12/11 19:25:27 by kepouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	dollar_in_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

static size_t	get_var_len(char *str)
{
	size_t	len;
	int		i;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			while (ft_isalnum(str[i]) || str[i] == '_')
			{
				len++;
				i++;
			}
			return (len);
		}
	}
	return (0);
}

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

static int	is_exist_in_env(char *var, t_data *data)
{
	t_env	*tmp;

	tmp = data->cpy_env;
	while (tmp)
	{
		if (ft_strcmp(tmp->type, var) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
static void	ft_concate(t_token *tok)
{
	(void)tok;
	printf("CONCATE\n");
}

static char	*extract_var(char *str, int *i)
{
	char	*var;
	size_t	var_len;

	var_len = 0;
	var = NULL;
	var_len = get_var_len(str);
    printf("var_len = %zu\n", var_len);
    (*i)++;
	var = ft_substr(str, *i, var_len);
    printf("i avant %d\n", *i);
	(*i) += var_len;
    printf("i apres %d\n", *i);
    free(str);
    return (var);
}
static void	expan_var(char *str, t_data *data, t_token *tok)
{
	int		i;
	int		len_total;
	char	*var;
	char	*in_var;
    int j;
                                    // int j pour depart de sub
    j = 0;
	var = NULL;
	in_var = NULL;
	len_total = ft_strlen(str);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
            printf("ce que j'envoi dans extract -> %s\n", ft_substr(str, i, len_total));
			var = extract_var(ft_substr(str, j, len_total), &i);
            printf("vac que j'ai extarct - > %s\n", var);
			if (is_exist_in_env(var, data))
			{
				in_var = give_me_inside_var(var, data);
				ft_concate(tok);
			}
            free(var);
			// else
			// si existe pas surement delete la var du token->value
		}
		else
			i++;
	}
    printf("je m'arrete\n");
}

// static int	is_var_in_tok_value(char *str, t_data *data)
// {
// 	t_token	*tok;
// 	char	*var;

// 	var = NULL;
// 	tok = data->token;
// 	while (tok)
// 	{
// 		if (dollar_in_str(tok->value))
// 			return (1);
// 		tok = tok->next;
// 	}
// 	return (0);
// }

void	expand(t_data *data)
{
	t_token *tok;
	char *var_in_str;

	var_in_str = NULL;
	tok = data->token;
	while (tok)
	{
		if (dollar_in_str(tok->value))
			expan_var(tok->value, data, tok);
		tok = tok->next;
	}
}