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

void	free_parse(t_glob *glob, int i, ssize_t size_cmd)
{
	size_t	size;

	size = 0;
	if (i >= 2)
	{
		while (size_cmd != -1)
		{
			size = 0;
			while (size != glob->cmd[size_cmd].args)
			{
				free(glob->cmd[size_cmd].argv[size]);
				size++;
			}
			printf("%ld %ld\n", size_cmd, size);
			free(glob->cmd[size_cmd].argv);
			size_cmd--;
		}
	}
	if (glob->cmd[i].args && glob->cmd[i].path)
		ft_free_double_tab(glob->cmd[i].path);
	if (i >= 1)
		free(glob->cmd);
}

void	free_tab(char **tab, int lenght)
{
	if (!tab)
		return ;
	if (lenght == 0)
	{
		free(tab[0]);
		free(tab);
		return ;
	}
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
