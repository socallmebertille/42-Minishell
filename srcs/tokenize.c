/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kepouliq <kepouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:55:18 by kepouliq          #+#    #+#             */
/*   Updated: 2024/11/20 18:13:33 by kepouliq         ###   ########.fr       */
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

static int	is_pipe(char c)
{
	if (c == PIPE)
		return (1);
	return (0);
}

static int	is_operateur(char c)
{
	if (c == INFILE || c == OUTFILE)
		return (1);
	return (0);
}

static int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}
static int	is_word(char c)
{
	if (!ft_isspace(c) && !is_operateur(c) && !is_pipe(c))
		return (1);
	return (0);
}
char	*ft_copy_word(char *line, int *i)
{
	int		j;
	int		count;
	char	*dup;

	j = *i;
	count = 0;
	while (line[j] && is_word(line[j]))
	{
		j++;
		count++;
	}
	dup = malloc(sizeof(char) * count + 1);
	if (!dup)
		return (NULL);
	j = 0;
	while (line[*i] && is_word(line[*i]))
	{
		dup[j] = line[*i];
		(*i)++;
		j++;
	}
	dup[j] = '\0';
	return (dup);
}

char	*ft_copy_pipe(int *i)
{
	char	*dup;

	dup = malloc(sizeof(char) * 2);
	if (!dup)
		return (NULL);
	dup[0] = '|';
	dup[1] = '\0';
	(*i)++;
	return (dup);
}
char	*ft_copy_operateur(int *i, int j)
{
	char	*dup;

	dup = malloc(sizeof(char) * 3);
	if (!dup)
		return (NULL);
	if (j == 3)
    {
        dup[0] = '>';
        dup[1] = '>';
        dup[2] = '\0';
        (*i)+=2;
    }
    else if (j == 4)
    {
        dup[0] = '<';
        dup[1] = '<';
        dup[2] = '\0';
        (*i)+=2;
    }
    else if (j == 60)
    {
        dup[0] = '<';
        dup[1] = '\0';
        dup[2] = '\0';
        (*i)++;
    }
    else if (j == 62)
    {
        dup[0] = '>';
        dup[1] = '\0';
        dup[2] = '\0';
        (*i)++;
    }
	return (dup);
}
int find_operateur(char *line, int *i)
{
    if (line[*i] == '>' && line[*i + 1] == '>')
        return(3);
    if (line[*i] == '<' && line[*i + 1] == '<')
        return(4);
    if (line[*i] == '<' && line[*i + 1] != '<')
        return (60);   
    if (line[*i] == '>' && line[*i + 1] != '>')
        return (62);
    return (0);
}

static void	add_token_word(char *line, t_token **tok, t_data *data, int *i)
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
static void	add_token_pipe(t_token **tok, t_data *data, int *i)
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
static void	add_token_operateur(char *line, t_token **tok, t_data *data, int *i)
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

static int	dispatcheur(char *line, int *i, t_data *data, t_token **tok)
{
	if (is_word(line[*i]))
		add_token_word(line, tok, data, i);
	else if (is_pipe(line[*i]))
		add_token_pipe(tok, data, i);
	else if (is_operateur(line[*i]))
		add_token_operateur(line, tok, data, i);
	return (0);
}
char	*ft_enum_to_char(int num)
{
	if (num == 1)
		return ("WORD");
	if (num == 124)
		return ("PIPE");
	if (num == HEREDOC)
		return ("HEREDOk");
	if (num == OUTFILE)
		return ("OUT");
    if (num == INFILE)
		return ("INT");
    if (num == APPEND)
		return ("APPEND");
	return ("");
}

void	tokenize(char *line, t_data *data)
{
	int i;
	t_token *tok;

	tok = NULL;
	i = 0;
	while (line[i] && line[i] != '\0')
	{
		if (ft_isspace(line[i]))
			i++;
		dispatcheur(line, &i, data, &tok);
	}
	t_token *tmp;
	tmp = NULL;
	while (tok)
	{
		tmp = tok->next;
		printf("TOK TYPE = %s / TOK VALUE = %s", ft_enum_to_char(tok->type),
			tok->value);
		if (tok->prev)
			printf(" / PREV = %s", tok->prev->value);
		if (tok->next)
			printf(" / NEXT = %s", tok->next->value);
		printf("\n");
		tok = tmp;
	}
}