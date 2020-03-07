/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 09:42:50 by cde-moul          #+#    #+#             */
/*   Updated: 2019/06/06 13:54:11 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void			ls_longtreat2_bis(struct stat **sts, char **lon, int *total)
{
	(*total) = (*total) + (*sts)->st_blocks;
	ls_longtype(*sts, lon);
	ls_longrights(*sts, lon);
}

static void		ls_longtreat2_ter(int total, t_infos *flags,
		char **lon, char **path)
{
	int		i;

	if (flags->path[0])
	{
		ft_putstr("total ");
		ft_putnbr(total);
		ft_putchar('\n');
	}
	ls_longtreat_norm(lon, flags, path);
	i = -1;
	while (lon[++i])
	{
		free(lon[i]);
		lon[i] = NULL;
	}
	free(lon);
}

static char		**ls_2longtreat2(char **path)
{
	char		**lon;
	int			i;

	i = 0;
	while (path[i])
		i++;
	if (!(lon = (char **)malloc(sizeof(char *) * (1 + i))))
		return (NULL);
	return (lon);
}

int				ls_freelonsts(struct stat **sts, char **lon, int i)
{
	while (i >= 0)
		free(lon[i--]);
	free(lon);
	free(*sts);
	return (1);
}

void			ls_longtreat2(t_infos *flags, char **path)
{
	int			i;
	struct stat	*sts;
	char		**lon;
	int			total;

	total = 0;
	lon = ls_2longtreat2(path);
	i = -1;
	while (path[++i] && flags->path[i])
	{
		if (!(sts = (struct stat *)ft_memalloc(sizeof(struct stat))))
			return ;
		if (!(lon[i] = (char *)malloc(sizeof(char) * 100)))
		{
			free(sts);
			return ;
		}
		if (ls_longtreat2_norm(path[i], &sts, &lon[i], &total) == -1 &&
			ls_freelonsts(&sts, lon, i))
			return ;
		ls_longdetails(&lon[i], flags->flags, &sts, path[i]);
	}
	lon[i] = NULL;
	ls_longtreat2_ter(total, flags, lon, path);
}
