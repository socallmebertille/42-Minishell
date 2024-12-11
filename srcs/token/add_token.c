/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:59:55 by kepouliq          #+#    #+#             */
/*   Updated: 2024/12/11 13:37:55 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*last_token(t_token *tok)
{
	if (!tok)
		return (NULL);
	while (tok->next)
		tok = tok->next;
	return (tok);
}

void	add_token_word(char *line, t_token **tok, t_data *data, int *i)
{
	t_token	*node;
	t_token	*new_last_node;

	new_last_node = (t_token *)malloc(sizeof(t_token));
	if (!new_last_node)
		return (malloc_failed_mess(data));
	new_last_node->next = NULL;
	new_last_node->type = WORD;
	new_last_node->value = NULL;
	new_last_node->value = ft_copy_word(line, i, data);
	if (!*tok)
	{
		new_last_node->prev = NULL;
		new_last_node->type = CMD;
		*tok = new_last_node;
		data->token = *tok;
	}
	else
	{
		node = last_token(*tok);
		if (!node)
			return (malloc_failed_mess(data));
		node->next = new_last_node;
		new_last_node->prev = node;
	}
	if (new_last_node->value == NULL && data->err_quote)
		open_quote_exit(data);
	else if (new_last_node->value == NULL)
		return (malloc_failed_mess(data));
}

void	add_token_pipe(t_token **tok, t_data *data, int *i)
{
	t_token	*node;
	t_token	*new_last_node;

	new_last_node = (t_token *)malloc(sizeof(t_token));
	if (!new_last_node)
		return (malloc_failed_mess(data));
	new_last_node->type = PIPE;
	new_last_node->value = ft_copy_pipe(i);
	if (new_last_node->value == NULL)
		return (malloc_failed_mess(data));
	new_last_node->next = NULL;
	if (!*tok)
	{
		new_last_node->prev = NULL;
		*tok = new_last_node;
		data->token = *tok;
	}
	else
	{
		node = last_token(*tok);
		if (!node)
			return (malloc_failed_mess(data));
		node->next = new_last_node;
		new_last_node->prev = node;
	}
}

void	add_token_operateur(char *line, t_token **tok, t_data *data, int *i)
{
	t_token	*node;
	t_token	*new_last_node;

	new_last_node = (t_token *)malloc(sizeof(t_token));
	if (!new_last_node)
		return (malloc_failed_mess(data));
	new_last_node->type = find_operateur(line, i);
	new_last_node->value = ft_copy_operateur(i, new_last_node->type);
	if (new_last_node->value == NULL)
		return (malloc_failed_mess(data));
	new_last_node->next = NULL;
	if (!*tok)
	{
		new_last_node->prev = NULL;
		*tok = new_last_node;
		data->token = *tok;
	}
	else
	{
		node = last_token(*tok);
		if (!node)
			return (malloc_failed_mess(data));
		node->next = new_last_node;
		new_last_node->prev = node;
	}
}
