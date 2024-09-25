/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredoc_outfile.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <arbenois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 05:54:43 by arbenois          #+#    #+#             */
/*   Updated: 2024/09/25 17:14:59 by arbenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	open_outfile(t_input *cmd, char **argv, int i, int flags)
{
	cmd->heredoc.file_outfile = ft_super_dup(argv[i + 1], NULL);
	if (!cmd->heredoc.file_outfile)
		return (0);
	cmd->fd = open(argv[i + 1], flags, 0644);
	if (cmd->fd == -1)
	{
		g_error_code = 1;
		*cmd->check_m = 1;
	}
	else
		close(cmd->fd);
	remove_heredoc(argv, i, cmd);
	return (1);
}

static int	handle_outfile(char **argv, t_input *cmd, int i)
{
	if (ft_comp_str(argv[i], ">") == 1)
	{
		cmd->heredoc.is_there_any = 1;
		cmd->heredoc.type_outfile = ">";
		return (open_outfile(cmd, argv, i, O_WRONLY | O_CREAT | O_TRUNC));
	}
	if (ft_comp_str(argv[i], ">>") == 1)
	{
		cmd->heredoc.is_there_any = 1;
		cmd->heredoc.type_outfile = ">>";
		return (open_outfile(cmd, argv, i, O_WRONLY | O_CREAT | O_APPEND));
	}
	return (2);
}

int	get_heredoc_outfile(char **argv, t_input *cmd)
{
	int	i;
	int	check;

	i = cmd->args - 2;
	check = 0;
	while (i >= 0)
	{
		check = handle_outfile(argv, cmd, i);
		if (check == 0)
			return (0);
		else if (check == 1)
			break ;
		i--;
	}
	return (1);
}
