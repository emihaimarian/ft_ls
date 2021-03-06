/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_options.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mienache <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 14:52:30 by mienache          #+#    #+#             */
/*   Updated: 2018/02/18 14:52:31 by mienache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	init_options(t_opt *option)
{
	option->u_g = 0;
	option->u_r = 0;
	option->u_s = 0;
	option->u_u = 0;
	option->a = 0;
	option->f = 0;
	option->l = 0;
	option->r = 0;
	option->t = 0;
	option->u = 0;
	option->c1 = 0;
}

void	is_options(char *s, t_opt *option)
{
	s++;
	while (*s)
	{
		if (*s != 'G' && *s != 'R' && *s != 'S' && *s != 'U' && *s != 'a'
			&& *s != 'f' && *s != 'l' && *s != 'r' && *s != 't' && *s != 'u'
			&& *s != '1')
			display_illegal_option(*s);
		else if (check_priority(*s, option))
			save_option(*s, option);
		s++;
	}
}

int		check_priority(char c, t_opt *option)
{
	if (c == 'f')
		option->a = 'a';
	if ((c == 't') && option->u_s)
		return (0);
	if (c == 'S' && (option->t))
		option->t = 0;
	if (c == 'U' && option->u)
		option->u = 0;
	if (c == 'u' && option->u_u)
		option->u_u = 0;
	if (c == '1' && option->l)
		option->l = 0;
	if (c == 'l' && option->c1)
		option->c1 = 0;
	return (1);
}

void	save_option(char c, t_opt *option)
{
	c == 'G' ? option->u_g = 'G' : 0;
	c == 'R' ? option->u_r = 'R' : 0;
	c == 'S' ? option->u_s = 'S' : 0;
	c == 'U' ? option->u_u = 'U' : 0;
	c == 'a' ? option->a = 'a' : 0;
	c == 'f' ? option->f = 'f' : 0;
	c == 'l' ? option->l = 'l' : 0;
	c == 'r' ? option->r = 'r' : 0;
	c == 't' ? option->t = 't' : 0;
	c == 'u' ? option->u = 'u' : 0;
	c == '1' ? option->c1 = '1' : 0;
}

int		read_options(int ac, char ***av, t_opt *option)
{
	while (--ac)
	{
		++*av;
		if (ft_strequ(**av, "-"))
			break ;
		if (ft_strequ(**av, "--"))
		{
			++*av;
			--ac;
			break ;
		}
		if (***av != '-')
			break ;
		else
			is_options(**av, option);
	}
	ac = set_current_dir(ac, av);
	return (ac);
}
