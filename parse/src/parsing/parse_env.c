/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 04:21:46 by arbenois          #+#    #+#             */
/*   Updated: 2024/06/17 04:21:47 by arbenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*copy_word_env(char *input, int i)
{
	char	*tab;
	int		lenght;

	lenght = 0;
	while (input[i + lenght])
	{
		if (input[i + lenght] == ' ' || input[i + lenght] == 39 \
			|| input[i + lenght] == 34)
			break ;
		lenght++;
	}
	tab = malloc(lenght * sizeof(char));
	if (!tab)
		return (NULL);
	lenght = 0;
	while (input[i + lenght])
	{
		if (input[i + lenght] == ' ' || input[i + lenght] == 39 \
			|| input[i + lenght] == 34)
			break ;
		tab[lenght] = input[i + lenght];
		lenght++;
	}
	tab[lenght] = 0;
	return (tab);
}

static char	*alloc_new_word(char *word, int i, char *path)
{
	char	*tab;
	int		length;

	length = ft_strlen(word) - ft_strlen(copy_word_env(word, i)) \
			+ ft_strlen(path);
	if (length == 0)
	{
		tab = malloc(1 * sizeof(char));
		tab[0] = 0;
		return (tab);
	}
	tab = malloc(length * sizeof(char));
	tab[length] = 0;
	return (tab);
}

static char	*replace_env_word(char *word, int i, char *path)
{
	char	*tab;
	int		size;
	int		index;

	tab = alloc_new_word(word, i, path);
	size = 0;
	while (size != i)
	{
		tab[size] = word[size];
		size++;
	}
	index = ft_strlen(path) - 1;
	while (index != -1)
	{
		tab[size + index] = path[index];
		index--;
	}
	size += ft_strlen(path);
	i += ft_strlen(copy_word_env(word, i));
	while (word[i])
		tab[size++] = word[i++];
	free(word);
	return (tab);
}

static char	*find_env_var(char *word, t_glob *glob, int i, char *temp)
{
	t_env	*env;
	int		check_sup;

	check_sup = 1;
	env = glob->env;
	while (env != NULL)
	{
		if (strcmp(env->value, temp) == 0)
		{
			word = replace_env_word(word, i, env->path);
			check_sup = 2;
			break ;
		}
		env = env->next;
	}
	if (check_sup == 1)
		word = replace_env_word(word, i, "");
	if (!word)
		return (NULL);
	return (word);
}

char	*expend_env_var(char *word, t_glob *glob)
{
	char	*temp;
	int		i;

	i = 0;
	while (word[i])
	{
		if (word[i] == '$' && (if_in_quote(word, i) == 1 \
			|| if_in_quote(word, i) == 3))
		{
			temp = copy_word_env(word, i + 1);
			if (!temp)
				return (free(word), NULL);
			word = find_env_var(word, glob, i, temp);
			if (!word)
				return (free(temp), NULL);
			free(temp);
		}
		i++;
	}
	return (word);
}
