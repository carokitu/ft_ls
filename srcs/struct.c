/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 12:00:58 by cde-moul          #+#    #+#             */
/*   Updated: 2019/06/06 13:24:44 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void			ls_manage_error_3(t_infos *flags, int a)
{
	char	*tmp;

	tmp = ft_strjoin("ls: ", flags->path[a]);
	flags->error[flags->nbr_error++] =
		ft_strjoin(tmp, ": Permission denied\n");
	free(tmp);
	while (flags->path[a + 1])
	{
		free(flags->path[a]);
		flags->path[a] = ft_strdup(flags->path[a + 1]);
		a++;
	}
	free(flags->path[a]);
	flags->path[a] = NULL;
}

int				ls_islink(char *path)
{
	struct stat	*sts;
	int			a;

	a = 1;
	if (!(sts = (struct stat *)malloc(sizeof(struct stat))))
		return (-1);
	lstat(path, sts);
	if (S_ISLNK(sts->st_mode))
		a = 0;
	free(sts);
	return (a);
}

static void		ls_put_in_struct_2(t_infos *flags, t_rep **rep)
{
	int		a;
	t_rep	*new;

	a = 0;
	while (flags->path[++a])
	{
		if (!(new = (t_rep *)malloc(sizeof(t_rep))))
			return ;
		new->master = NULL;
		new->prev = *rep;
		new->next = NULL;
		new->name = ft_strdup(flags->path[a]);
		(*rep)->next = new;
		(*rep) = (*rep)->next;
	}
}

static t_rep	*ls_put_in_struct(t_infos *flags)
{
	t_rep	*rep;
	t_rep	*new;

	if (flags->path[0])
	{
		if (!(rep = (t_rep *)malloc(sizeof(t_rep))))
			return (NULL);
		rep->master = NULL;
		rep->prev = NULL;
		rep->next = NULL;
		rep->name = ft_strdup(flags->path[0]);
	}
	ls_put_in_struct_2(flags, &rep);
	if (!(new = (t_rep *)malloc(sizeof(t_rep))))
		return (NULL);
	new->master = NULL;
	new->prev = rep;
	new->name = NULL;
	new->next = NULL;
	rep->next = new;
	rep = rep->next;
	while (rep->prev != NULL)
		rep = rep->prev;
	return (rep);
}

void			ls_open(t_infos *flags, int a)
{
	t_rep	*rep;
	int		i;

	rep = ls_put_in_struct(flags);
	i = 0;
	while (flags->path[i])
		i++;
	while (--i >= 0)
	{
		free(flags->path[i]);
		flags->path[i] = NULL;
	}
	ls_algo(flags, rep, a);
}
