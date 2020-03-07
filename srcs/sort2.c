/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 14:10:07 by cde-moul          #+#    #+#             */
/*   Updated: 2019/06/06 11:29:40 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void	ls_sort_path2_ter(char **path, t_infos *flags, int *count, int *cmp)
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
	tmp = ft_strdup(flags->path[*count]);
	free(flags->path[*count]);
	flags->path[*count] = NULL;
	flags->path[*count] = ft_strdup(flags->path[*cmp]);
	free(flags->path[*cmp]);
	flags->path[*cmp] = NULL;
	flags->path[*cmp] = ft_strdup(tmp);
	free(tmp);
	tmp = NULL;
	*count = *cmp;
	*cmp = *count - 1;
}

static void	ls_rev_path2(char **file, char **path)
{
	int		i;
	int		a;

	a = 0;
	i = 0;
	while (path[a])
		a++;
	a--;
	while (a > i)
	{
		ls_rev_path2_bis(file, path, a, i);
		a--;
		i++;
	}
	a = 0;
	while (path[a])
		a++;
	path[a] = NULL;
}

int			ls_sort_size(char *curse, char *compare)
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
	i = st_compare->st_size - st_curse->st_size;
	free(st_curse);
	free(st_compare);
	if (i == 0)
		i = ls_sort_alpha(curse, compare);
	return (i);
}

static void	ls_sort_path2_bis(t_infos *flags, char **path)
{
	int		(*fonction[3])(char *curse, char *compare);
	int		a;
	int		count;
	int		cmp;

	count = -1;
	a = 0;
	fonction[0] = ls_sort_alpha;
	fonction[1] = ls_sort_mod;
	fonction[2] = ls_sort_size;
	if (flags->flags & SMALL_F)
		return ;
	if (flags->flags & SMALL_T)
		a = 1;
	if (flags->flags & BIG_S)
		a = 2;
	while (path[++count] != NULL)
	{
		cmp = count - 1;
		while (cmp >= 0 && fonction[a](path[count], path[cmp]) < 0)
			ls_sort_path2_ter(path, flags, &count, &cmp);
	}
	if (flags->flags & SMALL_R)
		ls_rev_path2(flags->path, path);
}

char		**ls_sort_path2(t_infos *flags, t_rep *rep)
{
	int		a;
	char	**path;

	a = 0;
	while (flags->path[a])
		a++;
	if (!(path = (char **)malloc(sizeof(char *) * (a + 1))))
		return (NULL);
	ls_sort_path_norm(flags, rep, path);
	ls_sort_path2_bis(flags, path);
	return (path);
}
