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

static void	ft_init_path(t_glob *glob, t_env *temp)
{
	size_t	i;
	size_t	j;
	char	*temp_path;

	if (!temp)
		return (printf("Nothing in temp\n"), (void)0);
	i = 0;
	while (i < glob->cmd[i].args)
	{
		glob->cmd[i].path = ft_split(temp->path, ':');
		j = 0;
		while (glob->cmd[i].path[j])
		{
			temp_path = ft_str_join("/", glob->cmd[i].path[j]);
			free(glob->cmd->path[j]);
			glob->cmd->path[j] = ft_dup(temp_path);
			free(temp_path);
			j++;
		}
		i++;
	}
}

void	ft_init_exec(t_glob *glob)
{
	t_env	*temp;

	if (!glob)
		return (printf("Nothing in glob\n"), (void)0);
	if (glob->env)
		temp = glob->env;
	temp = ft_find_thing_in_env(&glob->env, "PATH");
	if (temp && ft_comp_str(temp->value, "PATH"))
		ft_init_path(glob, temp);
	//access et renvoie d'erreur
		//built_in ? i++;
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
