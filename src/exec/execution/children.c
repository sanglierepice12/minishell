/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <arbenois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:41:27 by gostr             #+#    #+#             */
/*   Updated: 2024/10/08 19:48:47 by arbenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	ft_close_pipe(void)
{
	int	k;

	k = 2;
	while (k++, k < 1024)
		close(k);
}

static void	ft_exec_child(t_glob *glob, size_t *i, char **envp)
{
	ft_close_pipe();
	execve(glob->cmd[*i].argv[0], glob->cmd[*i].argv, envp);
}

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
		ft_call_builtins(glob, glob->cmd[0], NULL);
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

void	ft_children(t_glob *glob, int pipefd[2], size_t *i)
{
	char	**envp;

	envp = ft_env_to_tab(&glob->env, glob);
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
		close(glob->cmd->fd);
	else if (ft_is_builtin(glob->cmd[*i].command))
	{
		ft_call_builtins(glob, glob->cmd[*i], envp);
		close(glob->cmd->fd);
	}
	else
		ft_exec_child(glob, i, envp);
	return (ft_free_double_tab(envp), ft_exit(glob, NULL));
}
