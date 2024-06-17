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

static void	remove_heredoc(char **argv, int pos, t_input *command)
{
	int	i;
	int	size;

	free(argv[pos]);
	free(argv[pos + 1]);
	i = pos;
	size = command->args;
	while (i < size - 2)
	{
		argv[i] = argv[i + 2];
		i++;
	}
	argv[size - 2] = NULL;
	argv[size - 1] = NULL;
	command->args -= 2;
}

char	**check_apply_heredoc(char **argv, t_input *command)
{
	int	i;

	i = command->args - 2;
	while (i > 0)
	{
		if (ft_comp_str(argv[i], "<") == 1)
		{
			command->heredoc.type_infile = "<";
			command->heredoc.file_infile = ft_super_dup(argv[i + 1], NULL);
			remove_heredoc(argv, i, command);
			break ;
		}
		if (ft_comp_str(argv[i], "<<") == 1)
		{
			command->heredoc.type_infile = "<<";
			command->heredoc.file_infile = ft_super_dup(argv[i + 1], NULL);
			remove_heredoc(argv, i, command);
			break ;
		}
		i--;
	}
	i = command->args - 2;
	while (i > 0)
	{
		if (ft_comp_str(argv[i], ">") == 1)
		{
			command->heredoc.type_outfile = ">";
			command->heredoc.file_outfile = ft_super_dup(argv[i + 1], NULL);
			remove_heredoc(argv, i, command);
			break ;
		}
		if (ft_comp_str(argv[i], ">>") == 1)
		{
			command->heredoc.type_outfile = ">>";
			command->heredoc.file_outfile = ft_super_dup(argv[i + 1], NULL);
			remove_heredoc(argv, i, command);
			break ;
		}
		i--;
	}
	return (argv);
}
