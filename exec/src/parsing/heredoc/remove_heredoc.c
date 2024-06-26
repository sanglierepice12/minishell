/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 01:35:22 by arbenois          #+#    #+#             */
/*   Updated: 2024/06/25 01:35:23 by arbenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static char	**ft_realloc(char **heredoc, char **tab)
{
	int		i;
	int		size;
	int		lenght;
	char	**realloc;

	i = 0;
	lenght = ft_strlen_bis(heredoc);
	realloc = malloc((lenght + 3) * sizeof(char *));
	while (i != lenght)
	{
		realloc[i] = heredoc[i];
		i++;
	}
	size = 0;
	while (i != lenght + 2)
	{
		realloc[i] = tab[size];
		i++;
		size++;
	}
	realloc[i] = NULL;
	if (ft_strlen_bis(heredoc) != 0)
		free(heredoc);
	return (realloc);
}

static char	**rs_heredoc(char **argv, t_input *cmd, int i)
{
	char	**tab;
	char	**temp;

	tab = malloc(3 * sizeof(char *));
	if (argv[i + 1] != NULL)
	{
		tab[0] = ft_dup(argv[i]);
		tab[1] = ft_dup(argv[i + 1]);
		tab[2] = NULL;
	}
	temp = ft_realloc(cmd->heredoc.rest_heredoc, tab);
	return (temp);
}

void	remove_and_stock_all_heredoc(char **argv, t_input *cmd)
{
	int	i;

	i = cmd->args - 2;
	while (i > 0)
	{
		if (ft_comp_str(argv[i], ">") == 1)
		{
			cmd->heredoc.rest_heredoc = rs_heredoc(argv, cmd, i);
			remove_heredoc(argv, i, cmd);
		}
		else if (ft_comp_str(argv[i], ">>") == 1)
		{
			cmd->heredoc.rest_heredoc = rs_heredoc(argv, cmd, i);
			remove_heredoc(argv, i, cmd);
		}
		i--;
	}
}
