/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_misc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mienache <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 14:51:23 by mienache          #+#    #+#             */
/*   Updated: 2018/02/18 14:51:30 by mienache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	check_arg_vid(int ac, char **av)
{
	struct stat	av_stat;
	int			ret;

	while (--ac)
	{
		++av;
		if ((ft_strequ(*av, "")))
		{
			if ((ret = stat("", &av_stat)) == -1)
			{
				ft_putstr_fd(LS, 2);
				ft_putstr_fd(""":", 2);
				ft_exit(strerror(errno));
			}
		}
	}
}

int		set_current_dir(int ac, char ***av)
{
	if (ac == 0)
	{
		ac++;
		**av = ".";
	}
	return (ac);
}

void	file_init(t_file *elem)
{
	elem->error = 0;
	elem->path = NULL;
	elem->name = NULL;
	elem->color_name = NULL;
	elem->long_format = NULL;
	elem->usr = NULL;
	elem->grp = NULL;
	elem->next = NULL;
	elem->inside = NULL;
	elem->len.nblink = 0;
	elem->len.user = 0;
	elem->len.group = 0;
	elem->len.size = 0;
	elem->len.maj = 0;
	elem->len.min = 0;
	elem->len.total = 0;
}

char	*create_path(char *s1, char *s2, char *s3)
{
	char	*path;

	if (ft_strequ(s1, "/"))
		path = ft_strjoin(s2, s3);
	else
		path = ft_strjoin3(s1, s2, s3);
	return (path);
}

void	get_usr_group_struct(t_file *elem)
{
	char	*temp;

	temp = NULL;
	elem->usr = NULL;
	elem->grp = NULL;
	if ((elem->usr = getpwuid(elem->lstat.st_uid)) == NULL)
	{
		temp = ft_itoa(elem->lstat.st_uid);
		elem->len.user = ft_strlen(temp);
		free(temp);
	}
	else
		elem->len.user = ft_strlen(elem->usr->pw_name);
	if ((elem->grp = getgrgid(elem->lstat.st_gid)) == NULL)
	{
		temp = ft_itoa(elem->lstat.st_uid);
		elem->len.group = ft_strlen(temp);
		free(temp);
	}
	else
		elem->len.group = ft_strlen(elem->grp->gr_name);
}
