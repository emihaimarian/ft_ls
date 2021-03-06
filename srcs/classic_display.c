/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classic_display.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mienache <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 14:49:59 by mienache          #+#    #+#             */
/*   Updated: 2018/02/18 19:23:43 by mienache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		display_non_dir(t_file *files, t_opt *option)
{
	t_file	*temp;
	int		nb_file;

	nb_file = 0;
	if (!option->c1)
		return (display_non_dir_column(files, option));
	temp = files;
	while (temp)
	{
		if (!S_ISDIR(temp->stat.st_mode)
			&& (temp->error == 0 || temp->error == 20))
		{
			if (option->u_g)
			{
				join_color(temp, temp->path);
				ft_putendl(temp->color_name);
			}
			else
				ft_putendl(temp->path);
			nb_file++;
		}
		temp = temp->next;
	}
	return (nb_file);
}

void	display_dir(int nb_file, int ac, t_file *files, t_opt *option)
{
	t_file	*temp;

	temp = files;
	while (temp)
	{
		if (S_ISDIR(temp->stat.st_mode))
		{
			if (ac != 1)
			{
				ft_putstr(temp->path);
				ft_putendl(":");
			}
			if (temp->error == 13)
				display_file_error(temp);
			else
			{
				temp->inside = which_sort(temp->inside, option);
				display_inside(temp->inside, option);
				readndisplay_inside(temp->inside, option);
			}
			if (++nb_file != ac)
				write(1, "\n", 1);
		}
		temp = temp->next;
	}
}

void	display_inside(t_file *files, t_opt *option)
{
	t_file	*temp;

	if (!display_column(files, option))
		;
	else
	{
		temp = files;
		while (temp)
		{
			if (lstat(temp->path, &temp->lstat) == -1)
			{
				if (errno != 9)
					display_file_error(temp);
			}
			else if (option->u_g)
			{
				join_color(temp, temp->name);
				ft_putendl(temp->color_name);
			}
			else
				ft_putendl(temp->name);
			temp = temp->next;
		}
	}
}

void	classic_display(int ac, t_file *files, t_opt *option)
{
	int		nb_error;
	int		nb_file;

	files = which_sort(files, option);
	nb_error = display_errors(files);
	nb_file = display_non_dir(files, option);
	if (nb_file != 0 && (nb_file + nb_error) != ac)
		write(1, "\n", 1);
	display_dir(nb_file + nb_error, ac, files, option);
}
