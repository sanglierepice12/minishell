/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <arbenois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 01:35:22 by arbenois          #+#    #+#             */
/*   Updated: 2024/09/25 17:15:10 by arbenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	handle_single_right_redir(char **argv, t_input *cmd, int i)
{
	int	fd;

	fd = open(argv[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		if (*cmd->check_m == 0)
		{
			ft_error(1);
			*cmd->check_m = 1;
		}
	}
	else
		close(fd);
	remove_heredoc(argv, i, cmd);
	return (0);
}

static int	handle_double_right_redir(char **argv, t_input *cmd, int i)
{
	int	fd;

	fd = open(argv[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		if (*cmd->check_m == 0)
		{
			ft_error(1);
			*cmd->check_m = 1;
		}
	}
	else
		close(fd);
	remove_heredoc(argv, i, cmd);
	return (0);
}

static int	handle_single_left_redir(char **argv, t_input *cmd, int i)
{
	int	fd;

	fd = open(argv[i + 1], O_WRONLY, O_RDONLY, 0644);
	if (fd == -1)
	{
		if (*cmd->check_m == 0)
		{
			free(cmd->heredoc.file_infile[0]);
			cmd->heredoc.file_infile[0] = ft_strdup(argv[i + 1]);
			g_error_code = 1;
			*cmd->check_m = 1;
		}
	}
	else
		close(fd);
	cmd->heredoc.rest_heredoc = rs_heredoc(argv, cmd, i);
	remove_heredoc(argv, i, cmd);
	return (0);
}

static int	handle_double_left_redir(char **argv, t_input *cmd, int i)
{
	cmd->heredoc.rest_heredoc = rs_heredoc(argv, cmd, i);
	remove_heredoc(argv, i, cmd);
	return (0);
}

int	remove_and_stock_all_heredoc(char **argv, t_input *cmd, unsigned long i)
{
	while (i < cmd->args)
	{
		if (ft_comp_str(argv[i], ">") == 1)
		{
			if (handle_single_right_redir(argv, cmd, i) == 1)
				return (1);
		}
		else if (ft_comp_str(argv[i], ">>") == 1)
		{
			if (handle_double_right_redir(argv, cmd, i) == 1)
				return (1);
		}
		else if (ft_comp_str(argv[i], "<") == 1)
		{
			if (handle_single_left_redir(argv, cmd, i) == 1)
				return (1);
		}
		else if (ft_comp_str(argv[i], "<<") == 1)
			handle_double_left_redir(argv, cmd, i);
		else
			i++;
	}
	return (0);
}
