/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <arbenois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:17:52 by gostr             #+#    #+#             */
/*   Updated: 2024/10/08 18:18:11 by arbenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_wait(int pid)
{
	int	status;
	int	i;
	int	j;

	i = 0;
	while (i != -1)
	{
		i = waitpid(0, &status, 0);
		if (i == pid)
			j = status;
	}
	if (WIFEXITED(j))
		g_error_code = WEXITSTATUS(j);
	else if (WIFSIGNALED(j))
		g_error_code = 128 + WTERMSIG(j);
}

static void	ft_cmd_fds_fix(t_glob *glob, int *pipefd, size_t *i)
{
	if (*i < glob->count_cmd - 1)
	{
		if (glob->cmd->fd > 2)
			close(glob->cmd->fd);
		glob->cmd->fd = pipefd[0];
	}
	else if (glob->cmd->fd > 2)
		close(glob->cmd->fd);
}

void	ft_pipeline(t_glob *glob)
{
	size_t	i;
	pid_t	pid;
	int		pipefd[2];

	pipefd[0] = 0;
	pipefd[1] = 1;
	i = 0;
	while (i < glob->count_cmd)
	{
		if (i < glob->count_cmd - 1 && pipe(pipefd) == -1)
			return (ft_error(1));
		pid = fork();
		if (pid == -1)
			return (ft_error(1));
		ft_handle_signal(CHILD);
		if (pid == 0)
			ft_children(glob, pipefd, &i);
		if (pipefd[1] > 2)
			close(pipefd[1]);
		ft_cmd_fds_fix(glob, pipefd, &i);
		i++;
	}
	ft_wait(pid);
}

void	ft_executor(t_glob *glob)
{
	if (!glob)
		return (dprintf(2, "no glob variable \n"), (void)0);
	glob->cmd->fd = 0;
	if (glob->count_cmd == 1 && ft_is_builtin(glob->cmd[0].command))
		return (ft_exec_built_in(glob));
	g_error_code = 0;
	ft_pipeline(glob);
	if (glob->cmd->fd != 0)
		close(glob->cmd->fd);
	ft_handle_signal(PARENT);
}
