/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mienache <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 14:50:36 by mienache          #+#    #+#             */
/*   Updated: 2018/02/18 17:35:17 by mienache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	free_file(t_file **files)
{
	t_file	*delete;

	if (!files)
		return ;
	while (*files)
	{
		delete = *files;
		*files = (*files)->next;
		if (delete->inside)
			free_file(&delete->inside);
		del_file(delete);
		free(delete);
	}
	*files = NULL;
}

void	del_file(t_file *file)
{
	file->path ? free(file->path) : 0;
	file->color_name ? free(file->color_name) : 0;
	file->long_format ? free(file->long_format) : 0;
}
