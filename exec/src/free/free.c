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

void	ft_free_here_doc(t_heredoc *heredoc)
{
	if (heredoc->file_infile)
		ft_free_double_tab(heredoc->file_infile);
	if (heredoc->file_outfile)
		free(heredoc->file_outfile);
	/*if (heredoc->type_infile)
		free(heredoc->type_infile);
	if (heredoc->type_outfile)
		free(heredoc->type_outfile);*/
	if (heredoc->rest_heredoc)
		ft_free_double_tab(heredoc->rest_heredoc);
}

void	ft_free_cmd(t_glob *glob)
{
	size_t	i;

	if (!glob->cmd)
		return ;
	i = 0;
	while (i < glob->count_cmd && &glob->cmd[i])
	{
		if (glob->cmd[i].args && glob->cmd[i].argv)
			free_tab(glob->cmd[i].argv, glob->cmd[i].args);
		if (glob->cmd[i].args && glob->cmd[i].path)
			ft_free_double_tab(glob->cmd[i].path);
		ft_free_here_doc(&glob->cmd[i].heredoc);
		i++;
	}
	free(glob->cmd);
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
	ft_free_cmd(glob);
	if (glob->env)
		ft_free_env(glob->env);
}
