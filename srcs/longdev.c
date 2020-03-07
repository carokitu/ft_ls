/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   longdev.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 13:11:32 by cde-moul          #+#    #+#             */
/*   Updated: 2019/06/06 11:17:23 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void		ls_longdev2(char **lon, int *count, int cout, long long cp)
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

static void		ls_longdev3(char **lon, int *count, struct stat *sts)
{
	long long	cp;
	int			cout;
	int			a;

	cout = (*count);
	cp = minor(sts->st_rdev);
	if (cp == 0)
		cout++;
	while (cp > 0)
	{
		cp = cp / 10;
		cout++;
	}
	if (cout < ((*count) + 4))
		cout = (*count) + 4;
	a = cout - (*count);
	cp = minor(sts->st_rdev);
	ls_longdev2(lon, count, cout, cp);
	while (a-- > 0)
		(*count)++;
}

void			ls_longdev(char **lon, int *count, struct stat *sts)
{
	long long	cp;
	int			cout;
	int			a;

	cout = (*count);
	cp = major(sts->st_rdev);
	if (cp == 0)
		cout++;
	while (cp > 0)
	{
		cp = cp / 10;
		cout++;
	}
	if (cout < ((*count) + 4))
		cout = (*count) + 4;
	a = cout - (*count);
	cp = major(sts->st_rdev);
	ls_longdev2(lon, count, cout, cp);
	while (a-- > 0)
		(*count)++;
	(*lon)[(*count)++] = ',';
	(*lon)[(*count)++] = ' ';
	ls_longdev3(lon, count, sts);
}
