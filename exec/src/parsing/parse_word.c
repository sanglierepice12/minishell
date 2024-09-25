/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <arbenois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 05:00:41 by arbenois          #+#    #+#             */
/*   Updated: 2024/09/25 05:12:10 by arbenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*expend_env_var(char *word, t_glob *glob)
{
	size_t		i;

	i = 0;
	while (word[i])
	{
		if (word[i] == '$' && (if_in_quote(word, i) == 1 \
			|| if_in_quote(word, i) == 3))
		{
			if (ft_isspace(word[i + 1]) == 1 && \
				word[i + 1] != '"' && word[i + 1] != 0)
			{
				word = expand_single_var(word, glob, &i);
				if (!word)
					return (NULL);
				i++;
			}
			else
				i++;
		}
		else
			i++;
	}
	return (word);
}

static char	*copy_word(char *input, const int *i)
{
	char	*tab;
	int		lenght;
	int		temp;
	int		y;

	temp = 0;
	lenght = ft_strlen_quote(input, *i, &temp);
	if (lenght == -1)
		return (NULL);
	tab = ft_cal_loc(lenght + 1, sizeof(char));
	if (!tab)
		return (NULL);
	tab[lenght] = '\0';
	y = 0;
	while (lenght != y)
	{
		tab[y] = input[*i + y];
		y++;
	}
	return (tab);
}

char	*parse_word(char *input, int *i, t_glob *glob)
{
	int		temp;
	char	*word;

	temp = 0;
	word = copy_word(input, i);
	if (!word)
		return (word);
	word = expend_env_var(word, glob);
	if (!word)
		return (word);
	*i += ft_strlen_quote(input, *i, &temp);
	return (word);
}
