/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 17:29:09 by cde-moul          #+#    #+#             */
/*   Updated: 2019/06/06 15:11:02 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void	ls_file_3(t_infos *flags, char **file)
{
	int a;

	a = -1;
	if (flags->flags & SMALL_L || flags->flags & SMALL_G
			|| flags->flags & SMALL_O)
		ls_longtreat(flags->flags, file);
	else
	{
		while (file[++a])
		{
			ft_putstr(file[a]);
			ft_putchar('\n');
		}
	}
}

static void	ls_file_2_bis(t_infos *flags, char **file, int i)
{
	int f;

	f = 0;
	while (file[f])
		f++;
	file[f++] = ft_strdup(flags->path[i]);
	file[f] = NULL;
	while (flags->path[i + 1])
	{
		free(flags->path[i]);
		flags->path[i] = NULL;
		flags->path[i] = ft_strdup(flags->path[i + 1]);
		i++;
	}
	free(flags->path[i]);
	flags->path[i] = NULL;
}

static int	ls_file_2(t_infos *flags, char **file)
{
	DIR			*dir;
	int			i;

	errno = 0;
	i = 0;
	while (flags->path[i])
	{
		if (flags->flags & SMALL_D || ((dir = opendir(flags->path[i])) == NULL
			&& errno != 13) || (ls_test(flags->path[i], flags) == 1))
		{
			ls_file_2_bis(flags, file, i);
			i--;
		}
		if (dir != NULL)
			closedir(dir);
		i++;
		errno = 0;
	}
	if (file[0] != NULL)
		return (1);
	return (0);
}

static int	ls_file(t_infos *flags)
{
	char	**file;
	int		i;
	int		a;

	i = 0;
	while (flags->path[i])
		i++;
	if (!(file = (char **)malloc(sizeof(char *) * (i + 1))))
		return (-1);
	i--;
	while (i >= 0)
		file[i--] = NULL;
	if (ls_file_2(flags, file) != 0)
		ls_file_3(flags, file);
	a = 0;
	while (file[a])
	{
		free(file[a]);
		file[a] = NULL;
		a++;
	}
	free(file);
	return (a);
}

void		ls_treat(t_infos *flags)
{
	int	a;

	if (flags->path[0] == NULL)
		return ;
	a = ls_file(flags);
	if (a == -1)
		return ;
	if (flags->path[0] != NULL)
	{
		if (a != 0)
			ft_putchar('\n');
		ls_open(flags, a);
	}
}
