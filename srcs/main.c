/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 12:33:01 by cde-moul          #+#    #+#             */
/*   Updated: 2019/06/06 15:18:40 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void		ls_start(int argv, char **argc)
{
	t_infos	*flags;

	if (!(flags = (t_infos *)malloc(sizeof(t_infos))))
		return ;
	if (ls_init_flags(flags, argv) == -1)
		return ;
	if (ls_get_arg(flags, argv, argc) == 1)
		ls_free_flags(flags, argv);
	else
	{
		free(flags->path);
		free(flags->error);
		free(flags);
	}
}

int				ls_test(char *path, t_infos *flags)
{
	struct stat	*sts;

	if (!(sts = (struct stat *)malloc(sizeof(struct stat))))
		return (0);
	lstat(path, sts);
	if (S_ISLNK(sts->st_mode) &&
			(flags->flags & SMALL_L || flags->flags & SMALL_G ||
			flags->flags & SMALL_O))
	{
		free(sts);
		return (1);
	}
	free(sts);
	return (0);
}

int				main(int argv, char **argc)
{
	if (argv < 1)
		return (0);
	ls_start(argv, argc);
	return (1);
}
