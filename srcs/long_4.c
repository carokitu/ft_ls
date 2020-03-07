/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 16:43:04 by cde-moul          #+#    #+#             */
/*   Updated: 2019/06/06 11:16:12 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void	ls_longtreat_norm2(char **lon, t_infos *flags, char **path, int i)
{
	char	buf[100];

	ft_bzero(buf, 100);
	readlink(path[i], buf, 99);
	ft_putstr(lon[i]);
	ft_putstr(flags->path[i]);
	ft_putstr(" -> ");
	ft_putstr(buf);
	ft_putchar('\n');
}

void		ls_longtreat_norm(char **lon, t_infos *flags, char **path)
{
	int		i;

	i = -1;
	while (lon[++i])
	{
		if (!(lon[i][0] == 'l'))
		{
			ft_putstr(lon[i]);
			if (lon[i][0] != '\0')
			{
				ft_putstr(flags->path[i]);
				ft_putchar('\n');
			}
		}
		else
			ls_longtreat_norm2(lon, flags, path, i);
	}
}

int			ls_longtreat2_norm(char *path, struct stat **sts, char **lon,
		int *total)
{
	errno = 0;
	lstat(path, *sts);
	ft_bzero(*lon, 100);
	if (errno != 0 && errno != 9)
	{
		errno = 0;
		return (-1);
	}
	ls_longtreat2_bis(sts, lon, total);
	return (0);
}
