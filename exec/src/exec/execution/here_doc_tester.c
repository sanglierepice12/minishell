/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc_tester.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostr <gostr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:34:52 by gostr             #+#    #+#             */
/*   Updated: 2024/07/11 17:34:52 by gostr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_unlink_cmd(t_glob *glob)
{
	size_t	i;

	i = 0;
	while (i < glob->count_cmd)
	{
		if (!access(glob->cmd[i].heredoc.file_outfile, F_OK))
			unlink(glob->cmd[i].heredoc.file_outfile);
		if (!access(glob->cmd[i].heredoc.file_infile, F_OK))
			unlink(glob->cmd[i].heredoc.file_infile);
		i++;
	}
}

bool	ft_here_doc_tester(t_input *cmd, int *fd)
{
	if (ft_comp_str(cmd->heredoc.type_outfile, ">"))
	{
		*fd = open(cmd->heredoc.file_outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (*fd == -1)
		{
			perror("MiniHell");
			return (true);
		}
		if (dup2(*fd, STDOUT_FILENO) == -1)
		{
			perror("MiniHell");
			close(*fd);
			return (true);
		}
		close(*fd);
	}
	if (ft_comp_str(cmd->heredoc.type_outfile, ">>"))
	{
		*fd = open(cmd->heredoc.file_outfile, \
			O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (*fd == -1)
		{
			perror("MiniHell");
			close(*fd);
			return (true);
		}
		if (dup2(*fd, STDOUT_FILENO) == -1)
		{
			perror("MiniHell");
			return (true);
		}
		close(*fd);
	}
	if (ft_comp_str(cmd->heredoc.type_infile, "<"))
	{
		*fd = open(cmd->heredoc.file_infile, O_RDONLY);
		if (*fd == -1)
		{
			perror("MiniHell");
			return (true);
		}
		if (dup2(*fd, STDIN_FILENO) == -1)
		{
			perror("MiniHell");
			close(*fd);
			return (true);
		}
		close(*fd);
	}
	/*if (ft_comp_str(cmd->heredoc.type_infile, "<<"))
	{
		*fd = open(cmd->heredoc.file_infile, \
            O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (*fd == -1)
		{
			perror("MiniHell");
			close(*fd);
			return (true);
		}
		close(*fd);
		*fd = open("/heredoc_temp_file", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (*fd == -1)
		{
			perror("MiniHell");
			return (true);
		}
		if (dup2(STDIN_FILENO) == -1)
	 	{
			perror("MiniHell");
			return (true);
		}
		close(*fd);
		unlink("/heredoc_temp_file");
	}*/
	return (0);
}