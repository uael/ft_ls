/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/18 19:43:27 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
# define LS_H

# include <dirent.h>
# include <errno.h>
# include <grp.h>
# include <libft.h>
# include <limits.h>
# include <pwd.h>
# include <stdio.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/time.h>

typedef	struct	s_ls
{
	char const	*p;
	uint8_t		opt;
	t_vec		ent;
	t_vec		errs;
}				t_ls;

typedef enum	e_ls_opt
{
	LS_DOTS = 1 << 0,
	LS_LONG = 1 << 1,
	LS_RECU = 1 << 2,
	LS_REVE = 1 << 3,
	LS_ASCT = 1 << 4,
	LS_UNIT = 1 << 5,
	LS_LINE = 1 << 6,
}				t_ls_opt;

typedef struct	s_ls_err
{
	char	*arg;
	int		err_no;
}				t_ls_err;

typedef struct	s_ls_entry
{
	char			*path;
	DIR				*dir;
	struct stat		stat;
	struct passwd	*usr;
	struct group	*grp;
	char			strsz[20];
	char			ln[PATH_MAX];
	ssize_t			lnl;
	struct stat		*lns;
}				t_ls_entry;

# define LS_ISLNDIR(e) ((e)->lns && S_ISDIR((e)->lns->st_mode))
# define LS_ISDIR(e) (S_ISDIR((e)->stat.st_mode) || LS_ISLNDIR(e))

extern uint8_t	ls_ctor(t_ls *ls, int ac, char **a);
extern void		ls_dtor(t_ls *self);
extern uint8_t	ls_err(char const *prg, char const *arg, int err_no);
extern uint8_t	ls_err_dump(t_ls *ls);

extern float	ls_fmt_size(off_t sz, char *unit);
extern uint8_t	ls_opt_error(t_ls *ls, char c);
extern uint8_t	ls_opt_parse(uint8_t *opt, char *s, char *c);

extern uint8_t	ls_entry_ctor(t_ls_entry *self, char *path);
extern void		ls_entry_dtor(t_ls_entry *self);
extern uint8_t	ls_entry_sort(t_ls_entry *ent, size_t n, uint8_t opt, t_bool r);
extern void		ls_entry_dump(t_ls_entry *ent, size_t n, uint8_t opt, t_bool s);

extern void		ls_print_dtype(mode_t mode);
extern void		ls_print_rights(mode_t mode);
extern void		ls_print_gps(t_ls_entry *self, uint8_t pad[2]);
extern void		ls_print_about(struct stat *stat);
extern void		ls_run(t_ls *s);

#endif
