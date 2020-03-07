/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 12:23:08 by cde-moul          #+#    #+#             */
/*   Updated: 2019/06/06 15:22:11 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void			ls_job_part_2(t_infos *flags, t_rep *rep)
{
	char	**path;
	int		i;

	i = 0;
	if (!(flags->flags & SMALL_A || flags->flags & SMALL_F))
		ls_hidden_files(flags);
	path = ls_sort_path2(flags, rep);
	if (flags->flags & SMALL_L || flags->flags & SMALL_G
			|| flags->flags & SMALL_O)
		ls_longtreat2(flags, path);
	else
	{
		while (flags->path[i])
		{
			ft_putstr(flags->path[i++]);
			ft_putchar('\n');
		}
	}
	i = -1;
	while (path[++i])
	{
		free(path[i]);
		path[i] = NULL;
	}
	free(path);
}

static int		ls_do_your_job(t_infos *flags, t_rep **rep, int u, char *file)
{
	DIR				*dir;
	int				a;
	t_rep			*wlk;

	wlk = NULL;
	ls_put_and_free(rep, flags, file, u);
	a = 0;
	errno = 0;
	dir = opendir(file);
	if (dir == NULL || errno == 13)
	{
		if (errno == 13)
			ls_print_permission((*rep)->name);
		errno = 0;
		flags->path[0] = NULL;
		return (0);
	}
	while (readdir(dir))
		a++;
	closedir(dir);
	free(flags->path);
	if (ls_do_your_job2(flags, rep, a, file) == -1)
		return (-1);
	return (flags->flags & BIG_R ? ls_recur(flags, rep, wlk) : 0);
}

static char		*ls_get_path(t_rep *rep)
{
	t_rep	*wlk;
	char	*tmp;
	char	*tmpp;

	wlk = rep;
	if (wlk->master == NULL)
		return (ft_strdup(rep->name));
	else
		tmp = ft_strdup(wlk->name);
	while (wlk->master != NULL)
	{
		wlk = wlk->master;
		tmpp = ft_strjoin("/", tmp);
		free(tmp);
		if (ft_strcmp(wlk->name, "/") != 0)
			tmp = ft_strjoin(wlk->name, tmpp);
		else
			tmp = ft_strdup(tmpp);
		free(tmpp);
	}
	return (tmp);
}

void			ls_free_line(t_rep *rep)
{
	t_rep		*tmp;

	while (rep->prev != NULL)
		rep = rep->prev;
	while (rep->name != NULL)
	{
		tmp = rep;
		free(rep->name);
		rep->name = NULL;
		rep->master = NULL;
		rep->prev = NULL;
		rep = rep->next;
		free(tmp);
	}
	free(rep);
}

void			ls_algo(t_infos *flags, t_rep *rep, int u)
{
	int			i;
	char		*file;
	t_rep		*tmp;

	while (rep->prev != NULL)
		rep = rep->prev;
	while (rep->name != NULL)
	{
		file = ls_get_path(rep);
		i = ls_do_your_job(flags, &rep, u, file);
		free(file);
		tmp = rep;
		if (i == 0)
			ls_in_algo(&rep, &tmp);
		if (i == -1)
			return ;
		if (rep->name != NULL)
			ft_putchar('\n');
	}
	ls_free_line(rep);
}
