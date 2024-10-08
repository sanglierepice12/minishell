/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <arbenois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 04:21:46 by arbenois          #+#    #+#             */
/*   Updated: 2024/10/08 21:00:02 by arbenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*alloc_new_word(char *word, char *path, char *temp)
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

void	ft_add_tab(char *str, char *tab, size_t size)
{
	size_t	index;

	index = ft_strlen(str) - 1;
	while ((ssize_t)index != -1)
	{
		tab[size + index] = str[index];
		index--;
	}
}

static int	handle_special_cases(char **word, size_t i, char *temp)
{
	char	*tab;

	if (ft_comp_str(temp, "?") == 1)
	{
		tab = ft_itoa(g_error_code);
		*word = replace_env_word(*word, i, tab, temp);
		if (!*word)
			return (free(tab), ft_error(1), 0);
		free(tab);
		return (1);
	}
	else if (ft_comp_str(temp, "$") == 1)
	{
		tab = ft_itoa(getpid());
		*word = replace_env_word(*word, i, tab, temp);
		if (!*word)
			return (free(tab), ft_error(1), 0);
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
	if (!word)
		return (NULL);
	return (word);
}

char	*expand_single_var(char *word, t_glob *glob, const size_t *i)
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
