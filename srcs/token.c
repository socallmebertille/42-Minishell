/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:06:55 by saberton          #+#    #+#             */
/*   Updated: 2024/11/19 16:51:07 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*last_value(t_token *tok)
{
	if (!tok)
		return (NULL);
	while (tok->next)
		tok = tok->next;
	return (tok);
}

static void add_token_node(char *value, t_token **tok, t_data *data)
{
	t_token	*node;
	t_token	*new_last_node;

	new_last_node = (t_token *)malloc(sizeof(t_token));
	if (!new_last_node)
		return ;
    // ft_bzero(new_last_node, sizeof(t_token));
	new_last_node->value = value;
	new_last_node->next = NULL;
	if (!*tok)
	{
        new_last_node->prev = NULL;
		*tok = new_last_node;
		data->token = *tok;
	}
	else
	{
		node = last_value(*tok);
		node->next = new_last_node;
        new_last_node->prev = node;
	}
	return ;
}

void	ft_strtok(char *line, t_data *data)
{
    char    **split;
    int     i;
    t_token	*tok;

	tok = NULL;
    i = 0;
    split = split_charset(line, " |><");
    while (split[i])
    {
        add_token_node(split[i], &tok, data);
        i++;
    }
    free(split);
    i = 0;
    t_token *tmp;
    tmp = NULL;
    while (tok)
    {
        tmp = tok->next;
        if (tok->prev)
            printf("%s <- ", tok->prev->value);
        if (tok->value)
            printf("%s", tok->value);
        if (tok->next)
            printf(" -> %s\n", tok->next->value );
        else
            printf("\n");
        tok = tmp;
    }
}