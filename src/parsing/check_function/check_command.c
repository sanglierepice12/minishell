/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <arbenois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 03:30:04 by arbenois          #+#    #+#             */
/*   Updated: 2024/10/08 21:15:25 by arbenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i] && n > 0)
	{
		i++;
		n--;
	}
	if (n == 0)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static int	check_input(char *input, int letter)
{
	if (input[letter] == ' ' || input[letter] == 0)
		return (1);
	return (0);
}

int	check_command(char *input)
{
	if (ft_strncmp(input, "pwd", 3) == 0)
		return (check_input(input, 3));
	else if (ft_strncmp(input, "echo", 4) == 0)
		return (check_input(input, 4));
	else if (ft_strncmp(input, "cd", 2) == 0)
		return (check_input(input, 2));
	else if (ft_strncmp(input, "export", 6) == 0)
		return (check_input(input, 6));
	else if (ft_strncmp(input, "unset", 5) == 0)
		return (check_input(input, 5));
	else if (ft_strncmp(input, "env", 3) == 0)
		return (check_input(input, 3));
	else if (ft_strncmp(input, "exit", 4) == 0)
		return (check_input(input, 4));
	return (0);
}

int	check_command_null(t_glob *glob, int num_args)
{
	int	i;

	i = 0;
	while (i != num_args)
	{
		if (glob->cmd[i].command == NULL)
			return (0);
		i++;
	}
	return (1);
}

void	check_tab_quote(char *tab, int check)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		if (check == 1)
		{
			if (tab[i] == -39)
				tab[i] *= -1;
			if (tab[i] == -124)
				tab[i] *= -1;
		}
		else
		{
			if (tab[i] == 39)
				tab[i] *= -1;
			if (tab[i] == 124)
				tab[i] *= -1;
		}
		i++;
	}
	return ;
}
