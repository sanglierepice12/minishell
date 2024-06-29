/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 00:22:35 by arbenois          #+#    #+#             */
/*   Updated: 2024/06/15 00:22:36 by arbenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	should_skip_quote(char c, int *checkquote)
{
	if (c == 39 && *checkquote == 0)
	{
		*checkquote = 1;
		return (1);
	}
	else if (c == 34 && *checkquote == 0)
	{
		*checkquote = 2;
		return (1);
	}
	else if (c == 39 && *checkquote == 1)
	{
		*checkquote = 0;
		return (1);
	}
	else if (c == 34 && *checkquote == 2)
	{
		*checkquote = 0;
		return (1);
	}
	return (0);
}

char	*allocate_newtab(char *input, int i, int *lenght)
{
	int		temp;
	char	*newtab;

	temp = 0;
	*lenght = ft_strlen_quote(input, i, &temp);
	if (*lenght == -1)
		return (NULL);
	if (temp >= 1)
		*lenght -= temp * 2;
	newtab = malloc((*lenght + 1) * sizeof(char));
	if (!newtab)
		return (NULL);
	newtab[*lenght] = 0;
	return (newtab);
}

void	copy_without_quotes(char *tab, char *newtab, int lenght)
{
	int	skip;
	int	checkquote;
	int	temp;

	skip = 0;
	checkquote = 0;
	temp = 0;
	while (temp != lenght)
	{
		if (should_skip_quote(tab[temp + skip], &checkquote))
			skip++;
		else
		{
			newtab[temp] = tab[temp + skip];
			temp++;
		}
	}
}

char	*delete_quote(char *tab, int i)
{
	int		lenght;
	char	*newtab;

	newtab = allocate_newtab(tab, i, &lenght);
	if (!newtab)
		return (free(tab), NULL);
	copy_without_quotes(tab, newtab, lenght);
	free(tab);
	return (newtab);
}
