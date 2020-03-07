/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 11:44:18 by cde-moul          #+#    #+#             */
/*   Updated: 2019/06/06 11:47:12 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		ls_rev_path2_bis(char **file, char **path, int a, int i)
{
	char *tmp;

	tmp = ft_strdup(path[a]);
	free(path[a]);
	path[a] = NULL;
	path[a] = ft_strdup(path[i]);
	free(path[i]);
	path[i] = NULL;
	path[i] = ft_strdup(tmp);
	free(tmp);
	tmp = ft_strdup(file[a]);
	free(file[a]);
	file[a] = NULL;
	file[a] = ft_strdup(file[i]);
	free(file[i]);
	file[i] = NULL;
	file[i] = ft_strdup(tmp);
	free(tmp);
}

void		ls_sort_path_norm(t_infos *flags, t_rep *rep, char **path)
{
	t_rep	*wlk;
	int		a;
	char	*debut;
	char	*tmp;

	wlk = rep;
	if (rep == NULL)
		debut = ft_strdup("./");
	else
		debut = ft_strjoin(wlk->name, "/");
	while (wlk->master != NULL)
	{
		wlk = wlk->master;
		tmp = ft_strjoin("/", debut);
		free(debut);
		debut = ft_strjoin(wlk->name, tmp);
		free(tmp);
	}
	a = -1;
	while (flags->path[++a])
		path[a] = ft_strjoin(debut, flags->path[a]);
	path[a] = NULL;
	free(debut);
	return ;
}
