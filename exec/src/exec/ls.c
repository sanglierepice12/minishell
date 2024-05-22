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
	struct dirent *de; // Pointer for directory entry
	DIR *dr = opendir(".");

	if (dr == NULL)  // opendir returns NULL if couldn't open directory
	{
		printf("Could not open current directory");
		return ;
	}

// Referencing readdir() inside the loop
	while ((de = readdir(dr)) != NULL)
		printf("%s ", de->d_name);
	printf("\n");
	closedir(dr);
}