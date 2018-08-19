/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mienache <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 14:52:10 by mienache          #+#    #+#             */
/*   Updated: 2018/02/18 14:52:11 by mienache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	sort_ascii(t_file **temp, t_file **left, t_file **right)
{
	if ((ft_strcmp((*left)->path, (*right)->path)) < 0)
	{
		*temp = *left;
		*left = (*left)->next;
	}
	else
	{
		*temp = *right;
		*right = (*right)->next;
	}
}

void	sort_time_modified(t_file **temp, t_file **left, t_file **right)
{
	if ((*left)->lstat.st_mtimespec.tv_sec
		== (*right)->lstat.st_mtimespec.tv_sec)
		sort_ascii(temp, left, right);
	else
	{
		if ((*left)->lstat.st_mtimespec.tv_sec
			> (*right)->lstat.st_mtimespec.tv_sec)
		{
			*temp = *left;
			*left = (*left)->next;
		}
		else
		{
			*temp = *right;
			*right = (*right)->next;
		}
	}
}

void	sort_last_access(t_file **temp, t_file **left, t_file **right)
{
	if ((*left)->lstat.st_atimespec.tv_sec
		== (*right)->lstat.st_atimespec.tv_sec)
		sort_ascii(temp, left, right);
	else
	{
		if ((*left)->lstat.st_atimespec.tv_sec
			> (*right)->lstat.st_atimespec.tv_sec)
		{
			*temp = *left;
			*left = (*left)->next;
		}
		else
		{
			*temp = *right;
			*right = (*right)->next;
		}
	}
}

void	sort_size(t_file **temp, t_file **left, t_file **right)
{
	if ((*left)->lstat.st_size == (*right)->lstat.st_size)
		sort_ascii(temp, left, right);
	else
	{
		if ((*left)->lstat.st_size > (*right)->lstat.st_size)
		{
			*temp = *left;
			*left = (*left)->next;
		}
		else
		{
			*temp = *right;
			*right = (*right)->next;
		}
	}
}

void	sort_birth_time(t_file **temp, t_file **left, t_file **right)
{
	if ((*left)->lstat.st_birthtimespec.tv_sec
		== (*right)->lstat.st_birthtimespec.tv_sec)
		sort_ascii(temp, left, right);
	else
	{
		if ((*left)->lstat.st_birthtimespec.tv_sec
			> (*right)->lstat.st_birthtimespec.tv_sec)
		{
			*temp = *left;
			*left = (*left)->next;
		}
		else
		{
			*temp = *right;
			*right = (*right)->next;
		}
	}
}
