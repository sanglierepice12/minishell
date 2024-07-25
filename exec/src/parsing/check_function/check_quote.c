/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 03:43:51 by arbenois          #+#    #+#             */
/*   Updated: 2024/05/29 03:43:52 by arbenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	check_quote(char *str, int len, int *checkquote, char c)
{
	if (str[len] == c && (*checkquote == 1 || *checkquote == 0) && c == 34)
	{
		if (*checkquote == 1)
			*checkquote = 0;
		else
		{
			*checkquote = 1;
			return (1);
		}
	}
	if (str[len] == c && (*checkquote == 2 || *checkquote == 0) && c == 39)
	{
		if (*checkquote == 2)
			*checkquote = 0;
		else
		{
			*checkquote = 2;
			return (1);
		}
	}
	return (0);
}

static int	check_char_spec(char *str, int len, int i)
{
	int size;

	size = 0;
	if (str[len + i] == '>')
	{
		while (str[len + i + size] == '>')
			size++;
		return (size);
	}
	if (str[len + i] == '<')
	{
		while (str[len + i + size] == '<')
			size++;
		return (size);
	}
	if (str[len + i] == '|')
		return (1);
	return (0);
}

int	ft_strlen_quote(char *str, int len, int *quote)
{
	int	i;
	int	checkquote;

	checkquote = 0;
	i = 0;
	if (check_char_spec(str, len, i) != 0)
		return (check_char_spec(str, len, i));
	while (str[len + i])
	{
		if (check_quote(str, len + i, &checkquote, 34) == 1)
			(*quote)++;
		else if (check_quote(str, len + i, &checkquote, 39) == 1)
			(*quote)++;
		if ((str[len + i] == ' ' || str[len + i] == '|') && checkquote == 0)
			break ;
		i++;
	}
	if (checkquote == 1 || checkquote == 2)
	{
		*quote = -1;
		printf("minishell: syntax error with open quotes\n");
		return (-1);
	}
	return (i);
}

int	if_in_quote(char *str, int i)
{
	int	lenght;
	int	quote;

	lenght = 0;
	quote = 0;
	while (str[lenght])
	{
		if (str[lenght] == 34 && quote == 1)
			quote = 0;
		else if (str[lenght] == 39 && quote == 2)
			quote = 0;
		else if (str[lenght] == 34 && quote == 0)
			quote = 1;
		else if (str[lenght] == 39 && quote == 0)
			quote = 2;
		if (lenght == i && quote == 1)
			return (1);
		if (lenght == i && quote == 2)
			return (2);
		else if (lenght == i && quote == 0)
			return (3);
		lenght++;
	}
	return (0);
}
