/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 12:48:38 by cde-moul          #+#    #+#             */
/*   Updated: 2019/06/06 15:22:48 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../libft/libftprintf.h"
# include <sys/types.h>
# include <sys/xattr.h>
# include <sys/stat.h>
# include <sys/acl.h>
# include <dirent.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <errno.h>

# define OPTIONS "alrRtgufSod1"

# define SMALL_A (1 << 0)
# define SMALL_L (1 << 1)
# define SMALL_R (1 << 2)
# define BIG_R (1 << 3)
# define SMALL_T (1 << 4)
# define SMALL_G (1 << 5)
# define SMALL_U (1 << 6)
# define SMALL_F (1 << 7)
# define BIG_S (1 << 8)
# define SMALL_O (1 << 9)
# define SMALL_D (1 << 10)

typedef struct		s_rep
{
	struct s_rep	*master;
	struct s_rep	*prev;
	struct s_rep	*next;
	char			*name;
}					t_rep;

typedef struct		s_infos
{
	int				flags;
	int				nbr_error;
	char			**path;
	char			**error;
}					t_infos;

char				**ls_sort_path2(t_infos *flags, t_rep *rep);
char				ls_attributes(char *path);
void				ls_sort_path_norm(t_infos *flags, t_rep *rep, char **path);
void				ls_free_flags(t_infos *flags, int i);
void				ls_printf_error(t_infos *flags);
void				ls_sort_path(t_infos *flags, char **path);
void				ls_rev_path(char **file);
void				ls_rev_path2_bis(char **file, char **path, int a, int i);
void				ls_treat(t_infos *flags);
void				ls_longtreat(int flags, char **file);
void				ls_longtreat_bis(char **lon, char *file, int flags);
void				ls_longtreat2(t_infos *flags, char **path);
void				ls_open(t_infos *flags, int i);
void				ls_algo(t_infos *flags, t_rep *rep, int i);
void				ls_hidden_files(t_infos *flags);
void				ls_longdetails(char **lon, int flags, struct stat **sts,
					char *path);
void				ls_longdetails2(char **lon, struct stat *sts, int *count,
					int flags);
void				ls_longsize2(char **lon, int *count, int cout,
					long long cp);
void				ls_longdate(char **lon, int flags, struct stat *sts,
					int *count);
void				ls_longlink(char **lon, struct stat *sts);
void				ls_longsize(char **lon, int *count, struct stat *sts);
void				ls_longtype(struct stat *sts, char **lon);
void				ls_longrights(struct stat *sts, char **lon);
void				ls_longrights3(struct stat *sts, char **lon);
void				ls_job_part_2(t_infos *flags, t_rep *rep);
void				ls_in_algo(t_rep **rep, t_rep **tmp);
void				ls_free_line(t_rep *rep);
void				ls_longdev(char **lon, int *count, struct stat *sts);
void				ls_manage_error_3(t_infos *flags, int a);
void				ls_longgroupename(char **lon, int *count,
					struct stat *sts);
void				ls_longusername(char **lon, int *count, struct stat *sts);
void				ls_longtreat_dev(t_infos *flags, char **path);
void				ls_recur3_ter(char **path);
void				ls_longtreat_norm(char **lon, t_infos *flags, char **path);
void				ls_print_permission(char *name);
void				ls_put_and_free(t_rep **rep, t_infos *flags, char *file,
					int u);
void				ls_longtreat2_bis(struct stat **sts, char **lon,
					int *total);
int					ls_freelonsts(struct stat **sts, char **lon, int i);
int					ls_init_flags(t_infos *flags, int i);
int					ls_recur(t_infos *flags, t_rep **rep, t_rep *wlk);
int					ls_islink(char *path);
int					ls_get_arg(t_infos *flags, int argv, char **argc);
int					ls_sort_alpha(char *curse, char *compare);
int					ls_sort_mod(char *curse, char *compare);
int					ls_check_master_dev(t_rep **rep);
int					ls_sort_access(char *curse, char *compare);
int					ls_do_your_job2(t_infos *flags, t_rep **rep,
					int a, char *file);
int					ls_test(char *path, t_infos *flags);
int					ls_longtreat2_norm(char *path, struct stat **sts,
					char **lon, int *total);
int					ls_recur3_bis(char **path, int *i);

#endif
