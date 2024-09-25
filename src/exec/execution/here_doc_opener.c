/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_opener.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsuter <gsuter@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:32:06 by gsuter            #+#    #+#             */
/*   Updated: 2024/09/25 18:32:06 by gsuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

bool	ft_right_operand(t_input *cmd)
{
	if (ft_comp_str(cmd->heredoc.type_outfile, ">"))
	{
		cmd->fd = open(cmd->heredoc.file_outfile, O_WRONLY \
			| O_CREAT | O_TRUNC, 0644);
		if (cmd->fd == -1)
			return (ft_error(1), true);
		if (dup2(cmd->fd, 1) == -1)
			return (perror("miniHell"), true);
		close(cmd->fd);
	}
	return (false);
}

bool	ft_right_operand_double(t_input *cmd)
{
	if (ft_comp_str(cmd->heredoc.type_outfile, ">>"))
	{
		cmd->fd = open(cmd->heredoc.file_outfile, O_WRONLY \
			| O_CREAT | O_APPEND, 0644);
		if (cmd->fd == -1)
			return (ft_error(1), true);
		if (dup2(cmd->fd, 1) == -1)
			return (ft_error(2), true);
		close(cmd->fd);
	}
	return (false);
}

bool	ft_left_operand(t_input *cmd)
{
	if (ft_comp_str(cmd->heredoc.type_infile, "<"))
	{
		cmd->fd = open(cmd->heredoc.file_infile[0], O_RDONLY);
		if (cmd->fd == -1)
			return (ft_error(1), true);
		if (dup2(cmd->fd, STDIN_FILENO) == -1)
		{
			close(cmd->fd);
			return (ft_error(2), true);
		}
		close(cmd->fd);
	}
	return (false);
}

bool	ft_heredoc(t_input *cmd)
{
	char	*temp_file;

	if (ft_comp_str(cmd->heredoc.type_infile, "<<"))
	{
		temp_file = ft_dup("/tmp/gbnrozahgulbazilbgebahjgbggbdsbfdbvvfd");
		if (!temp_file)
			ft_err_printf("nothing in temp file\n", 1);
		ft_write_heredoc_to_file(cmd->heredoc.file_infile, temp_file);
		cmd->fd = open(temp_file, O_RDONLY);
		if (cmd->fd == -1)
			return (ft_error(1), true);
		if (dup2(cmd->fd, STDIN_FILENO) == -1)
			return (ft_error(2), true);
		close(cmd->fd);
		unlink(temp_file);
		free(temp_file);
	}
	return (false);
}
