/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 10:41:20 by cde-moul          #+#    #+#             */
/*   Updated: 2019/06/06 15:21:08 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

char		ls_attributes(char *path)
{
	char		buf[100];
	int			ext;
	acl_t		acl;

	errno = 0;
	acl = NULL;
	acl = acl_get_link_np(path, ACL_TYPE_EXTENDED);
	ext = acl == NULL ? 0 : 2;
	acl_free(acl);
	if (listxattr(path, buf, 100, XATTR_NOFOLLOW) > 0)
		ext = 1;
	if (errno != 0)
		errno = 0;
	if (ext == 2)
		return ('+');
	return (ext == 0 ? ' ' : '@');
}

void		ls_longrights3(struct stat *sts, char **lon)
{
	if (sts->st_mode & S_ISUID)
		(*lon)[3] = (sts->st_mode & S_IXUSR) ? 's' : 'S';
	if (sts->st_mode & S_ISGID)
		(*lon)[6] = (sts->st_mode & S_IXGRP) ? 's' : 'S';
	if (sts->st_mode & S_ISVTX)
		(*lon)[9] = (sts->st_mode & S_IXOTH) ? 't' : 'T';
}

int			ls_recur3_bis(char **path, int *i)
{
	if (errno == 13)
	{
		free(*path);
		(*i)++;
		return (-1);
	}
	return (*i);
}

void		ls_recur3_ter(char **path)
{
	free(*path);
	*path = NULL;
}

void		ls_print_permission(char *name)
{
	ft_putstr("./ft_ls: ");
	ft_putstr(name);
	ft_putstr(": Permission denied\n");
}
