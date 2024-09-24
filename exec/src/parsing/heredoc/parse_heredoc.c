/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <arbenois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 04:22:26 by arbenois          #+#    #+#             */
/*   Updated: 2024/09/24 10:09:01 by arbenois         ###   ########.fr       */
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

static char	**add_tab(char *input, char **tab, size_t *size)
{
	char	**new_tab;
	size_t	i;

	new_tab = ft_cal_loc(*size + 1, sizeof(char *));
	i = 0;
	while (i != *size - 1)
	{
		new_tab[i] = ft_super_dup(tab[i], NULL);
		i++;
	}
	new_tab[i] = ft_super_dup(input, NULL);
	(*size)++;
	free(tab);
	return (new_tab);
}

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
		/*ft_handle_signal(HEREDOC);
		if (g_error_code == 130)
			return (tab);*/
		tab = add_tab(input, tab, &size);
		free(input);
	}
	return (tab);
}

static void	handle_single_infile(char **argv, t_input *cmd, int i)
{
	cmd->heredoc.is_there_any = 1;
	cmd->heredoc.type_infile = "<";
	cmd->heredoc.file_infile = ft_cal_loc(2, sizeof(char *));
	cmd->heredoc.file_infile[0] = ft_super_dup(argv[i + 1], NULL);
	remove_heredoc(argv, i, cmd);
}

static int	handle_double_infile(char **argv, t_input *cmd, int i)
{
	cmd->heredoc.is_there_any = 1;
	cmd->heredoc.type_infile = "<<";
	cmd->heredoc.file_infile = ft_write_infile(argv[i + 1]);
	if (!cmd->heredoc.file_infile)
		return (0);
	remove_heredoc(argv, i, cmd);
	return (1);
}

static int	check_infile_type(char **argv, t_input *cmd, int i)
{
	if (ft_comp_str(argv[i], "<") == 1)
	{
		handle_single_infile(argv, cmd, i);
		return (1);
	}
	if (ft_comp_str(argv[i], "<<") == 1)
	{
		if (!handle_double_infile(argv, cmd, i))
			return (0);
		return (1);
	}
	return (0);
}

static void	get_heredoc_infile(char **argv, t_input *cmd)
{
	int	i;

	i = cmd->args - 2;
	while (i >= 0)
	{
		if (check_infile_type(argv, cmd, i))
			break ;
		i--;
	}
}

static int	get_heredoc_outfile(char **argv, t_input *cmd)
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
			cmd->fd = open(argv[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (cmd->fd == -1)
				return (ft_error(1), 0);
			close(cmd->fd),
			remove_heredoc(argv, i, cmd);
			break ;
		}
		if (ft_comp_str(argv[i], ">>") == 1)
		{
			cmd->heredoc.is_there_any = 1;
			cmd->heredoc.type_outfile = ">>";
			cmd->heredoc.file_outfile = ft_super_dup(argv[i + 1], NULL);
			cmd->fd = open(argv[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (cmd->fd == -1)
				return (ft_error(1), true);
			close(cmd->fd);
			remove_heredoc(argv, i, cmd);
			break ;
		}
		i--;
	}
	return (1);
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
	unsigned long	i;

	i = 0;
	cmd->heredoc.is_there_any = 0;
	get_heredoc_infile(argv, cmd);
	if (get_heredoc_outfile(argv, cmd) == 0)
		return (NULL);
	if (remove_and_stock_all_heredoc(argv, cmd, i) == 1)
		return (NULL);
	return (argv);
}
