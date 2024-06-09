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

static ssize_t	count_args(char *input, int lenght)
{
	size_t	i;
	int		quote;
	int		temp;

	i = 0;
	while (input[lenght])
	{
		if (input[lenght] != ' ')
		{
			i++;
			temp = ft_strlen_quote(input, lenght, &quote);
			if (temp == -1)
				return (-1);
			lenght += temp;
		}
		if (input[lenght] == ' ')
			lenght++;
	}
	return (i);
}

static char	*delete_quote(char *tab, char *input, int i)
{
	char	*newtab;
	int		skip;
	int		checkquote;
	int		lenght;
	int		temp;

	temp = 0;
	lenght = ft_strlen_quote(input, i, &temp);
	if (lenght == -1)
		return (NULL);
	if (temp >= 1)
		lenght -= temp * 2;
	newtab = malloc(lenght + 1 * sizeof(char));
	if (newtab == NULL)
		return (NULL);
	newtab[lenght] = 0;
	temp = 0;
	skip = 0;
	checkquote = 0;
	while (temp != lenght)
	{
		if (tab[temp + skip] == 39 && checkquote == 0)
		{
			checkquote = 1;
			skip++;
		}
		else if (tab[temp + skip] == 34 && checkquote == 0)
		{
			checkquote = 2;
			skip++;
		}
		else if (tab[temp + skip] == 39 && checkquote == 1)
		{
			checkquote = 0;
			skip++;
		}
		else if (tab[temp + skip] == 34 && checkquote == 2)
		{
			checkquote = 0;
			skip++;
		}
		else
		{
			newtab[temp] = tab[temp + skip];
			temp++;
		}
	}
	free(tab);
	return (newtab);
}

static char	*copy_word(char *input, int *i)
{
	char	*tab;
	int		lenght;
	int		temp;
	int		y;

	temp = 0;
	lenght = ft_strlen_quote(input, *i, &temp);
	if (lenght == -1)
		return (NULL);
	tab = malloc(lenght + 1 * sizeof(char));
	tab[lenght] = 0;
	y = 0;
	while (lenght != y)
	{
		tab[y] = input[*i + y];
		y++;
	}
	return (tab);
}

static void parse_word(char **argv, char *input, int *i, int *lenght)
{
	int temp;
	char *word;

	temp = 0;
	word = copy_word(input, i);
	if (word == NULL)
	{
		free_tab(argv, (*lenght) - 1);
		*lenght = -1;
		return ;
	}
	//check_redir(argv, word, lenght);
	argv[*lenght] = delete_quote(word, input, *i);
	*i += ft_strlen_quote(input, *i, &temp);
	(*lenght)++;
}

static char	**set_argv(char *input, t_input *command)
{
	char	**argv;
	int		i;
	int		lenght;

	argv = malloc(command->args * sizeof(char *));
	if (argv == NULL)
		return (0);
	lenght = 0;
	i = ft_strlen(command->command);
	while (input[i])
	{
		if (input[i] != ' ')
			parse_word(argv, input, &i, &lenght);
		if (lenght == -1)
			return (0);
		if (input[i] == ' ')
			i++;
	}
	return (argv);
}

void	show_struct(t_input *command)
{
	int	i;

	printf("ARGS = %d\n", command->args);
	printf("command = %s\n", command->command);
	i = 0;
	while (i != command->args)
	{
		printf("ARGV = %s\n", command->argv[i]);
		free(command->argv[i]);
		i++;
	}
	free(command->argv);
}

int	parse_in_struct(t_glob *glob, char *input)
{
	glob->command.command = set_command(input);
	glob->command.args = count_args(input, ft_strlen(glob->command.command));
	if (glob->command.args == -1)
		return (0);
	glob->command.argv = set_argv(input, &glob->command);
	if (glob->command.argv == 0)
		return (0);
	show_struct(&glob->command);
	return (1);
}
