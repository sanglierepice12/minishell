/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <arbenois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 05:49:25 by arbenois          #+#    #+#             */
/*   Updated: 2024/10/08 19:23:29 by arbenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_strdup(const char *str)
{
	char	*tab;
	size_t	i;

	if (!str)
		return (NULL);
	tab = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (str[i])
	{
		tab[i] = str[i];
		i++;
	}
	tab[i] = 0;
	return (tab);
}
