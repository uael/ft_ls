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
# include <pwd.h>
# include <stdio.h>
# include <sys/stat.h>
# include <sys/types.h>

typedef	struct	s_ls
{
	uint8_t		opt;
	t_vec		entries;
	t_bool		errs;
}				t_ls;

typedef enum	e_ls_opt
{
	LS_DOTS = 1 << 0,
	LS_LONG = 1 << 1,
	LS_RECU = 1 << 2,
	LS_REVE = 1 << 3,
	LS_ASCT = 1 << 4
}				t_ls_opt;

typedef struct	s_ls_entry
{
	char			*path;
	DIR				*dir;
	struct stat		stat;
}				t_ls_entry;

extern uint8_t	ls_ctor(t_ls *self, int ac, char **av);
extern void		ls_dtor(t_ls *self);
extern void		ls_run(t_ls *self);

extern uint8_t	ls_entry_ctor(t_ls_entry *self, char *path, t_bool root);
extern void		ls_entry_dtor(t_ls_entry *self);
extern void		ls_entry_sort(t_ls_entry *self, size_t n, uint8_t opt);
extern void		ls_entry_print(t_ls_entry *self, size_t n, uint8_t opt);

extern void		ls_print_dtype(mode_t mode);
extern void		ls_print_rights(mode_t mode);
extern void		ls_print_gps(struct stat *s, struct passwd *u, struct group *g);
extern void		ls_print_about(struct stat *stat);
extern void		ls_print_linkto(char *p);

#endif
