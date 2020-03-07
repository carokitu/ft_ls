/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 14:52:10 by cde-moul          #+#    #+#             */
/*   Updated: 2019/05/21 16:37:20 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static int		ls_cmp_error(char *curse, char *compare)
{
	int i;

	i = 4;
	while (curse[i] && compare[i] && curse[i] != ' ')
	{
		if (curse[i] != compare[i])
		{
			if (compare[i] == ':')
				return (4);
			if (curse[i] == ':' && compare[i] < ':')
				return (-2);
			return (curse[i] - compare[i]);
		}
		i++;
	}
	return (curse[i] - compare[i]);
}

static void		ls_order_error(t_infos *flags)
{
	int		a;
	int		b;
	char	*tmp;

	a = 1;
	while (a < flags->nbr_error)
	{
		b = a - 1;
		while (b >= 0 && ls_cmp_error(flags->error[a], flags->error[b]) < 0)
		{
			tmp = ft_strdup(flags->error[a]);
			free(flags->error[a]);
			flags->error[a] = NULL;
			flags->error[a] = ft_strdup(flags->error[b]);
			free(flags->error[b]);
			flags->error[b] = ft_strdup(tmp);
			free(tmp);
			a = b;
			b = a - 1;
		}
		a++;
	}
}

void			ls_printf_error(t_infos *flags)
{
	int		a;

	a = -1;
	ls_order_error(flags);
	while (++a < flags->nbr_error)
		ft_putstr_fd(flags->error[a], STDERR_FILENO);
	a = -1;
	while (++a < flags->nbr_error)
		free(flags->error[a]);
}

void			ls_rev_path(char **path)
{
	int		i;
	int		a;
	char	*tmp;

	a = 0;
	i = 0;
	tmp = NULL;
	while (path[a])
		a++;
	path[a] = NULL;
	a--;
	while (a > i)
	{
		tmp = ft_strdup(path[a]);
		free(path[a]);
		path[a] = NULL;
		path[a] = ft_strdup(path[i]);
		free(path[i]);
		path[i] = NULL;
		path[i] = ft_strdup(tmp);
		free(tmp);
		a--;
		i++;
	}
}

void			ls_hidden_files(t_infos *flags)
{
	int a;
	int	i;

	a = 0;
	while (flags->path[a])
	{
		i = a;
		if (flags->path[a][0] == '.')
		{
			while (flags->path[i + 1])
			{
				free(flags->path[i]);
				flags->path[i] = NULL;
				flags->path[i] = ft_strdup(flags->path[i + 1]);
				i++;
			}
			free(flags->path[i]);
			flags->path[i] = NULL;
			a--;
		}
		a++;
	}
}
