/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 18:44:10 by cde-moul          #+#    #+#             */
/*   Updated: 2019/06/06 14:43:19 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void			ls_longtype(struct stat *sts, char **lon)
{
	if (S_ISREG(sts->st_mode))
		(*lon)[0] = '-';
	else if (S_ISDIR(sts->st_mode))
		(*lon)[0] = 'd';
	else if (S_ISFIFO(sts->st_mode))
		(*lon)[0] = 'p';
	else if (S_ISBLK(sts->st_mode))
		(*lon)[0] = 'b';
	else if (S_ISLNK(sts->st_mode))
		(*lon)[0] = 'l';
	else if (S_ISSOCK(sts->st_mode))
		(*lon)[0] = 's';
	else if (S_ISCHR(sts->st_mode))
		(*lon)[0] = 'c';
}

static void		ls_longrights2(struct stat *sts, char **lon)
{
	if (sts->st_mode & S_IROTH)
		(*lon)[7] = 'r';
	else
		(*lon)[7] = '-';
	if (sts->st_mode & S_IWOTH)
		(*lon)[8] = 'w';
	else
		(*lon)[8] = '-';
	if (sts->st_mode & S_IXOTH)
		(*lon)[9] = 'x';
	else
		(*lon)[9] = '-';
}

static void		ls_longrights1(struct stat *sts, char **lon)
{
	if (sts->st_mode & S_IRGRP)
		(*lon)[4] = 'r';
	else
		(*lon)[4] = '-';
	if (sts->st_mode & S_IWGRP)
		(*lon)[5] = 'w';
	else
		(*lon)[5] = '-';
	if (sts->st_mode & S_IXGRP)
		(*lon)[6] = 'x';
	else
		(*lon)[6] = '-';
	ls_longrights2(sts, lon);
}

void			ls_longrights(struct stat *sts, char **lon)
{
	if (sts->st_mode & S_IRUSR)
		(*lon)[1] = 'r';
	else
		(*lon)[1] = '-';
	if (sts->st_mode & S_IWUSR)
		(*lon)[2] = 'w';
	else
		(*lon)[2] = '-';
	if (sts->st_mode & S_IXUSR)
		(*lon)[3] = 'x';
	else
		(*lon)[3] = '-';
	ls_longrights1(sts, lon);
	ls_longrights3(sts, lon);
}

void			ls_longtreat(int flags, char **file)
{
	int			i;
	char		*lon;
	char		buf[100];

	i = -1;
	while (file[++i])
	{
		if (!(lon = (char *)malloc(sizeof(char) * 100)))
			return ;
		ls_longtreat_bis(&lon, file[i], flags);
		if (!(lon[0] == 'l'))
			ft_printf("%s%s\n", lon, file[i]);
		else
		{
			ft_bzero(buf, 100);
			readlink(file[i], buf, 100);
			ft_printf("%s%s -> %s\n", lon, file[i], buf);
		}
		free(lon);
	}
}
