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

#include "../../../include/minishell.h"

void	remove_heredoc(char **argv, int pos, t_input *cmd)
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

static void	get_heredoc_infile(char **argv, t_input *cmd)
{
	int	i;

	i = cmd->args - 2;
	while (i >= 0)
	{
		if (ft_comp_str(argv[i], "<") == 1)
		{
			cmd->heredoc.is_there_any = 1;
			cmd->heredoc.type_infile = "<";
			cmd->heredoc.file_infile = ft_super_dup(argv[i + 1], NULL);
			remove_heredoc(argv, i, cmd);
			break ;
		}
		if (ft_comp_str(argv[i], "<<") == 1)
		{
			cmd->heredoc.is_there_any = 1;
			cmd->heredoc.type_infile = "<<";
			cmd->heredoc.file_infile = ft_super_dup(argv[i + 1], NULL);
			remove_heredoc(argv, i, cmd);
			break ;
		}
		i--;
	}
}

static void	get_heredoc_outfile(char **argv, t_input *cmd)
{
	int	i;

	i = cmd->args - 2;
	while (i >= 0)
	{
		if (ft_comp_str(argv[i], ">") == 1)
		{
			cmd->heredoc.is_there_any = 1;
			cmd->heredoc.type_outfile = ">";
			cmd->heredoc.file_outfile = ft_super_dup(argv[i + 1], NULL);
			remove_heredoc(argv, i, cmd);
			break ;
		}
		if (ft_comp_str(argv[i], ">>") == 1)
		{
			cmd->heredoc.is_there_any = 1;
			cmd->heredoc.type_outfile = ">>";
			cmd->heredoc.file_outfile = ft_super_dup(argv[i + 1], NULL);
			remove_heredoc(argv, i, cmd);
			break ;
		}
		i--;
	}
}

int	ft_strlen_bis(char **tab)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return (0);
	while (tab[i])
		i++;
	return (i);
}

char	**check_apply_heredoc(char **argv, t_input *cmd)
{
	cmd->heredoc.is_there_any = 0;
	get_heredoc_infile(argv, cmd);
	get_heredoc_outfile(argv, cmd);
	remove_and_stock_all_heredoc(argv, cmd);
	return (argv);
}