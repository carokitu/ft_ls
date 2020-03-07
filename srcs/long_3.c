/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 14:35:15 by cde-moul          #+#    #+#             */
/*   Updated: 2019/06/06 11:08:35 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		ls_longdate_mod(char **lon, struct stat *sts, int *count)
{
	int		a;
	char	*atime;

	a = 3;
	if (!(atime = ctime(&sts->st_mtime)))
		return ;
	while (++a < 11)
		(*lon)[(*count)++] = atime[a];
	if ((sts->st_mtime + 15778800) < time(NULL) ||
			(sts->st_mtime - time(NULL) > 0))
	{
		a = 20;
		(*lon)[(*count)++] = ' ';
		while (a < 24)
			(*lon)[(*count)++] = atime[a++];
	}
	else
	{
		while (a < 16)
			(*lon)[(*count)++] = atime[a++];
	}
	(*lon)[(*count)++] = ' ';
	(*lon)[(*count)++] = '\0';
}

void		ls_longdate_access(char **lon, struct stat *sts, int *count)
{
	int		a;
	char	*atime;

	a = 3;
	atime = ctime(&sts->st_atime);
	while (++a < 11)
		(*lon)[(*count)++] = atime[a];
	if ((sts->st_atime + 15778800) < time(NULL) ||
			(sts->st_atime - time(NULL) > 0))
	{
		a = 20;
		(*lon)[(*count)++] = ' ';
		while (a < 24)
			(*lon)[(*count)++] = atime[a++];
	}
	else
	{
		while (a < 16)
			(*lon)[(*count)++] = atime[a++];
	}
	(*lon)[(*count)++] = ' ';
	(*lon)[(*count)++] = '\0';
}

void		ls_longdate(char **lon, int flags, struct stat *sts, int *count)
{
	if (flags & SMALL_U)
		ls_longdate_access(lon, sts, count);
	else
		ls_longdate_mod(lon, sts, count);
}

void		ls_longtreat_bis(char **lon, char *file, int flags)
{
	struct stat		*sts;
	int				a;

	if (!(sts = (struct stat *)malloc(sizeof(struct stat))))
		return ;
	lstat(file, sts);
	a = 0;
	while (a < 100)
		(*lon)[a++] = '\0';
	ls_longtype(sts, lon);
	ls_longrights(sts, lon);
	ls_longdetails(lon, flags, &sts, file);
}

void		ls_longsize2(char **lon, int *count, int cout, long long cp)
{
	while (cp > 9)
	{
		(*lon)[--cout] = (cp % 10) + 48;
		cp = cp / 10;
	}
	(*lon)[--cout] = cp + 48;
	while (cout > (*count))
		(*lon)[--cout] = ' ';
}
