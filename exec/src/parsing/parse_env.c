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
		if (input[i + lenght] == ' ' || input[i + lenght] == 39 || input[i + lenght] == 34)
			break ;
		lenght++;
	}
	tab = malloc(lenght * sizeof(char));
	lenght = 0;
	while (input[i + lenght])
	{
		if (input[i + lenght] == ' ' || input[i + lenght] == 39 || input[i + lenght] == 34)
			break ;
		tab[lenght] = input[i + lenght];
		lenght++;
	}
	tab[lenght] = 0;
	return (tab);
}

static char	*replace_env_word(char *word, int i, char *path)
{
	char	*tab;
	int		lenght;
	int		size;
	int		index;

	lenght = ft_strlen(word) - ft_strlen(copy_word_env(word, i)) + ft_strlen(path);
	if (lenght == 0)
	{
		tab = malloc(1 * sizeof(char));
		tab[0] = 0;
		return (tab);
	}
	tab = malloc(lenght * sizeof(char));
	tab[lenght] = 0;
	size = 0;
	while (size != i)
	{
		tab[size] = word[size];
		size++;
	}
	i += ft_strlen(copy_word_env(word, i));
	index = ft_strlen(path) - 1;
	while (index != -1)
	{
		tab[size + index] = path[index];
		index--;
	}
	size += ft_strlen(path);
	while (word[i])
	{
		tab[size] = word[i];
		size++;
		i++;
	}
	free(word);
	return (tab);
}

char	*expend_env_var(char *word, t_glob *glob)
{
	char	*temp;
	t_env	*env;
	int		i;
	int		check_sup;

	i = 0;
	check_sup = 0;
	while (word[i])
	{
		if (word[i] == '$' && (if_in_quote(word, i) == 1 || if_in_quote(word, i) == 3))
		{
			env = glob->env;
			temp = copy_word_env(word, i + 1);
			check_sup = 1;
			while (env != NULL)
			{
				if (ft_comp_str(env->value, temp))
				{
					word = replace_env_word(word, i, env->path);
					check_sup = 2;
					break ;
				}
				env = env->next;
			}
			if (check_sup == 1)
				word = replace_env_word(word, i, "");
		}
		i++;
	}
	return (word);
}
