/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lib.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 05:06:26 by arbenois          #+#    #+#             */
/*   Updated: 2024/05/29 05:06:28 by arbenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_tab(char **tab, int lenght)
{
	while (lenght != 0)
	{
		free(tab[lenght]);
		lenght--;
	}
	free(tab);
}
