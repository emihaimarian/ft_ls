/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mienache <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 14:51:03 by mienache          #+#    #+#             */
/*   Updated: 2018/02/18 14:51:12 by mienache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int ac, char **av)
{
	t_file	*files;
	t_opt	option;

	files = NULL;
	check_arg_vid(ac, av);
	init_options(&option);
	ac = read_options(ac, &av, &option);
	read_names(ac, av, &files, &option);
	if (option.l)
		long_display(ac, files, &option);
	else
		classic_display(ac, files, &option);
	free_file(&files);
	return (0);
}
