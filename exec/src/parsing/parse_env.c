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
	if (input[i] == '?')
	{
		tab = calloc(2, sizeof(char));
		tab[0] = '?';
		return (tab);
	}
	if (input[i] == '$')
	{
		tab = calloc(2, sizeof(char));
		tab[0] = '$';
		return (tab);
	}
	while (input[i + lenght] && lenght >= 0)
	{
		if (input[i + lenght] == ' ' || input[i + lenght] == 39 \
			|| input[i + lenght] == 34 || input[i + lenght] == '$')
			break ;
		lenght++;
	}
	tab = calloc(lenght + 1, sizeof(char));
	if (!tab)
		return (NULL);
	tab[lenght] = 0;
	lenght = 0;
	while (input[i + lenght])
	{
		if (input[i + lenght] == ' ' || input[i + lenght] == 39 \
			|| input[i + lenght] == 34 || input[i + lenght] == '$')
			break ;
		tab[lenght] = input[i + lenght];
		lenght++;
	}
	return (tab);
}

static char	*alloc_new_word(char *word, char *path, char *temp)
{
	char	*tab;
	int		length;

	length = ft_strlen(word) - ft_strlen(temp) - 1 \
				+ ft_strlen(path);
	if (length == 0)
	{
		tab = calloc(1, sizeof(char));
		if (!tab)
			return (0);
		tab[0] = 0;
		return (tab);
	}
	tab = calloc(length, sizeof(char));
	if (!tab)
		return (0);
	tab[length] = 0;
	return (tab);
}

static char	*replace_env_word(char *word, int i, char *path, char *temp)
{
	char	*tab;
	int		size;
	int		index;

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
	while (index != -1)
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

static char	*find_env_var(char *word, t_glob *glob, int i, char *temp)
{
	t_env	*env;
	int		check_sup;
	char	*tab;
	int		pid_num;

	tab = NULL;
	pid_num = getpid();
	check_sup = 5;
	if (ft_comp_str(temp, "?") == 1)
	{
		tab = ft_itoa(g_error_code);
		word = replace_env_word(word, i, tab, temp);
		free(tab);
		return (word);
	}
	if (ft_comp_str(temp, "$") == 1)
	{
		tab = ft_cal_loc(7, sizeof(char));
		while (pid_num != 0)
		{
			tab[check_sup] = pid_num % 10 + 48;
			pid_num /= 10;
			check_sup--;
		}
		word = replace_env_word(word, i, tab, temp);
		free(tab);
		return (word);
	}
	check_sup = 1;
	env = glob->env;
	while (env != NULL)
	{
		if (ft_comp_str_for_alpha(env->value, temp) == 0)
		{
			word = replace_env_word(word, i, env->path, temp);
			if (!word)
				return (NULL);
			check_sup = 2;
			break ;
		}
		env = env->next;
	}
	if (check_sup == 1)
		word = replace_env_word(word, i, "", temp);
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
			if (ft_isspace(word[i + 1]) == 1 && \
				word[i + 1] != '"' && word[i + 1] != 0)
			{
				temp = copy_word_env(word, i + 1);
				if (!temp)
					return (free(word), NULL);
				word = find_env_var(word, glob, i, temp);
				if (!word)
					return (free(temp), NULL);
				free(temp);
			}
			else
				i++;
		}
		else
			i++;
	}
	return (word);
}
