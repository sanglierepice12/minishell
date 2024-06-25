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

void	remove_heredoc(char **argv, int pos, t_input *command)
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

static void	get_heredoc_infile(char **argv, t_input *command)
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
}

static void	get_heredoc_outfile(char **argv, t_input *command)
{
	int	i;

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

char	**check_apply_heredoc(char **argv, t_input *command)
{
	get_heredoc_infile(argv, command);
	get_heredoc_outfile(argv, command);
	remove_and_stock_all_heredoc(argv, command);
	return (argv);
}
