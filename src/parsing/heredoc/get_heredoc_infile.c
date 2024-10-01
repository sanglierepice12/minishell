/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredoc_infile.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <arbenois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 05:14:16 by arbenois          #+#    #+#             */
/*   Updated: 2024/09/25 22:24:50 by arbenois         ###   ########.fr       */
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
	while (8)
	{
		input = readline("> ");
		if (g_error_code == 130)
		{
			free(input);
			ft_free_double_tab(tab);
			return (NULL);
		}
		if (input == NULL)
		{
			printf("minishell: warning: here-document"
				"delimited by end-of-file (wanted '%s')\n", word);
			return (tab);
		}
		if (ft_comp_str(input, word) == 1)
		{
			free(input);
			break ;
		}
		tab = add_tab(input, tab, &size);
		free(input);
	}
	return (tab);
}

static int	handle_single_infile(char **argv, t_input *cmd, size_t i)
{
	cmd->heredoc.is_there_any = 1;
	cmd->heredoc.type_infile = "<";
	cmd->heredoc.file_infile = ft_cal_loc(2, sizeof(char *));
	if (!cmd->heredoc.file_infile)
		return (0);
	cmd->fd = open(argv[i + 1], O_RDONLY);
	if (cmd->fd == -1)
		g_error_code = 1;
	else
		close(cmd->fd);
	cmd->heredoc.file_infile[0] = ft_super_dup(argv[i + 1], NULL);
	if (!cmd->heredoc.file_infile[0])
		return (0);
	remove_heredoc(argv, i, cmd);
	return (1);
}

static int	handle_double_infile(char **argv, t_input *cmd, size_t i)
{
	cmd->heredoc.is_there_any = 1;
	cmd->heredoc.type_infile = "<<";
	if (cmd->heredoc.file_infile != NULL)
		ft_free_double_tab(cmd->heredoc.file_infile);
	ft_handle_signal(HEREDOC);
	cmd->heredoc.file_infile = ft_write_infile(argv[i + 1]);
	if (!cmd->heredoc.file_infile)
		return (0);
	*cmd->check_m = 1;
	remove_heredoc(argv, i, cmd);
	return (1);
}

int	get_heredoc_infile(char **argv, t_input *cmd)
{
	size_t	i;

	cmd->heredoc.file_infile = NULL;
	i = cmd->args - 1;
	while (i > 0)
	{
		if (ft_comp_str(argv[i], "<") == 1)
		{
			if (!handle_single_infile(argv, cmd, i))
				return (0);
			break ;
		}
		i--;
	}
	while (cmd->args >= i)
	{
		if (ft_comp_str(argv[i], "<<") == 1)
		{
			if (!handle_double_infile(argv, cmd, i))
				return (0);
			i = 0;
		}
		i++;
	}
	return (1);
}
