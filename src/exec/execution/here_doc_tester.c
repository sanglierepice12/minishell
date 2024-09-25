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
	if (ft_right_operand(cmd))
		return (true);
	if (ft_right_operand_double(cmd))
		return (true);
	if (ft_left_operand(cmd))
		return (true);
	if (ft_heredoc(cmd))
		return (true);
	return (false);
}
