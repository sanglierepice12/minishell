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

/*void	free_tab(char **tab, int lenght)
{
	if (!tab)
		return ;
	while (lenght != 0)
	{
		free(tab[lenght]);
		lenght--;
	}
	free(tab);
}*/
void	free_tab(char **tab)
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
}


void	ft_free_cmd(t_input *cmd)
{
	if (!cmd)
		return ;
	if (cmd->argv)
		free_tab(cmd->argv);
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
	int	i;

	if (glob->cmd)
	{
		i = 0;
		while (&glob->cmd[i])
		{
			ft_free_cmd(&glob->cmd[i]);
			i++;
		}
		free(glob->cmd);
	}
	if (glob->env)
		ft_free_env(glob->env);
}
