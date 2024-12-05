/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:34:54 by saberton          #+#    #+#             */
/*   Updated: 2024/12/05 18:18:21 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(t_data *data, char **env, char **cmd, t_token *tok)
{
	char	*cmd_path;

	// if (tok->type == BUILD)
	// {
	// 	handle_builtins(data, tok);
	// }
	if (!cmd || !*cmd)
		return ;
	cmd_path = valid_cmd(data, tok->value);
	if (!cmd_path)
		return ;
	if (!*cmd_path)
	{
		free(cmd_path);
		cmd_path = ft_strdup(*cmd);
		if (!cmd_path)
			return ;
	}
	if (tok->type != BUILD)
	{
		if (execve(cmd_path, cmd, env) == -1)
		{
			free(cmd_path);
			perror("Error executing execve\n");
			exit_prog(data, EXIT_FAILURE);
			// a change pour re display readline(minishell$ )
		}
	}
	// exit(EXIT_SUCCESS);
	free(cmd_path);
}

static void	ft_pipes(t_data *data, t_token *tok, char **cmd)
{
	pid_t	pid;
	int		fds[2];

	if (pipe(fds) == -1)
		exit_prog(data, EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit_prog(data, EXIT_FAILURE);
	if (pid == 0)
	{
		close(fds[0]);
		dup2(fds[1], STDOUT_FILENO);
		close(fds[1]);
		if (tok->type == BUILD)
			handle_builtins(data, tok);
		else
			exec_cmd(data, data->env, cmd, tok);
	}
	else
	{
		close(fds[1]);
		dup2(fds[0], STDIN_FILENO);
		close(fds[0]);
		waitpid(pid, NULL, 0);
	}
}

static void	exec_choice(t_data *data, t_token *tok)
{
	t_enum	choice;
	char	**cmd;

	choice = wich_type_exec(data);
	cmd = NULL;
	if (choice == CMD)
	{
		cmd = recup_cmd(data, tok);
		if (data->nb_pipe == 0)
		{
			if (tok->type == BUILD)
				handle_builtins(data, tok);
			else
				exec_cmd(data, data->env, cmd, tok);
		}
		else
			ft_pipes(data, tok, cmd);
		ft_free_tab(cmd);
	}
	// else if (choice == INFILE)
	// 	exec_in();
	// else if (choice == OUTFILE)
	// 	exec_out();
	// else if (choice == APPEND)
	// 	exec_append();
	// else if (choice == HEREDOC)
	// 	exec_heredoc();
}

void	wich_exec(t_data *data)
{
	t_token	*tmp;
	pid_t	pid;

	tmp = data->token;
	data->nb_pipe = pipe_in_line(data);
	if (data->nb_pipe)
	{
		pid = fork();
		if (pid == -1)
			exit_prog(data, EXIT_FAILURE);
		if (pid == 0)
		{
			while (tmp)
			{
				exec_choice(data, tmp);
				data->nb_pipe--;
				tmp = recup_tok_after_pipe(tmp);
			}
			// char **cmd = recup_cmd(data, tmp);
			// ft_pipes(data, tmp, cmd);
			// ft_free_tab(cmd);
		}
		else
			waitpid(pid, NULL, 0);
	}
	else
	{
		if (tmp->type == BUILD)
			handle_builtins(data, tmp);
		else
		{
			pid = fork();
			if (pid == -1)
				exit_prog(data, EXIT_FAILURE);
			if (pid == 0)
				exec_choice(data, tmp);
			else
				waitpid(pid, NULL, 0);
		}
	}
}
