/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kepouliq <kepouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:59:55 by kepouliq          #+#    #+#             */
/*   Updated: 2024/11/25 17:21:13 by kepouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*last_value(t_token *tok)
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
		return ;
	new_last_node->type = WORD;
	new_last_node->value = ft_copy_word(line, i);
	// if (new_last_node->value == NULL)
	//     (message erreur free et exit)
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

void	add_token_pipe(t_token **tok, t_data *data, int *i)
{
	t_token	*node;
	t_token	*new_last_node;

	new_last_node = (t_token *)malloc(sizeof(t_token));
	if (!new_last_node)
		return ;
	new_last_node->type = PIPE;
	new_last_node->value = ft_copy_pipe(i);
	// if (new_last_node->value == NULL)
	//     (message erreur free et exit)
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

void	add_token_operateur(char *line, t_token **tok, t_data *data, int *i)
{
	t_token	*node;
	t_token	*new_last_node;

	new_last_node = (t_token *)malloc(sizeof(t_token));
	if (!new_last_node)
		return ;
	new_last_node->type = find_operateur(line, i);
	new_last_node->value = ft_copy_operateur(i, new_last_node->type);
	// / if (new_last_node->value == NULL)
	//     (message erreur free et exit)
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
