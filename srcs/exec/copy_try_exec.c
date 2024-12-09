/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_try_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:34:54 by saberton          #+#    #+#             */
/*   Updated: 2024/12/07 19:13:49 by saberton         ###   ########.fr       */
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
	if (tok->type != BUILD)
	{
		data->exit_code = execve(cmd_path, cmd, env);
		if (data->exit_code == -1)
		{
			free(cmd_path);
			perror("Error executing execve\n");
			exit_prog(data, EXIT_FAILURE); // a change pour re display readline(minishell$ ) = exit_prompt
		}
		// ft_putstrfd(data->exit_code, 2);  // display exit_code avtn de quitte OU rediplay prompt
	}
	free(cmd_path);
}

// static void	maj_originals_fds(t_data *data)
// {
// 	dup2(data->pipe->original_fd[0], STDIN_FILENO);
// 	dup2(data->pipe->original_fd[1], STDOUT_FILENO);
// }

static void	ft_pipes(t_data *data, t_token *tok, char **cmd)
{
	if (pipe(data->pipe->pipe_fds) == -1)
		exit_prog(data, EXIT_FAILURE);
	data->pipe->exec_pid = fork();
	if (data->pipe->exec_pid == 0) { // Processus enfant
		if (data->pipe->prev_fd != -1) {
			dup2(data->pipe->prev_fd, STDIN_FILENO); // Lire l'entrée précédente
			close(data->pipe->prev_fd);
		}
		if (tok->next) { // Si ce n'est pas la dernière commande, écrire dans le pipe
			dup2(data->pipe->pipe_fds[1], STDOUT_FILENO);
		}
		close(data->pipe->pipe_fds[0]);
		close(data->pipe->pipe_fds[1]);
		
		if (tok->type == BUILD) {
			handle_builtins(data, tok, STDOUT_FILENO);
			exit(EXIT_SUCCESS);
		} else {
			exec_cmd(data, data->env, cmd, tok);
		}
	} 
	else { // Processus parent
		if (data->pipe->prev_fd != -1) {
			close(data->pipe->prev_fd);
		}
		data->pipe->prev_fd = data->pipe->pipe_fds[0]; // Conserver la lecture du pipe
		close(data->pipe->pipe_fds[1]); // Fermer l'écriture
		waitpid(data->pipe->exec_pid, &data->exit_code, 0);
	}
	
	// maj_originals_fds(data);
	// dup2(data->pipe->original_fd[0], STDIN_FILENO);
	// dup2(data->pipe->original_fd[1], STDOUT_FILENO);
	// if (*(data->pipe->fds) == 0)
	// {
	// 	if (tok->type == BUILD)
	// 	{
	// 		dup2(data->pipe->fds[0], STDIN_FILENO);
	// 		dup2(data->pipe->fds[2], STDOUT_FILENO);
	// 		handle_builtins(data, tok, STDOUT_FILENO);
	// 	}
	// 	else
	// 	{
	// 		data->pipe->exec_pid = fork();
	// 		dup2(data->pipe->fds[0], STDIN_FILENO);
	// 		dup2(data->pipe->fds[2], STDOUT_FILENO);
	// 		if (data->pipe->exec_pid == -1)
	// 			exit_prog(data, EXIT_FAILURE);
	// 		if (data->pipe->exec_pid == 0)
	// 			exec_cmd(data, data->env, cmd, tok);
	// 		else
	// 			waitpid(data->pipe->exec_pid, NULL, 0);
	// 		// {
	// 		// 	dup2(data->pipe->fds[4], STDIN_FILENO);
	// 		// }
	// 		// exec_cmd(data, data->env, cmd, tok);
	// 	}
	// }
	// else if (*(data->pipe->fds) != 0)
	// {
	// 	// maj_originals_fds(data);
	// 	if (tok->type == BUILD)
	// 	{
	// 		dup2(data->pipe->fds[1], STDIN_FILENO);
	// 		dup2(data->pipe->fds[3], STDOUT_FILENO);
	// 		handle_builtins(data, tok, STDOUT_FILENO);
	// 	}
	// 	else
	// 	{
	// 		data->pipe->exec_pid = fork();
	// 		dup2(data->pipe->fds[1], STDIN_FILENO);
	// 		dup2(data->pipe->fds[3], STDOUT_FILENO);
	// 		if (data->pipe->exec_pid == -1)
	// 			exit_prog(data, EXIT_FAILURE);
	// 		if (data->pipe->exec_pid == 0)
	// 			exec_cmd(data, data->env, cmd, tok);
	// 		else
	// 			waitpid(data->pipe->exec_pid, NULL, 0);
	// 		// 	dup2(data->pipe->fds[4], STDIN_FILENO);
	// 		// else
	// 		// exec_cmd(data, data->env, cmd, tok);
	// 	}
	// }
	
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
		if (data->nb_pipe < 0)
		{
			if (tok->type == BUILD)
				handle_builtins(data, tok, STDOUT_FILENO);
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
	t_pipe	data_pipe;
	pid_t	pid;

	tmp = data->token;
	data_pipe.data = data;
	data->pipe = &data_pipe;
	data_pipe.nb_pipe = pipe_in_line(data);
	data->nb_pipe = pipe_in_line(data);
	if (data->nb_pipe >= 0)
	{
		// data->pipe->fds = malloc(sizeof(int) * (data->pipe->nb_pipe * 2 + 2));
		// data->pipe->original_fd[0] = dup(STDIN_FILENO);
		// data->pipe->original_fd[1] = dup(STDOUT_FILENO);
		// data->pipe->fds[0] = data->pipe->original_fd[0];
		// data->pipe->fds[3] = data->pipe->original_fd[1];
		// pipe(data->pipe->pipe_fds);
		// data->pipe->fds[1] = data->pipe->pipe_fds[0];
		// data->pipe->fds[2] = data->pipe->pipe_fds[1];
		while (tmp)
		{
			exec_choice(data, tmp);
			*(data->pipe->fds)+=1;
			data->nb_pipe--;
			tmp = recup_tok_after_pipe(tmp);
		}
		if (data_pipe.prev_fd != -1) {
			close(data_pipe.prev_fd);
		}
		while (wait(NULL) > 0)
			;
		printf("je suis sur le fd [%d]\n", *(data->pipe->fds));
	}
	else
	{
		if (tmp->type == BUILD)
			handle_builtins(data, tmp, STDOUT_FILENO);
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
