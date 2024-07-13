/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostr <gostr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:17:52 by gostr             #+#    #+#             */
/*   Updated: 2024/07/12 14:17:52 by gostr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_executor(t_glob *glob)
{
	int pipefd[2];
	pid_t pid;
	int fd;
	size_t	i;

	if (!glob)
		return (dprintf(2, "no glob variable \n"), (void)0);
	fd = 0;
	i = 0;
	while (i < glob->count_cmd)
	{
		if (ft_is_builtin(glob->cmd[i].command))
		{
			ft_here_doc_tester(&glob->cmd[i], &fd);
			ft_call_builtins(glob, glob->cmd[i]);
			dup2(fd, STDOUT_FILENO);
			i++;
			continue ;
		}
		if (i < glob->count_cmd -1)
		{
			if (pipe(pipefd) == -1)
				return (perror("MinisHell"), (void)0);
		}

		pid = fork();
		if (pid == -1)
			return (perror("MinisHell"), (void)0);

		if (pid == 0)
		{
			if (i < glob->count_cmd - 1)
			{
				if (dup2(pipefd[1], STDOUT_FILENO) == -1)
				{
					perror("MiniHell");
					exit(EXIT_FAILURE);
				}
			}
			if (i > 0)
			{
				if (dup2(fd, STDIN_FILENO) == -1)
				{
					perror("MiniHell");
					exit(EXIT_FAILURE);
				}
			}
			if (i < glob->count_cmd - 1)
				close(pipefd[0]);
			execve(glob->cmd[i].argv[0], glob->cmd[i].argv, glob->cmd[i].path);
			exit(EXIT_FAILURE);
		}

		waitpid(pid, NULL, 0);
		if (fd != 0)
			close(fd);
		if (i < glob->count_cmd - 1)
		{
			close(pipefd[1]);  // Fermer le descripteur d'écriture actuel
			fd = pipefd[0]; // Le prochain processus lit depuis ce pipe
		}
		i++;
	}
}