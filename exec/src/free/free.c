/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsuter <gsuter@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:09:48 by gsuter            #+#    #+#             */
/*   Updated: 2024/05/21 17:09:48 by gsuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_parse(t_glob *glob, int i)
{
	int	size;

	if (i >= 2)
	{
		size = glob->cmd->args - 1;
		while (size != -1)
		{
			free(glob->cmd->argv[size]);
			size--;
		}
		free(glob->cmd->argv);
	}
	if (i >= 1)
		free(glob->cmd);
}

void	free_tab(char **tab, int lenght)
{
	if (!tab)
		return ;
	while (lenght != 0)
	{
		lenght--;
		free(tab[lenght]);
	}
	free(tab);
}

static void	ft_free_double_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_free_here_doc(t_heredoc *heredoc)
{
	if (heredoc->file_infile)
		free(heredoc->file_infile);
	if (heredoc->file_outfile)
		free(heredoc->file_outfile);
	if (heredoc->type_infile)
		free(heredoc->type_infile);
	if (heredoc->type_outfile)
		free(heredoc->type_outfile);
	if (heredoc->rest_heredoc)
		ft_free_double_tab(heredoc->rest_heredoc);
}

void	ft_free_cmd(t_input *cmd)
{
	printf("\ncoucou !\n");
	if (!cmd)
		return ;
	printf("je suis passé !\n");
	if (cmd->args && cmd->argv)
		free_tab(cmd->argv, cmd->args);
	ft_free_here_doc(&cmd->heredoc);
	printf("sans crash !\n");
}

void	ft_free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		if (tmp->value)
			free(tmp->value);
		if (tmp->path)
			free(tmp->path);
		free(tmp);
	}
}

void	ft_free_all(t_glob *glob)
{
	int	i;

	if (glob->cmd)
	{
		i = 0;
		while (glob->cmd[i].command)
		{
			printf("ici i = %d\n", i);
			ft_free_cmd(&glob->cmd[i]);
			i++;
		}
		free(glob->cmd);
	}
	if (glob->env)
		ft_free_env(glob->env);
}
