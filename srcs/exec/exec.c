/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:34:54 by saberton          #+#    #+#             */
/*   Updated: 2024/12/04 19:24:10 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(t_data *data, char **env, char **cmd, t_token *tok)
{
	char	*cmd_path;

	if (tok->type == BUILD)
	{
		handle_builtins(data, tok);
	}
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
    exit(EXIT_SUCCESS);
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
		exec_cmd(data, data->env, cmd, tok);
        printf("je rentre ici\n");
		// exit(EXIT_SUCCESS);
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
		if (!data->nb_pipe)
			exec_cmd(data, data->env, cmd, tok);
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

	pid = fork();
	if (pid == -1)
		exit_prog(data, EXIT_FAILURE);
	if (pid == 0)
	{
		tmp = data->token;
		data->nb_pipe = pipe_in_line(data);
		if (data->nb_pipe)
		{
			while (tmp)
			{
				exec_choice(data, tmp);
				data->nb_pipe--;
				tmp = recup_tok_after_pipe(tmp);
			}
		}
		else
        {
            // dup2(fds[0], STDIN_FILENO);
			exec_choice(data, tmp);
        }
		// exit(EXIT_SUCCESS);
        printf("je rentre icic\n");
		exit_prog(data, 1);
	}
	else
		waitpid(pid, NULL, 0);
}
