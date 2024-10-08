/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <arbenois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:41:41 by gsuter            #+#    #+#             */
/*   Updated: 2024/10/08 19:13:21 by arbenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *) s)[i] = 0;
		i++;
	}
}

void	*ft_cal_loc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (size != 0 && nmemb > SIZE_MAX / size)
		return (NULL);
	if (nmemb == 0 && size == 0)
	{
		ptr = malloc(sizeof(char));
		if (!ptr)
			return (NULL);
		((char *) ptr)[0] = '\0';
	}
	else
	{
		ptr = malloc(size * nmemb);
		if (!ptr)
			return (NULL);
		ft_bzero(ptr, nmemb * size);
	}
	return (ptr);
}

static char	**ft_realloc(char **heredoc, char **tab)
{
	size_t		i;
	size_t		size;
	size_t		lenght;
	char		**realloc;

	i = 0;
	lenght = ft_strlen_double(heredoc);
	realloc = malloc((lenght + 3) * sizeof(char *));
	while (i != lenght)
	{
		realloc[i] = heredoc[i];
		i++;
	}
	size = 0;
	while (i != lenght + 2)
	{
		realloc[i] = tab[size];
		i++;
		size++;
	}
	realloc[i] = NULL;
	if (ft_strlen_double(heredoc) != 0)
		free(heredoc);
	return (realloc);
}

char	**rs_heredoc(char **argv, t_input *cmd, int i)
{
	char	**tab;
	char	**temp;

	tab = ft_cal_loc(3, sizeof(char *));
	if (!tab)
		return (0);
	if (argv[i + 1] != NULL)
	{
		tab[0] = ft_dup(argv[i]);
		tab[1] = ft_dup(argv[i + 1]);
		tab[2] = NULL;
	}
	temp = ft_realloc(cmd->heredoc.rest_heredoc, tab);
	free(tab);
	return (temp);
}
