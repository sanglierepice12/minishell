/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_in_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 03:30:09 by arbenois          #+#    #+#             */
/*   Updated: 2024/05/29 03:30:10 by arbenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*set_command(char *input)
{
	if (ft_strncmp(input, "pwd", 3) == 0)
		return ("pwd");
	else if (ft_strncmp(input, "echo", 4) == 0)
		return ("echo");
	else if (ft_strncmp(input, "cd", 2) == 0)
		return ("cd");
	else if (ft_strncmp(input, "export", 6) == 0)
		return ("export");
	else if (ft_strncmp(input, "unset", 5) == 0)
		return ("unset");
	else if (ft_strncmp(input, "env", 3) == 0)
		return ("env");
	else if (ft_strncmp(input, "exit", 4) == 0)
		return ("exit");
	return (NULL);
}

static size_t	count_args(char *input, int lenght)
{
	size_t	i;
	int		quote;

	i = 0;
	while (input[lenght])
	{
		if (input[lenght] != ' ')
		{
			i++;
			lenght += ft_strlen_quote(input, lenght, &quote);
		}
		if (input[lenght] == ' ')
			lenght++;
	}
	return (i);
}

static char	*copy_word(char *input, int *i)
{
	int		lenght;
	char	*tab;
	int		temp;
	int		skip;

	temp = 0;
	lenght = ft_strlen_quote(input, *i, &temp);
	if (temp >= 1)
		lenght -= temp * 2;
	tab = malloc(lenght + 1 * sizeof(char));
	tab[lenght] = 0;
	temp = 0;
	skip = 0;
	while (temp != lenght)
	{
		if (input[*i + temp + skip] == 39 || input[*i + temp + skip] == 34)
			skip++;
		else
		{
			tab[temp] = input[*i + temp + skip];
			temp++;
		}
	}
	*i += ft_strlen_quote(input, *i, &temp);
	return (tab);
}

static char	**set_argv(char *input, t_input *command)
{
	char	**argv;
	int		i;
	int		lenght;

	argv = malloc(command->args * sizeof(char *));
	lenght = 0;
	i = ft_strlen(command->command);
	while (input[i])
	{
		if (input[i] != ' ')
		{
			argv[lenght] = copy_word(input, &i);
			lenght++;
		}
		if (input[i] == ' ')
			i++;
	}
	return (argv);
}

int	parse_in_struct(t_input *command, char *input)
{
	command->command = set_command(input);
	command->args = count_args(input, ft_strlen(command->command));
	command->argv = set_argv(input, command);
	return (1);
}
