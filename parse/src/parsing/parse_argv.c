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

static char	*parse_word(char *input, int *i, t_glob *glob)
{
	int		temp;
	char	*word;

	temp = 0;
	word = copy_word(input, i);
	if (word == NULL)
		return (NULL);
	word = expend_env_var(word, glob);
	word = delete_quote(word, 0);
	*i += ft_strlen_quote(input, *i, &temp);
	return (word);
}

char	**set_argv(char *input, int num, t_glob *glob)
{
	char	**argv;
	int		i;
	int		lenght;

	argv = malloc(glob->command->args * sizeof(char *));
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
			argv[lenght++] = parse_word(input, &i, glob);
		if (lenght == -1)
		{
			//Faut free argv
			return (0);
		}
		if (input[i] == ' ')
			i++;
		if (input[i] == '|')
		{
			if (input[i - 1] == ' ' && input[i + 1] == ' ')
				break ;
		}
	}
	return (check_apply_heredoc(argv, glob->command));
}
