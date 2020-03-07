/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 11:21:14 by cde-moul          #+#    #+#             */
/*   Updated: 2019/06/05 16:42:38 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int			ls_do_your_job2(t_infos *flags, t_rep **rep, int a, char *file)
{
	DIR				*dir;
	struct dirent	*dirent;

	if (!(flags->path = (char **)malloc(sizeof(char *) * (a + 1))))
		return (-1);
	a = 0;
	dir = opendir(file);
	while ((dirent = readdir(dir)) != NULL)
		flags->path[a++] = ft_strdup(dirent->d_name);
	closedir(dir);
	flags->path[a] = NULL;
	ls_job_part_2(flags, *rep);
	return (1);
}

void		ls_in_algo(t_rep **rep, t_rep **tmp)
{
	if ((*rep)->next->name != NULL)
		(*rep) = (*rep)->next;
	else if ((*rep)->master != NULL)
	{
		while ((*rep)->next->name == NULL && (*rep)->master != NULL)
		{
			(*rep) = (*rep)->master;
			if ((*rep)->next->name == NULL && (*rep)->master != NULL)
			{
				ls_free_line(*tmp);
				(*tmp) = (*rep);
			}
		}
		(*rep) = (*rep)->next;
		ls_free_line(*tmp);
	}
	else
		(*rep) = (*rep)->next;
}

void		ls_put_and_free(t_rep **rep, t_infos *flags, char *file, int u)
{
	int	a;

	a = 0;
	if ((*rep)->next->name != NULL || u != 0 || (*rep)->prev != NULL
			|| (*rep)->master != NULL || flags->nbr_error != 0)
	{
		ft_putstr(file);
		ft_putstr(":\n");
	}
	a = -1;
	while (flags->path[++a])
		free(flags->path[a]);
}

void		ls_longdetails2(char **lon, struct stat *sts, int *count,
		int flags)
{
	if (!(flags & SMALL_G))
	{
		ls_longusername(lon, count, sts);
		(*lon)[(*count)++] = ' ';
		(*lon)[(*count)++] = ' ';
	}
	if (!(flags & SMALL_O))
	{
		ls_longgroupename(lon, count, sts);
		(*lon)[(*count)++] = ' ';
		(*lon)[(*count)++] = ' ';
	}
	if (flags & SMALL_O && flags & SMALL_G)
	{
		(*lon)[(*count)++] = ' ';
		(*lon)[(*count)++] = ' ';
	}
	if (S_ISCHR(sts->st_mode) || S_ISBLK(sts->st_mode))
		ls_longdev(lon, count, sts);
	else
		ls_longsize(lon, count, sts);
}
