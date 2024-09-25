/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <arbenois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 04:22:26 by arbenois          #+#    #+#             */
/*   Updated: 2024/09/25 12:42:25 by arbenois         ###   ########.fr       */
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

char	**add_tab(char *input, char **tab, size_t *size)
{
	char	**new_tab;
	size_t	i;

	new_tab = ft_cal_loc(*size + 1, sizeof(char *));
	i = 0;
	while (i != *size - 1)
	{
		new_tab[i] = ft_super_dup(tab[i], NULL);
		free(tab[i]);
		i++;
	}
	new_tab[i] = ft_super_dup(input, NULL);
	(*size)++;
	free(tab);
	return (new_tab);
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
	ssize_t	i;

	i = 0;
	cmd->heredoc.is_there_any = 0;
	if (!get_heredoc_infile(argv, cmd))
		return (free_tab(argv, ft_strlen_bis(argv)), NULL);
	if (get_heredoc_outfile(argv, cmd) == 0)
		return (free_tab(argv, ft_strlen_bis(argv)), NULL);
	if (remove_and_stock_all_heredoc(argv, cmd, i) == 1)
		return (free_tab(argv, ft_strlen_bis(argv)), NULL);
	return (argv);
}
