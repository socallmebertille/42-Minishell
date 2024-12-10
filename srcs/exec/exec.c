/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:34:54 by saberton          #+#    #+#             */
/*   Updated: 2024/12/10 19:35:27 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(t_data *data, char **env, char **cmd, t_token *tok)
{
	char	*cmd_path;

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
	if (execve(cmd_path, cmd, env) == -1)
	{
		free(cmd_path);
		perror("Error executing execve\n");
		exit_prog(data, EXIT_FAILURE);
		// a change pour re display readline(minishell$ )
	}
	free(cmd_path);
}

void	exec_choice(t_data *data, t_token *tok)
{
	t_enum	choice;
	char	**cmd;

	choice = wich_type_exec(data);
	cmd = NULL;
	if (choice == CMD)
	{
		cmd = recup_cmd(data, tok);
		if (tok->type == BUILD)
			handle_builtins(data, tok, STDOUT_FILENO);
		else
			exec_cmd(data, data->env, cmd, tok);
		ft_free_tab(cmd);
	}
	else if (choice == INFILE)
		exec_in();
	else if (choice == OUTFILE)
		exec_out();
	else if (choice == APPEND)
		exec_append();
	else if (choice == HEREDOC)
		exec_heredoc();
}

void	wich_exec(t_data *data)
{
	t_token	*tmp;
	t_pipe	data_pipe;
	pid_t	pid;
	int		status;

	tmp = data->token;
	ft_bzero(&data_pipe, sizeof(t_pipe));
	data_pipe.data = data;
	data_pipe.fds = NULL;
	data_pipe.pid = NULL;
	data->pipe = &data_pipe;
	data_pipe.nb_pipe = pipe_in_line(data);
	data->nb_pipe = pipe_in_line(data);
	if (data->nb_pipe > 0)
	{
		ft_pipes(data);
	}
	else
	{
		if (tmp->type == BUILD)
			handle_builtins(data, tmp, STDOUT_FILENO);
		else
		{
			pid = fork();
			if (pid == -1)
				return ; // exit & redisplay
			if (pid == 0)
				exec_choice(data, tmp);
			else
			{
				waitpid(pid, &status, 0);
				if (WIFEXITED(status))
				{
					printf("Child process %d finished with exit status %d\n",
						pid, WEXITSTATUS(status));
				}
				else if (WIFSIGNALED(status))
				{
					printf("Child process %d terminated by signal %d\n", pid,
						WTERMSIG(status));
				}
			}
		}
	}
}

// echo "cc
// les
// petis
// potes"