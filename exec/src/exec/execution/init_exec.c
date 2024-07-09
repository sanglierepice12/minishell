/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostr <gostr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:47:43 by gostr             #+#    #+#             */
/*   Updated: 2024/07/09 16:47:43 by gostr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_init_exec(t_glob *glob)
{
	(void)glob;
	//si (env->value == PATH) ok ?
		//setpath glob->cmd[i]->cmd;
			//si cmd = built_in -> path = NULL;
			//cmd.path = ft_split(env.value == PATH, :);
		//-> acces_cmd();
			//si access fonctionne direct tu met dedans else :
			//temp = strjoin (path[i], '/');
			//path[i] = strjoin(temp, cmd.command); exemple "/bin/ls
			//access (path[i] , F_OK, X_OK);
			//cmd.command = path[i];
		//execute_pipeline(glob.cmd)
			//pipefd[2];
			//pid;
			// fd = 0 pour le stdin
}

/*
void execute_pipeline(Command **cmds, int num_cmds) {
	int pipefd[2];
	pid_t pid;
	int in_fd = 0;  // Le premier processus lit de stdin

	for (int i = 0; i < num_cmds; i++) {
		// Vérifier et exécuter les builtins dans le processus parent
		if (execute_builtin(cmds[i])) {
			continue; // Passer à la prochaine commande
		}

		if (i < num_cmds - 1) {
			if (pipe(pipefd) == -1) {
				perror("pipe");
				exit(EXIT_FAILURE);
			}
		}

		if ((pid = fork()) == 0) {
			// Dans le processus enfant
			if (i < num_cmds - 1) {
				if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
					perror("dup2");
					exit(EXIT_FAILURE);
				}
			}
			if (i > 0) {
				if (dup2(in_fd, STDIN_FILENO) == -1) {
					perror("dup2");
					exit(EXIT_FAILURE);
				}
			}

			// Fermer les descripteurs inutilisés dans le processus enfant
			if (i < num_cmds - 1) {
				close(pipefd[0]);
				close(pipefd[1]);
			}
			execvp(cmds[i]->command, cmds[i]->argv);
			perror("execvp");
			exit(EXIT_FAILURE);
		} else if (pid < 0) {
			perror("fork");
			exit(EXIT_FAILURE);
		}

		// Processus parent
		waitpid(pid, NULL, 0);

		// Fermer le descripteur de lecture précédent si ce n'est pas stdin
		if (in_fd != 0) {
			close(in_fd);
		}

		// Si ce n'est pas la dernière commande, mettre à jour le descripteur de fichier d'entrée
		if (i < num_cmds - 1) {
			close(pipefd[1]);  // Fermer le descripteur d'écriture actuel
			in_fd = pipefd[0]; // Le prochain processus lit depuis ce pipe
		}
	}
}*/
