/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_dup2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertille <bertille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 08:51:10 by saberton          #+#    #+#             */
/*   Updated: 2024/12/15 21:23:16 by bertille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	first_pipe(t_data *data)
{
	if (data->redir->infile != -1)
	{
		if (dup2(data->redir->infile, STDIN_FILENO) == -1)
			failed_mess(data, "dup2 input failed", 1);
		close(data->redir->infile);
		data->redir->infile = -1;
	}
	if (data->redir->outfile != -1)
	{
		if (dup2(data->redir->outfile, STDOUT_FILENO) == -1)
			failed_mess(data, "dup2 output failed", 1);
		close(data->redir->outfile);
		data->redir->outfile = -1;
	}
	else if (data->pipe->nb_pipe)
	{
		if (dup2(data->pipe->fds[0][1], STDOUT_FILENO) == -1)
			failed_mess(data, "dup2 pipe write failed", 1);
	}
}

static void	mid_pipe(t_data *data, int pipe_num)
{
	if (data->redir->infile != -1)
	{
		if (dup2(data->redir->infile, STDIN_FILENO) == -1)
			failed_mess(data, "dup2 input failed", 1);
		close(data->redir->infile);
		data->redir->infile = -1;
	}
	else
	{
		if (dup2(data->pipe->fds[pipe_num - 1][0], STDIN_FILENO) == -1)
			failed_mess(data, "dup2 pipe read failed", 1);
	}
	if (data->redir->outfile != -1)
	{
		if (dup2(data->redir->outfile, STDOUT_FILENO) == -1)
			failed_mess(data, "dup2 output failed", 1);
		close(data->redir->outfile);
		data->redir->outfile = -1;
	}
	else
	{
		if (dup2(data->pipe->fds[pipe_num][1], STDOUT_FILENO) == -1)
			failed_mess(data, "dup2 pipe write failed", 1);
	}
}

static void	last_pipe(t_data *data, int pipe_num)
{
	if (data->redir->infile != -1)
	{
		if (dup2(data->redir->infile, STDIN_FILENO) == -1)
			failed_mess(data, "dup2 input failed", 1);
		close(data->redir->infile);
		data->redir->infile = -1;
	}
	else if (pipe_num)
	{
		if (dup2(data->pipe->fds[pipe_num - 1][0], STDIN_FILENO) == -1)
			failed_mess(data, "dup2 pipe read failed", 1);
	}
	if (data->redir->outfile != -1)
	{
		if (dup2(data->redir->outfile, STDOUT_FILENO) == -1)
			failed_mess(data, "dup2 output failed", 1);
		close(data->redir->outfile);
		data->redir->outfile = -1;
	}
}

void	exec_dup2_pipe(t_data *data, t_token *tmp, int i)
{
	if (i == 0)
		first_pipe(data);
	else if (!recup_tok_after_pipe(tmp))
		last_pipe(data, i);
	else
		mid_pipe(data, i);
	// free_close_fds(data, i);
}

void	exec_dup2_simple(t_data *data)
{
	first_pipe(data);
	last_pipe(data, 0);
}

// void free_close_fds(t_data *data, int keep_index)
// {
//     int i = 0;
	
//     // Close read and write ends of all pipes, except the one we want to keep
//     while (data->pipe->fds && data->pipe->fds[i])
//     {
//         if (i != keep_index)
//         {
//             if (data->pipe->fds[i][0] > 0)
//                 close(data->pipe->fds[i][0]);
//             if (data->pipe->fds[i][1] > 0)
//                 close(data->pipe->fds[i][1]);
//         }
//         i++;
//     }
// }


// void exec_dup2_pipe(t_data *data, t_token *tmp, int i)
// {
// 	// Sauvegarder les descripteurs originaux si nécessaire
// 	int stdin_backup = dup(STDIN_FILENO);
// 	int stdout_backup = dup(STDOUT_FILENO);
	
// 	// Gérer l'entrée
// 	if (data->redir->infile != -1) {
// 		if (dup2(data->redir->infile, STDIN_FILENO) == -1) {
// 			failed_mess(data, "Erreur de redirection d'entrée", 1);
// 			close(stdin_backup);
// 			close(stdout_backup);
// 			exit(1);
// 		}
// 		close(data->redir->infile);
// 	}
	
// 	// Gérer les pipes
// 	if (data->pipe->nb_pipe > 0) {
// 		// Première commande
// 		if (i == 0) {
// 			if (dup2(data->pipe->fds[0][1], STDOUT_FILENO) == -1) {
// 				failed_mess(data, "Erreur d'écriture sur le premier pipe", 1);
// 				dup2(stdout_backup, STDOUT_FILENO);
// 				close(stdin_backup);
// 				close(stdout_backup);
// 				exit(1);
// 			}
// 		}
// 		// Dernière commande
// 		else if (!recup_tok_after_pipe(tmp)) {
// 			// Lire du pipe précédent
// 			if (dup2(data->pipe->fds[i - 1][0], STDIN_FILENO) == -1) {
// 				failed_mess(data, "Erreur de lecture du pipe précédent", 1);
// 				dup2(stdin_backup, STDIN_FILENO);
// 				close(stdin_backup);
// 				close(stdout_backup);
// 				exit(1);
// 			}
			
// 			// Rediriger la sortie si nécessaire
// 			if (data->redir->outfile != -1) {
// 				if (dup2(data->redir->outfile, STDOUT_FILENO) == -1) {
// 					failed_mess(data, "Erreur de redirection de sortie", 1);
// 					dup2(stdout_backup, STDOUT_FILENO);
// 					close(stdin_backup);
// 					close(stdout_backup);
// 					exit(1);
// 				}
// 				close(data->redir->outfile);
// 			}
// 		}
// 		// Commandes intermédiaires
// 		else {
// 			// Lire du pipe précédent
// 			if (dup2(data->pipe->fds[i - 1][0], STDIN_FILENO) == -1) {
// 				failed_mess(data, "Erreur de lecture du pipe intermédiaire", 1);
// 				dup2(stdin_backup, STDIN_FILENO);
// 				close(stdin_backup);
// 				close(stdout_backup);
// 				exit(1);
// 			}
			
// 			// Écrire dans le pipe courant
// 			if (dup2(data->pipe->fds[i][1], STDOUT_FILENO) == -1) {
// 				failed_mess(data, "Erreur d'écriture du pipe intermédiaire", 1);
// 				dup2(stdout_backup, STDOUT_FILENO);
// 				close(stdin_backup);
// 				close(stdout_backup);
// 				exit(1);
// 			}
// 		}
// 	}
	
// 	// Fermer les descripteurs
// 	close(stdin_backup);
// 	close(stdout_backup);
	
// 	// Fermer tous les descripteurs de fichiers de pipe
// 	free_close_fds(data, 1);
// }