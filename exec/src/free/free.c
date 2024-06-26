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
	if (i >= 1)
		free(glob->cmd);
}

void	free_tab(char **tab, int lenght)
{
	if (!tab)
		return ;
	while (lenght != 0)
	{
		free(tab[lenght]);
		lenght--;
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
	if (!cmd)
		return ;
	if (cmd->argv)
		ft_free_double_tab(cmd->argv);
	if (cmd->command)
		free(cmd->command);
	ft_free_here_doc(&cmd->heredoc);
	if (cmd->args)
		cmd->args = 0;
}
void	ft_free_env(t_env *env)
{
	if (!env)
		return ;
	ft_free_lst(&env);
}

void	ft_free_all(t_glob *glob)
{
//int	i;

	/*if (glob->cmd)
	{
		//i = 0;
		//printf("cmd [%d] %s\n",i, glob->cmd->argv[0]);
		//printf("i = %d\n", i);
		*//*while (&glob->cmd[i])
		{
			printf("ici i = %d\n", i);
			ft_free_cmd(&glob->cmd[i]);
			free(&glob->cmd[i]);
			i++;
		}*//*
		ft_free_cmd(&glob->cmd[0]);
		free(glob->cmd);
	}*/
	if (glob->env)
		ft_free_env(glob->env);
}
