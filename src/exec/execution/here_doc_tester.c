/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_tester.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <arbenois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:34:52 by gostr             #+#    #+#             */
/*   Updated: 2024/09/25 05:23:42 by arbenois         ###   ########.fr       */
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
		if (!access(glob->cmd[i].heredoc.file_infile[0], F_OK))
			unlink(glob->cmd[i].heredoc.file_infile[0]);
		i++;
	}
}

void	ft_write_heredoc_to_file(char **lines, const char *filename)
{
	int		fd;
	size_t	i;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		ft_error(2);
	i = 0;
	while (lines[i])
	{
		write(fd, lines[i], ft_strlen(lines[i]));
		write(fd, "\n", 1);
		i++;
	}
	close(fd);
}

bool	ft_here_doc_tester(t_input *cmd)
{
	char	*temp_file;

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
	if (ft_comp_str(cmd->heredoc.type_infile, "<<"))
	{
		temp_file = ft_dup("/tmp/gbnrozahgulbazilbgebahjgb");
		if (!temp_file)
			ft_err_printf("nothing in temp file\n", 1);
		ft_write_heredoc_to_file(cmd->heredoc.file_infile, temp_file);
		cmd->fd = open(temp_file, O_RDONLY);
		if (cmd->fd == -1)
			ft_error(1);
		if (dup2(cmd->fd, STDIN_FILENO) == -1)
			ft_error(2);
		close(cmd->fd);
		unlink(temp_file);
		free(temp_file);
	}
	return (false);
}
