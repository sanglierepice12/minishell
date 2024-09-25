/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_word_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <arbenois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 05:09:26 by arbenois          #+#    #+#             */
/*   Updated: 2024/09/25 05:10:32 by arbenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*allocate_special_char(char c)
{
	char	*tab;

	tab = calloc(2, sizeof(char));
	if (!tab)
		return (NULL);
	tab[0] = c;
	return (tab);
}

static size_t	get_word_length(const char *input, size_t i)
{
	size_t	length;

	length = 0;
	while (input[i + length] && input[i + length] != ' ' && \
		input[i + length] != 39 && input[i + length] != 34 && \
		input[i + length] != '$')
		length++;
	return (length);
}

static char	*allocate_and_copy_word(const char *input, size_t i, size_t length)
{
	char		*tab;
	size_t		j;

	tab = calloc(length + 1, sizeof(char));
	if (!tab)
		return (NULL);
	j = 0;
	while (j < length)
	{
		tab[j] = input[i + j];
		j++;
	}
	return (tab);
}

char	*copy_word_env(char *input, size_t i)
{
	size_t	length;

	if (input[i] == '?' || input[i] == '$')
		return (allocate_special_char(input[i]));
	length = get_word_length(input, i);
	return (allocate_and_copy_word(input, i, length));
}
