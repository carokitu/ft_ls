/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 15:57:33 by cde-moul          #+#    #+#             */
/*   Updated: 2019/06/06 11:42:02 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		ls_longlink(char **lon, struct stat *sts)
{
	unsigned short		cp;
	int					count;

	count = 14;
	cp = sts->st_nlink;
	while (cp > 9)
	{
		(*lon)[--count] = (cp % 10) + 48;
		cp = cp / 10;
	}
	(*lon)[--count] = cp + 48;
	while (count > 11)
		(*lon)[--count] = ' ';
}

void		ls_longsize(char **lon, int *count, struct stat *sts)
{
	long long			cp;
	int					cout;
	int					a;

	cout = (*count);
	cp = sts->st_size;
	if (cp == 0)
		cout++;
	while (cp > 0)
	{
		cp = cp / 10;
		cout++;
	}
	if (cout < ((*count) + 5))
		cout = (*count) + 5;
	a = cout - (*count);
	cp = sts->st_size;
	ls_longsize2(lon, count, cout, cp);
	while (a-- > 0)
		(*count)++;
}

void		ls_longusername(char **lon, int *count, struct stat *sts)
{
	struct passwd	*user;
	int				a;

	a = -1;
	user = getpwuid(sts->st_uid);
	if (user == NULL)
		return ;
	while (user->pw_name[++a])
		(*lon)[(*count)++] = user->pw_name[a];
}

void		ls_longgroupename(char **lon, int *count, struct stat *sts)
{
	struct group	*group;
	int				a;

	a = -1;
	group = getgrgid(sts->st_gid);
	if (group == NULL)
		return ;
	while (group->gr_name[++a])
		(*lon)[(*count)++] = group->gr_name[a];
}

void		ls_longdetails(char **lon, int flags, struct stat **sts, char *path)
{
	int		count;

	(*lon)[10] = ls_attributes(path);
	ls_longlink(lon, *sts);
	(*lon)[14] = ' ';
	count = 15;
	ls_longdetails2(lon, *sts, &count, flags);
	(*lon)[count++] = ' ';
	ls_longdate(lon, flags, *sts, &count);
	free(*sts);
}
