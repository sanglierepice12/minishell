/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <arbenois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 01:35:22 by arbenois          #+#    #+#             */
/*   Updated: 2024/09/24 06:56:02 by arbenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

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

static char	**rs_heredoc(char **argv, t_input *cmd, int i)
{
	char	**tab;
	char	**temp;

	tab = calloc(3, sizeof(char *));
	if (argv[i + 1] != NULL)
	{
		tab[0] = ft_dup(argv[i]);
		tab[1] = ft_dup(argv[i + 1]);
		tab[2] = NULL;
	}
	temp = ft_realloc(cmd->heredoc.rest_heredoc, tab);
	return (temp);
}

static int	handle_single_right_redir(char **argv, t_input *cmd, int i)
{
	int	fd;

	fd = open(argv[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("minisHell");
		g_error_code = 1;
		return (1);
	}
	close(fd);
	remove_heredoc(argv, i, cmd);
	return (0);
}

static int	handle_double_right_redir(char **argv, t_input *cmd, int i)
{
	int	fd;

	fd = open(argv[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("minisHell");
		g_error_code = 1;
		return (1);
	}
	close(fd);
	remove_heredoc(argv, i, cmd);
	return (0);
}

static int	handle_single_left_redir(char **argv, t_input *cmd, int i)
{
	int	fd;

	fd = open(argv[i + 1], O_WRONLY, O_RDONLY, 0644);
	if (fd == -1)
	{
		fprintf(stderr, "minisHell: No such file or directory\n");
		g_error_code = 1;
		return (1);
	}
	close(fd);
	cmd->heredoc.rest_heredoc = rs_heredoc(argv, cmd, i);
	remove_heredoc(argv, i, cmd);
	return (0);
}

static int	handle_double_left_redir(char **argv, t_input *cmd, int i)
{
	cmd->heredoc.rest_heredoc = rs_heredoc(argv, cmd, i);
	remove_heredoc(argv, i, cmd);
	return (0);
}

int	remove_and_stock_all_heredoc(char **argv, t_input *cmd, unsigned long i)
{
	while (i < cmd->args)
	{
		printf("%ld %ld %s\n", i, cmd->args, argv[i]);
		if (ft_comp_str(argv[i], ">") == 1)
		{
			if (handle_single_right_redir(argv, cmd, i) == 1)
				return (1);
		}
		else if (ft_comp_str(argv[i], ">>") == 1)
		{
			if (handle_double_right_redir(argv, cmd, i) == 1)
				return (1);
		}
		else if (ft_comp_str(argv[i], "<") == 1)
		{
			if (handle_single_left_redir(argv, cmd, i) == 1)
				return (1);
		}
		else if (ft_comp_str(argv[i], "<<") == 1)
			handle_double_left_redir(argv, cmd, i);
		else
			i++;
	}
	return (0);
}
