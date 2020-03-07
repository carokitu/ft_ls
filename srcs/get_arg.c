/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 13:34:35 by cde-moul          #+#    #+#             */
/*   Updated: 2019/06/06 15:34:16 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void	ls_manage_error_2(t_infos *flags, int a)
{
	char	*tmp;

	tmp = ft_strjoin("./ft_ls: ", flags->path[a]);
	flags->error[flags->nbr_error++] = (errno == 2) ?
		ft_strjoin(tmp, ": No such file or directory\n") :
		ft_strjoin(tmp, ": Bad file descriptor\n");
	errno = 0;
	free(tmp);
	while (flags->path[a + 1])
	{
		free(flags->path[a]);
		flags->path[a] = ft_strdup(flags->path[a + 1]);
		a++;
	}
	free(flags->path[a]);
	flags->path[a] = NULL;
}

static void	ls_manage_error(t_infos *flags)
{
	int			a;
	int			b;
	struct stat	*test;

	a = 0;
	b = 0;
	errno = 0;
	while (flags->path[a])
	{
		if (!(test = (struct stat *)malloc(sizeof(struct stat))))
			return ;
		if (stat(flags->path[a], test) == -1)
		{
			if (errno == EACCES)
				ls_manage_error_3(flags, a--);
			else
				ls_manage_error_2(flags, a--);
		}
		free(test);
		a++;
	}
}

static void	ls_next(t_infos *flags)
{
	int count;

	count = -1;
	ls_manage_error(flags);
	ls_printf_error(flags);
	ls_sort_path(flags, flags->path);
	ls_treat(flags);
}

static int	ls_get_arg2(char *arg, t_infos *flags)
{
	int		nb;
	int		pos;

	nb = 1;
	pos = -1;
	while (arg[nb])
	{
		pos = ft_chrpos(OPTIONS, arg[nb]);
		if (pos == -1)
		{
			ft_putstr_fd("./ft_ls: illegal option -- ", STDERR_FILENO);
			ft_putchar_fd(arg[nb], STDERR_FILENO);
			ft_putchar_fd('\n', STDERR_FILENO);
			ft_putstr_fd("usage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1]",
					STDERR_FILENO);
			ft_putstr_fd(" [file ...]", STDERR_FILENO);
			ft_putchar_fd('\n', STDERR_FILENO);
			return (0);
		}
		flags->flags |= (1 << pos);
		nb++;
	}
	return (1);
}

int			ls_get_arg(t_infos *flags, int argv, char **argc)
{
	int	nb;
	int count;

	count = 0;
	nb = 1;
	while (nb < argv && argc[nb][0] == '-' && argc[nb][1]
			&& !(argc[nb][1] == '-' && argc[nb][2] == '\0'))
	{
		if (ls_get_arg2(argc[nb], flags) == 0)
			return (-1);
		nb++;
	}
	if (argc[nb] && argc[nb][0] == '-' && argc[nb][1] == '-'
			&& argc[nb][2] == '\0')
		nb++;
	if (nb == argv)
		flags->path[count++] = ft_strdup(".");
	while (nb < argv)
		flags->path[count++] = ft_strdup(argc[nb++]);
	flags->path[count] = NULL;
	ls_next(flags);
	return (1);
}
