/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <arbenois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 04:58:00 by arbenois          #+#    #+#             */
/*   Updated: 2024/09/25 19:20:31 by arbenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_env_derror(char *cmd, char *variable, char *followed, int code)
{
	g_error_code = code;
	dprintf(2, "minisHell : %s: `%s': %s\n", cmd, variable, followed);
}

static int	check_tab(char *tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (0);
	if (ft_comp_str("\t", tab))
		return (1);
	while (tab[i])
	{
		if (ft_isspace(tab[i]) == 1)
			return (0);
		if (tab[i] == 0)
			return (0);
		i++;
	}
	return (1);
}

static void	remove_tab(char **argv, int size, t_glob *glob, unsigned long num)
{
	free(argv[size]);
	while (argv[size + 1])
	{
		argv[size] = argv[size + 1];
		size++;
	}
	argv[size] = 0;
	glob->cmd[num].args--;
	if (glob->cmd[num].args == 0)
		glob->cmd[num].initargs = -1;
}

int	check_env(char **argv, t_glob *glob, unsigned long num)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (check_tab(argv[i]) == 1)
		{
			remove_tab(argv, i, glob, num);
			i = -1;
		}
		i++;
	}
	if (glob->cmd[num].initargs == -1)
		return (0);
	return (1);
}
