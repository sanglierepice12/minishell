/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_follow.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <arbenois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 12:28:30 by gostr             #+#    #+#             */
/*   Updated: 2024/09/25 19:24:01 by arbenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_tab(char **tab, size_t lenght)
{
	if (!tab)
		return ;
	if (lenght == 0)
	{
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
