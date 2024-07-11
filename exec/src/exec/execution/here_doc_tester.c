/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc_tester.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostr <gostr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:34:52 by gostr             #+#    #+#             */
/*   Updated: 2024/07/11 17:34:52 by gostr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

bool	ft_here_doc_tester(t_input *cmd)
{
	if (ft_comp_str(cmd->heredoc.type_outfile, ">"))
	{
		if ((open(cmd->heredoc.file_outfile, \
            O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
		{
			perror("MiniHell");
			return (1);
		}
	}
	if (ft_comp_str(cmd->heredoc.type_outfile, ">>"))
	{
		if ((open(cmd->heredoc.file_outfile, \
            O_WRONLY | O_CREAT | O_APPEND, 0644)) == -1)
		{
			perror("MiniHell");
			return (1);
		}
	}
	if (ft_comp_str(cmd->heredoc.type_infile, "<"))
	{
		if ((open(cmd->heredoc.file_infile, O_RDONLY) == -1))
		{
			perror("MiniHell");
			return (1);
		}
	}
	/*if (ft_comp_str(cmd->heredoc.type_infile, "<<"))
	{
		if ((open(cmd->heredoc.file_infile, \
            O_WRONLY | O_CREAT | O_APPEND, 0644)) == -1)
		{
			perror("MiniHell");
			return (1);
		}
	}*/
	return (0);
}