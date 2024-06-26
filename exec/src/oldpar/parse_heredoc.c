/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 04:22:26 by arbenois          #+#    #+#             */
/*   Updated: 2024/06/17 04:22:28 by arbenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	remove_heredoc(char **argv, int pos, t_input *cmd)
{
	int	i;
	int	size;

	free(argv[pos]);
	free(argv[pos + 1]);
	i = pos;
	size = cmd->args;
	while (i < size - 2)
	{
		argv[i] = argv[i + 2];
		i++;
	}
	argv[size - 2] = NULL;
	argv[size - 1] = NULL;
	cmd->args -= 2;
}

char	**check_apply_heredoc(char **argv, t_input *cmd)
{
	int	i;

	i = cmd->args - 2;
	while (i > 0)
	{
		if (ft_comp_str(argv[i], "<") == 1)
		{
			cmd->heredoc.type_infile = "<";
			cmd->heredoc.file_infile = ft_super_dup(argv[i + 1], NULL);
			remove_heredoc(argv, i, cmd);
			break ;
		}
		if (ft_comp_str(argv[i], "<<") == 1)
		{
			cmd->heredoc.type_infile = "<<";
			cmd->heredoc.file_infile = ft_super_dup(argv[i + 1], NULL);
			remove_heredoc(argv, i, cmd);
			break ;
		}
		i--;
	}
	i = cmd->args - 2;
	while (i > 0)
	{
		if (ft_comp_str(argv[i], ">") == 1)
		{
			cmd->heredoc.type_outfile = ">";
			cmd->heredoc.file_outfile = ft_super_dup(argv[i + 1], NULL);
			remove_heredoc(argv, i, cmd);
			break ;
		}
		if (ft_comp_str(argv[i], ">>") == 1)
		{
			cmd->heredoc.type_outfile = ">>";
			cmd->heredoc.file_outfile = ft_super_dup(argv[i + 1], NULL);
			remove_heredoc(argv, i, cmd);
			break ;
		}
		i--;
	}
	return (argv);
}
