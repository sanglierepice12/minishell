/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <arbenois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 04:21:46 by arbenois          #+#    #+#             */
/*   Updated: 2024/08/29 19:54:59 by arbenois         ###   ########.fr       */
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
	char	*tab;
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

static char	*copy_word_env(char *input, size_t i)
{
	size_t	length;

	if (input[i] == '?' || input[i] == '$')
		return (allocate_special_char(input[i]));
	length = get_word_length(input, i);
	return (allocate_and_copy_word(input, i, length));
}

static char	*alloc_new_word(char *word, char *path, char *temp)
{
	char		*tab;
	size_t		length;

	length = ft_strlen(word) - ft_strlen(temp) - 1 \
				+ ft_strlen(path);
	if (length == 0)
	{
		tab = ft_cal_loc(1, sizeof(char));
		if (!tab)
			return (0);
		return (tab);
	}
	tab = ft_cal_loc(length + 1, sizeof(char));
	if (!tab)
		return (0);
	tab[length] = 0;
	return (tab);
}

static char	*replace_env_word(char *word, size_t i, char *path, char *temp)
{
	char		*tab;
	size_t		size;
	size_t		index;

	tab = alloc_new_word(word, path, temp);
	if (!tab)
		return (free(word), NULL);
	size = 0;
	while (size != i)
	{
		tab[size] = word[size];
		size++;
	}
	index = ft_strlen(path) - 1;
	while ((ssize_t)index != -1)
	{
		tab[size + index] = path[index];
		index--;
	}
	size += ft_strlen(path);
	i += ft_strlen(temp) + 1;
	while (word[i])
		tab[size++] = word[i++];
	free(word);
	return (tab);
}

static int	handle_special_cases(char **word, size_t i, char *temp)
{
	char	*tab;

	if (ft_comp_str(temp, "?") == 1)
	{
		tab = ft_itoa(g_error_code);
		*word = replace_env_word(*word, i, tab, temp);
		free(tab);
		return (1);
	}
	else if (ft_comp_str(temp, "$") == 1)
	{
		tab = ft_itoa(getpid());
		*word = replace_env_word(*word, i, tab, temp);
		free(tab);
		return (1);
	}
	return (0);
}

static char	*find_env_var(char *word, t_glob *glob, size_t i, char *temp)
{
	t_env	*env;
	int		check_sup;

	if (handle_special_cases(&word, i, temp) == 1)
		return (word);
	check_sup = 1;
	env = glob->env;
	while (env != NULL)
	{
		if (ft_comp_str_for_alpha(env->key, temp) == 0)
		{
			word = replace_env_word(word, i, env->value, temp);
			if (!word)
				return (NULL);
			check_sup = 2;
			break ;
		}
		env = env->next;
	}
	if (check_sup == 1)
		word = replace_env_word(word, i, "\t", temp);
//	dprintf(2, "je passe par ici\n");
	if (!word)
	{
//		dprintf(2, "je passe par la\n");
		return (NULL);
	}
	return (word);
}

static char	*expand_single_var(char *word, t_glob *glob, const size_t *i)
{
	char	*temp;

	temp = copy_word_env(word, *i + 1);
	if (!temp)
		return (free(word), NULL);
	word = find_env_var(word, glob, *i, temp);
	free(temp);
	if (!word)
		return (NULL);
	return (word);
}

char	*expend_env_var(char *word, t_glob *glob)
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
