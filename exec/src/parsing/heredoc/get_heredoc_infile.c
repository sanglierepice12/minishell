/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredoc_infile.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <arbenois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 05:14:16 by arbenois          #+#    #+#             */
/*   Updated: 2024/09/25 08:08:05 by arbenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static char	**ft_write_infile(char *word)
{
	char	*input;
	char	**tab;
	size_t	size;

	size = 1;
	tab = ft_cal_loc(1, sizeof(char *));
	while (1)
	{
		input = readline("> ");
		if (input == NULL)
			return (NULL);
		if (ft_comp_str(input, word) == 1)
			break ;
		tab = add_tab(input, tab, &size);
		free(input);
	}
	return (tab);
}

static int	handle_single_infile(char **argv, t_input *cmd, int i)
{
	cmd->heredoc.is_there_any = 1;
	cmd->heredoc.type_infile = "<";
	cmd->heredoc.file_infile = ft_cal_loc(2, sizeof(char *));
	if (!cmd->heredoc.file_infile)
		return (0);
	cmd->fd = open(cmd->heredoc.file_infile[0], O_RDONLY);
	if (cmd->fd == -1)
		g_error_code = 1;
	cmd->heredoc.file_infile[0] = ft_super_dup(argv[i + 1], NULL);
	if (!cmd->heredoc.file_infile[0])
		return (0);
	remove_heredoc(argv, i, cmd);
	return (1);
}

static int	handle_double_infile(char **argv, t_input *cmd, int i)
{
	cmd->heredoc.is_there_any = 1;
	cmd->heredoc.type_infile = "<<";
	cmd->heredoc.file_infile = ft_write_infile(argv[i + 1]);
	if (!cmd->heredoc.file_infile)
		return (0);
	*cmd->check_m = 1;
	remove_heredoc(argv, i, cmd);
	return (1);
}

static int	check_infile_type(char **argv, t_input *cmd, int i)
{
	if (ft_comp_str(argv[i], "<") == 1)
	{
		if (!handle_single_infile(argv, cmd, i))
			return (0);
		return (1);
	}
	else if (ft_comp_str(argv[i], "<<") == 1)
	{
		if (!handle_double_infile(argv, cmd, i))
			return (0);
		return (1);
	}
	return (2);
}

int	get_heredoc_infile(char **argv, t_input *cmd)
{
	int	i;

	i = cmd->args;
	while (i >= 0)
	{
		if (check_infile_type(argv, cmd, i) == 1)
			break ;
		else if (check_infile_type(argv, cmd, i) == 0)
			return (0);
		i--;
	}
	return (1);
}
