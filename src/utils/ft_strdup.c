/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <arbenois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 05:49:25 by arbenois          #+#    #+#             */
/*   Updated: 2024/09/25 05:50:14 by arbenois         ###   ########.fr       */
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

char	**ft_strstrdup(char **str)
{
	char	**tab;
	size_t	i;

	i = 0;
	tab = ft_cal_loc(ft_strlen_bis(str), sizeof(char *));
	while (str[i])
	{
		tab[i] = ft_strdup(str[i]);
		if (!tab[i])
			return (free_tab(tab, ft_strlen_bis(str)), NULL);
		i++;
	}
	return (tab);
}
