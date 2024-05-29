/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsuter <gsuter@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:21:20 by gsuter            #+#    #+#             */
/*   Updated: 2024/05/22 17:21:20 by gsuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_ls()
{
	struct dirent *de;

	DIR *dr = opendir(".");
	if (dr == NULL)
	{
		printf("Could not open current directory");
		return ;
	}
	while ((de = readdir(dr)) != NULL)
		printf("%s ", de->d_name);
	printf("\n");
	closedir(dr);
}