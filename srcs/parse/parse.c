/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kepouliq <kepouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:05:45 by kepouliq          #+#    #+#             */
/*   Updated: 2024/12/13 17:54:21 by kepouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtins(t_token *token)
{
	if (token && token->value != NULL)
	{
		if (ft_strcmp(token->value, "exit") == 0)
			return (token->type = BUILD, 1);
		else if (ft_strcmp(token->value, "env") == 0)
			return (token->type = BUILD, 1);
		else if (ft_strcmp(token->value, "echo") == 0)
			return (token->type = BUILD, 1);
		else if (ft_strcmp(token->value, "pwd") == 0)
			return (token->type = BUILD, 1);
		else if (ft_strcmp(token->value, "unset") == 0)
			return (token->type = BUILD, 1);
		else if (ft_strcmp(token->value, "export") == 0)
			return (token->type = BUILD, 1);
		else if (ft_strcmp(token->value, "cd") == 0)
			return (token->type = BUILD, 1);
	}
	return (0);
}

int	handle_builtins(t_data *data, t_token *tok, int fd_out)
{
	if (tok && tok->value != NULL && tok->type == BUILD)
	{
		update_last_cmd(data, tok->value);
		if (ft_strcmp(tok->value, "exit") == 0)
			handle_exit(data, tok, fd_out);
		else if (ft_strcmp(tok->value, "env") == 0)
			handle_env(data, tok, fd_out);
		else if (ft_strcmp(tok->value, "echo") == 0)
			handle_echo(tok, fd_out);
		else if (ft_strcmp(tok->value, "pwd") == 0)
			handle_pwd(fd_out);
		else if (ft_strcmp(tok->value, "unset") == 0)
			handle_unset(data, tok);
		else if (ft_strcmp(tok->value, "export") == 0)
			handle_export(data, tok, fd_out);
		else if (ft_strcmp(tok->value, "cd") == 0)
			handle_cd(data, fd_out);
		return (1);
	}
	return (0);
}

static void	print_token(t_data *data)
{
	int		i;
	t_token	*tok;
	t_token	*tmp;

	tmp = NULL;
	tok = data->token;
	if (data->err_quote)
		return ;
	i = 0;
	while (tok)
	{
		printf(MAGENTA "============== TOKEN %d ======================\n" RESET,
			i);
		tmp = tok->next;
		if (tok->prev)
		{
			printf("PREV = ");
			printf(BLUE "%s\t" RESET, tok->prev->value);
		}
		else
			printf("\t\t");
		printf(RED "%s " RESET, tok->value);
		printf(YELLOW "= %s" RESET, ft_enum_to_char(tok->type));
		if (tok->next)
		{
			printf("\tNEXT = ");
			printf(GREEN "%s\n" RESET, tok->next->value);
		}
		else
			printf("\n");
		printf("\n");
		tok = tmp;
		i++;
	}
}

void	parse(t_data *data)
{
	// expand(data);
	ft_change_word_to_cmd(data);
	print_token(data);
	if (!good_syntaxe(data))
		return ;
	ft_check_access_cmd(data);
	if (data->err)
		return ;
	wich_exec(data);
	if (data->err)
		return ;
}
