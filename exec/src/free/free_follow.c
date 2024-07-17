/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_follow.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostr <gostr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 12:28:30 by gostr             #+#    #+#             */
/*   Updated: 2024/07/17 12:29:33 by gostr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_parse(t_glob *glob, int i)
{
	int	size;

	if (i >= 2)
	{
		size = glob->cmd->args - 1;
		while (size != -1)
		{
			free(glob->cmd->argv[size]);
			size--;
		}
		free(glob->cmd->argv);
	}
	if (glob->cmd->args && glob->cmd->path)
		ft_free_double_tab(glob->cmd->path);
	if (i >= 1)
		free(glob->cmd);
}

void	free_tab(char **tab, int lenght)
{
	if (!tab)
		return ;
	while (lenght != 0)
	{
		lenght--;
		free(tab[lenght]);
	}
	free(tab);
}

void	ft_free_double_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
