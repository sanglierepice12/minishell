/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 00:22:47 by arbenois          #+#    #+#             */
/*   Updated: 2024/06/15 00:22:48 by arbenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	skip_command(char *input, int *i)
{
	while (input[*i] == ' ')
		(*i)++;
	while (input[*i])
	{
		if (input[*i] == ' ' || input[*i] == 0)
			break ;
		(*i)++;
	}
}

int	count_args(char *input, int lenght)
{
	int	i;
	int	args;
	int	quote;
	int	temp;

	i = 0;
	args = 1;
	if (lenght != 0)
		i = get_lenght_num(input, lenght);
	else
		i = 0;
	skip_command(input, &i);
	while (input[i])
	{
		if (input[i] != ' ')
		{
			args++;
			temp = ft_strlen_quote(input, i, &quote);
			if (temp == -1)
				return (-1);
			i += temp;
		}
		if (input[i] == ' ')
			i++;
		if (input[i] == '|')
		{
			if (input[i - 1] == ' ' && input[i + 1] == ' ')
				break ;
		}
	}
	return (args);
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

static void	parse_word(char **argv, char *input, int *i, int *lenght)
{
	int		temp;
	char	*word;

	temp = 0;
	word = copy_word(input, i);
	if (word == NULL)
	{
		free_tab(argv, (*lenght) - 1);
		*lenght = -1;
		return ;
	}
	argv[*lenght] = delete_quote(word, input, *i);
	*i += ft_strlen_quote(input, *i, &temp);
	(*lenght)++;
}

static void remove_heredoc(char **argv, int pos, t_input *command)
{
	int i;
	int size;

	free(argv[pos]);
	free(argv[pos + 1]);
	i = pos;
	size = command->args;
	while (i < size - 2)
	{
		argv[i] = argv[i + 2];
		i++;
	}
	argv[size - 2] = NULL;
	argv[size - 1] = NULL;
	command->args -= 2;
}

static char **check_apply_heredoc(char **argv, t_input *command)
{
	int		i;

	i = command->args - 2;
	while (i > 0)
	{
		if (ft_comp_str(argv[i], "<") == 1)
		{
			command->heredoc.type = "<";
			command->heredoc.file = ft_super_dup(argv[i + 1], NULL);
			remove_heredoc(argv, i, command);
			break ;
		}
		i--;
	}
	return (argv);
}

char	**set_argv(char *input, int num, t_input *command)
{
	char	**argv;
	int		i;
	int		lenght;

	argv = malloc(command->args * sizeof(char *));
	if (argv == NULL)
		return (0);
	lenght = 0;
	if (num != 0)
		i = get_lenght_num(input, num);
	else
		i = 0;
	while (input[i])
	{
		if (input[i] != ' ')
			parse_word(argv, input, &i, &lenght);
		if (lenght == -1)
			return (0);
		if (input[i] == ' ')
			i++;
		if (input[i] == '|')
		{
			if (input[i - 1] == ' ' && input[i + 1] == ' ')
				break;
		}
	}
	return (check_apply_heredoc(argv, command));
}
