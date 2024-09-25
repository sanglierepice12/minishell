/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <arbenois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:41:27 by gostr             #+#    #+#             */
/*   Updated: 2024/09/25 07:46:45 by arbenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_exec_built_in(t_glob *glob)
{
	int		temp_fd_in;
	int		temp_fd_out;

	temp_fd_out = 4;
	temp_fd_in = 4;
	if (glob->cmd->heredoc.is_there_any)
	{
		temp_fd_out = dup(STDOUT_FILENO);
		temp_fd_in = dup(STDIN_FILENO);
		if (temp_fd_in == -1 || temp_fd_out == -1)
			return (ft_error(1));
	}
	if (ft_here_doc_tester(glob->cmd) == false)
		ft_call_builtins(glob, glob->cmd[0]);
	if (glob->cmd->heredoc.is_there_any)
	{
		if (dup2(temp_fd_out, STDOUT_FILENO) == -1)
			return (ft_error(1));
		if (dup2(temp_fd_in, STDIN_FILENO))
			return (ft_error(1));
	}
	close(temp_fd_in);
	close(temp_fd_out);
}

void	ft_children(t_glob *glob, int pipefd[2], const size_t *i)
{
	if (*i > 0)
	{
		ft_dup_two(glob->cmd->fd, STDIN_FILENO, glob);
		close(pipefd[0]);
	}
	if (*i < glob->count_cmd - 1)
	{
		close(pipefd[0]);
		ft_dup_two(pipefd[1], STDOUT_FILENO, glob);
	}
	if (pipefd[1] > 2)
		close(pipefd[1]);
	if (ft_here_doc_tester(&glob->cmd[*i]))
	{
		close(glob->cmd->fd);
		ft_exit(glob, NULL);
	}
	if (ft_is_builtin(glob->cmd[*i].command))
	{
		ft_call_builtins(glob, glob->cmd[*i]);
		close(glob->cmd->fd);
		ft_exit(glob, NULL);
	}
	execve(glob->cmd[*i].argv[0], glob->cmd[*i].argv, glob->cmd[*i].path);
	ft_exit(glob, NULL);
}
