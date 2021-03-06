/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sorting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mienache <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 14:51:17 by mienache          #+#    #+#             */
/*   Updated: 2018/02/18 14:51:19 by mienache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_comp	g_comp[] =
{
	sort_ascii,
	reverse_sort_ascii,
	sort_size,
	reverse_sort_size,
	sort_time_modified,
	reverse_sort_time_modified,
	sort_last_access,
	reverse_sort_last_access,
	sort_birth_time,
	reverse_sort_birth_time
};

t_file	*which_sort(t_file *files, t_opt *option)
{
	int i;

	if ((file_list_len(files)) < 2 || option->f || not_sortable(files, option))
		return (files);
	i = 0;
	if (option->u_s)
		i = 2;
	if (option->t)
		i = 4;
	if (option->t && option->u)
		i += 2;
	if (option->t && option->u_u)
		i += 4;
	if (option->r)
		i += 1;
	return (merge_sort(files, g_comp[i]));
}

t_file	*merge_sort(t_file *files, void (*f)(t_file**, t_file**, t_file**))
{
	t_file	*left;
	t_file	*right;
	int		len;
	int		half;
	int		i;

	if (files->next == NULL)
		return (files);
	len = file_list_len(files);
	half = len / 2;
	i = 0;
	left = files;
	while (i < half - 1)
	{
		left = left->next;
		i++;
	}
	right = left->next;
	left->next = NULL;
	left = files;
	left = merge_sort(left, f);
	right = merge_sort(right, f);
	return (merge(left, right, f));
}

t_file	*merge(t_file *left, t_file *right,
	void (*f)(t_file**, t_file**, t_file**))
{
	t_file	*head;
	t_file	*temp;
	t_file	*tail;

	head = NULL;
	while (left || right)
	{
		if (!left)
			pick_last_elem(&temp, &right);
		else
		{
			if (!right)
				pick_last_elem(&temp, &left);
			else
				f(&temp, &left, &right);
		}
		if (!head)
			head = temp;
		else
			tail->next = temp;
		tail = temp;
	}
	return (head);
}

void	pick_last_elem(t_file **temp, t_file **side)
{
	*temp = *side;
	*side = (*side)->next;
}

int		file_list_len(t_file *files)
{
	t_file	*temp;
	int		len;

	if (!files)
		return (0);
	len = 0;
	temp = files;
	while (temp)
	{
		len++;
		temp = temp->next;
	}
	return (len);
}
