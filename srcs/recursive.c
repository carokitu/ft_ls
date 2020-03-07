/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 10:17:27 by cde-moul          #+#    #+#             */
/*   Updated: 2019/06/06 15:06:03 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void	ls_put_in_struct3(t_rep **rep, t_rep **wlk)
{
	t_rep	*new;

	if (!(new = (t_rep *)malloc(sizeof(t_rep))))
		return ;
	new->master = *rep;
	new->prev = *wlk;
	new->name = NULL;
	new->next = NULL;
	(*wlk)->next = new;
	*rep = new;
	while ((*rep)->prev != NULL)
		*rep = (*rep)->prev;
}

static void	ls_put_in_struct2(t_infos *flags, t_rep **rep, t_rep *new)
{
	int		i;
	t_rep	*wlk;

	i = 0;
	if (flags->path[0])
	{
		if (!(wlk = (t_rep *)malloc(sizeof(t_rep))))
			return ;
		wlk->master = *rep;
		wlk->prev = NULL;
		wlk->next = NULL;
		wlk->name = ft_strdup(flags->path[0]);
	}
	while (flags->path[++i])
	{
		if (!(new = (t_rep *)malloc(sizeof(t_rep))))
			return ;
		new->master = *rep;
		new->prev = wlk;
		new->next = NULL;
		new->name = ft_strdup(flags->path[i]);
		wlk->next = new;
		wlk = wlk->next;
	}
	ls_put_in_struct3(rep, &wlk);
}

static char	*ls_recur2(t_rep **rep, char *path)
{
	t_rep	*wlk;
	char	*tmp;

	wlk = *rep;
	while (wlk->master != NULL)
	{
		wlk = wlk->master;
		tmp = ft_strjoin("/", path);
		free(path);
		path = ft_strjoin(wlk->name, tmp);
		free(tmp);
	}
	if (path[0] != '/')
	{
		tmp = path;
		path = ft_strjoin("./", path);
		free(tmp);
	}
	return (path);
}

static void	ls_recur3(t_infos *flags, char *tmp, int *i)
{
	char	*path;
	DIR		*dir;
	int		a;

	a = 0;
	path = ft_strjoin(tmp, flags->path[*i]);
	if ((dir = opendir(path)) == NULL || ft_strcmp(flags->path[*i], "..") == 0
			|| ft_strcmp(flags->path[*i], ".") == 0 || ls_islink(path) == 0)
	{
		if ((a = ls_recur3_bis(&path, i)) == -1)
			return ;
		while (flags->path[a + 1])
		{
			free(flags->path[a]);
			flags->path[a] = NULL;
			flags->path[a] = ft_strdup(flags->path[a + 1]);
			a++;
		}
		ls_recur3_ter(&flags->path[a]);
		(*i)--;
	}
	if (dir != NULL)
		closedir(dir);
	(*i)++;
	free(path);
}

int			ls_recur(t_infos *flags, t_rep **rep, t_rep *wlk)
{
	int		i;
	int		a;
	char	*path;
	char	*tmp;
	t_rep	*new;

	new = NULL;
	wlk = *rep;
	a = 0;
	i = 0;
	path = NULL;
	if ((*rep) == NULL)
		path = ft_strdup("./");
	else
		path = ft_strjoin(wlk->name, "/");
	tmp = ls_recur2(rep, path);
	while (flags->path[i] != NULL)
		ls_recur3(flags, tmp, &i);
	free(tmp);
	if (flags->path[0] == NULL)
		return (0);
	ls_put_in_struct2(flags, rep, new);
	return (1);
}
