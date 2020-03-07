/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 15:30:09 by cde-moul          #+#    #+#             */
/*   Updated: 2019/06/06 11:25:59 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int			ls_sort_alpha(char *curse, char *compare)
{
	int		i;

	i = 0;
	while (curse[i] && compare[i])
	{
		if (curse[i] != compare[i])
			return (curse[i] - compare[i]);
		i++;
	}
	return (curse[i] - compare[i]);
}

int			ls_sort_mod(char *curse, char *compare)
{
	int			i;
	struct stat *st_curse;
	struct stat	*st_compare;

	i = 0;
	if (!(st_curse = (struct stat *)malloc(sizeof(struct stat))))
		return (0);
	if (!(st_compare = (struct stat *)malloc(sizeof(struct stat))))
	{
		free(st_curse);
		return (0);
	}
	if (stat(curse, st_curse) == -1 || stat(compare, st_compare) == -1)
	{
		free(st_curse);
		free(st_compare);
		return (0);
	}
	i = st_compare->st_mtime - st_curse->st_mtime;
	free(st_curse);
	free(st_compare);
	if (i == 0)
		i = ls_sort_alpha(curse, compare);
	return (i);
}

int			ls_sort_access(char *curse, char *compare)
{
	int			i;
	struct stat *st_curse;
	struct stat	*st_compare;

	i = 0;
	if (!(st_curse = (struct stat *)malloc(sizeof(struct stat))))
		return (0);
	if (!(st_compare = (struct stat *)malloc(sizeof(struct stat))))
	{
		free(st_curse);
		return (0);
	}
	if (stat(curse, st_curse) == -1 || stat(compare, st_compare) == -1)
	{
		free(st_curse);
		free(st_compare);
		return (0);
	}
	i = st_compare->st_atime - st_curse->st_atime;
	free(st_curse);
	free(st_compare);
	if (i == 0)
		i = ls_sort_alpha(curse, compare);
	return (i);
}

static void	ls_sort_path_2(char **path, int *count, int *cmp)
{
	char	*tmp;

	tmp = ft_strdup(path[*count]);
	free(path[*count]);
	path[*count] = NULL;
	path[*count] = ft_strdup(path[*cmp]);
	free(path[*cmp]);
	path[*cmp] = NULL;
	path[*cmp] = ft_strdup(tmp);
	free(tmp);
	tmp = NULL;
	*count = *cmp;
	*cmp = *count - 1;
}

void		ls_sort_path(t_infos *flags, char **path)
{
	int		(*fonction[3])(char *curse, char *compare);
	int		a;
	int		count;
	int		cmp;

	count = 0;
	a = 0;
	fonction[0] = ls_sort_alpha;
	fonction[1] = ls_sort_mod;
	fonction[2] = ls_sort_access;
	if (flags->flags & SMALL_F)
		return ;
	if (flags->flags & SMALL_T || flags->flags & SMALL_U)
		a = (flags->flags & SMALL_T) ? 1 : 2;
	while (path[++count] != NULL)
	{
		cmp = count - 1;
		while (cmp >= 0 && fonction[a](path[count], path[cmp]) < 0)
			ls_sort_path_2(path, &count, &cmp);
	}
	if (flags->flags & SMALL_R)
		ls_rev_path(path);
}
