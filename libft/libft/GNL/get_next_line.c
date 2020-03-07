/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 15:08:33 by cde-moul          #+#    #+#             */
/*   Updated: 2018/12/05 18:20:12 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_if_save(char **save, char **line)
{
	char		*tmp;
	size_t		t;

	t = ft_char_in_str(*save, '\n');
	if (!(*line = ft_strsub(*save, 0, t)))
		return (0);
	tmp = *save;
	if (t < (ft_strlen(*save)))
	{
		if (t < (ft_strlen(*save) - 1))
		{
			if (!(*save = ft_strsub(tmp, t + 1, (ft_strlen(*save) - t - 1))))
				return (0);
			ft_strdel(&tmp);
		}
		else
			ft_strdel(save);
		return (2);
	}
	else
	{
		if (*save)
			ft_strdel(save);
	}
	return (1);
}

static int	ft_if_line(char *buf, char **save, char **line)
{
	size_t	t;
	char	*tmp;
	size_t	len;

	t = ft_char_in_str(buf, '\n');
	tmp = *line;
	len = ft_strlen(buf);
	buf[t] = '\0';
	if (!(*line = ft_strjoin(tmp, buf)))
		return (0);
	ft_strdel(&tmp);
	if (t == len)
		return (1);
	else
	{
		if (t < (len - 1))
		{
			if (!(*save = ft_strsub(buf, t + 1, len - t - 1)))
				return (0);
		}
		else
			ft_strdel(save);
		return (2);
	}
	return (1);
}

static int	ft_no_line(char *buf, size_t t, char **save, char **line)
{
	if (!(*line = ft_strsub(buf, 0, t)))
	{
		if (*save)
			ft_strdel(save);
		return (-1);
	}
	if (t < (ft_strlen(buf) - 1))
	{
		if (!(*save = ft_strsub(buf, t + 1, (ft_strlen(buf) - t - 1))))
			return (-1);
	}
	else
	{
		if (*save)
			ft_strdel(save);
	}
	if (t != (ft_strlen(buf)))
		return (1);
	return (0);
}

static int	ft_boucle(int fd, char **save, char *buf, char **line)
{
	int		ret;

	ret = read(fd, buf, BUFF_SIZE);
	while (ret >= 0)
	{
		if (ret == 0 && (*line) && !(*save))
			return (1);
		if (ret == 0 && !(*save))
			return (0);
		buf[ret] = '\0';
		if (!*line)
		{
			ret = ft_no_line(buf, ft_char_in_str(buf, '\n'), save, line);
			if (ret == 1 || ret == -1)
				return (ret);
		}
		else
		{
			ret = ft_if_line(buf, save, line);
			if (ret == 2 || ret == 0)
				return (ret - 1);
		}
		ret = read(fd, buf, BUFF_SIZE);
	}
	return (0);
}

int			get_next_line(const int fd, char **line)
{
	static char	*save = NULL;
	char		buf[BUFF_SIZE + 1];
	int			a;

	if (read(fd, buf, 0) == -1 || BUFF_SIZE <= 0 || !line || fd < 0)
		return (-1);
	*line = NULL;
	if (save)
	{
		a = ft_if_save(&save, line);
		if (a == 0)
			return (-1);
		if (a == 2)
			return (1);
	}
	a = ft_boucle(fd, &save, buf, line);
	return (a);
}
