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
	int		pipefd[2];
	pid_t	pid;
	int		temp_fd_in;
	int		temp_fd_out;
	int		close_int;
	size_t	i;

	pipefd[0] = 0;
	pipefd[1] = 1;
	if (!glob)
		return (dprintf(2, "no glob variable \n"), (void)0);
	glob->cmd->fd = 0;
	i = 0;
	if (glob->count_cmd == 1 && ft_is_builtin(glob->cmd[0].command))
	{
		if (glob->cmd->heredoc.is_there_any)
		{
			temp_fd_out = 1;
			temp_fd_in = 0;
			temp_fd_out = dup(STDOUT_FILENO);
			temp_fd_in = dup(STDIN_FILENO);
		}
		if (!ft_here_doc_tester(&glob->cmd[0]))
			ft_call_builtins(glob, glob->cmd[0]);
		dup2(temp_fd_out, STDOUT_FILENO);
		dup2(temp_fd_in, STDIN_FILENO);
		close(temp_fd_in);
		close(temp_fd_out);
		//ft_reset_in_out(glob);
		return ;
	}
	while (i < glob->count_cmd)
	{
		if (i < glob->count_cmd - 1 && pipe(pipefd) == -1)
			return (perror("MinisHell"), (void)0);
		pid = fork();
		if (pid == -1)
			return (perror("MinisHell"), (void)0);
		/*-------------------------------------*/

		if (pid == 0)
		{
			if (i > 0)
			{
				if (dup2(glob->cmd->fd, STDIN_FILENO) == -1)
				{
					perror("MiniHell");
					ft_free_all(glob);
					exit(EXIT_FAILURE);
				}
			}
			if (i < glob->count_cmd - 1)
			{
				close(pipefd[0]);
				if (dup2(pipefd[1], STDOUT_FILENO) == -1)
				{
					perror("MiniHell");
					ft_free_all(glob);
					exit(EXIT_FAILURE);
				}
			}
			if (pipefd[1] > 2)
				close(pipefd[1]);
			if (ft_here_doc_tester(&glob->cmd[i]))
			{
				ft_free_all(glob);
				exit(EXIT_FAILURE);
			}
			if (ft_is_builtin(glob->cmd[i].command))
			{
				ft_call_builtins(glob, glob->cmd[i]);
				ft_free_all(glob);
				exit(EXIT_SUCCESS);
			}
			close_int = 3;
			while (close_int < 1025)
			{
				close(close_int);
				close_int++;
			}
			execve(glob->cmd[i].argv[0], glob->cmd[i].argv, glob->cmd[i].path);
			ft_free_all(glob);
			exit(EXIT_FAILURE);
		}

		/*-------------------------------------*/
		if (pipefd[1] > 2)
			close(pipefd[1]);
		if (i < glob->count_cmd - 1)
		{
			if (glob->cmd->fd > 2)
				close(glob->cmd->fd);
			glob->cmd->fd = pipefd[0];
		}
		i++;
	}
	temp_fd_in = 0;
	while (temp_fd_in != -1)
		temp_fd_in = waitpid(pid, &temp_fd_out, 0);
	if (glob->cmd->fd != 0)
		close(glob->cmd->fd);
}