/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/18 19:43:27 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

#define PUTL ft_putc(1, '\n')
#define LS_ERR(arg, err_no) (t_ls_err){arg, err_no}

static void		ls_ctor_init(t_ls *ls, char **a, t_bool *m, int *i)
{
	ft_memset(ls, 0, sizeof(t_ls));
	ls->p = ft_basename(a[0]);
	ft_vec_ctor(&ls->ent, sizeof(t_ls_entry));
	ft_vec_ctor(&ls->errs, sizeof(t_ls_err));
	*i = 0;
	*m = 0;
}

inline uint8_t	ls_ctor(t_ls *ls, int ac, char **a)
{
	int			i;
	t_ls_entry	e;
	char		c;
	t_bool		m;

	ls_ctor_init(ls, a, &m, &i);
	while (++i < ac)
	{
		c = !m && (char)(ft_strcmp(a[i], "--") == 0);
		m = (t_bool)(m || (*a[i] != '-' || !*(a[i] + 1)) || c);
		if (!*a[i])
			return (ls_err(ls->p, "fts_open", ENOENT));
		if (!c && m && ls_entry_ctor(&e, a[i]))
			ft_vec_pushc(&ls->errs, &LS_ERR(a[i], errno));
		else if (!c && m && !(e.path = ft_strdup(e.path)))
			return (1);
		else if (!c && m && !ft_vec_pushc(&ls->ent, &e))
			return (1);
		else if (!m && *a[i] == '-' && ls_opt_parse(&ls->opt, a[i], &c))
			return (ls_opt_error(ls, c));
	}
	if (!ls->errs.len && !ft_vec_size(&ls->ent) &&
		(ls_entry_ctor(&e, ft_strdup(".")) || !ft_vec_pushc(&ls->ent, &e)))
		return (1);
	return (ls_err_dump(ls));
}

inline void		ls_dtor(t_ls *self)
{
	ft_vec_dtor(&self->ent, (void (*)(void *)) ls_entry_dtor);
	ft_vec_dtor(&self->errs, NULL);
}

static t_bool	ls_childs(t_ls *self, t_vec *v, t_ls_entry *ent, size_t i)
{
	t_ls_entry		e;
	struct dirent	*de;
	size_t			j;

	v->len = 0;
	if (!(ent->dir = opendir(ent->path)))
		return ((t_bool)!ls_err(self->p, ft_basename(ent->path), errno));
	j = 0;
	while ((de = readdir(ent->dir)))
	{
		if (*de->d_name == '.' && !(self->opt & LS_DOTS))
			continue ;
		if (ls_entry_ctor(&e, ft_pathjoin(ent->path, de->d_name)))
			continue ;
		if ((self->opt & LS_RECU) && !ft_isdots(de->d_name) &&
			S_ISDIR(e.stat.st_mode) && ++j)
			ft_vec_putc(&self->ent, i, &e);
		ft_vec_pushc(v, &e);
	}
	(void)(closedir(ent->dir) & (size_t)(ent->dir = NULL));
	if (j)
		ls_entry_sort((t_ls_entry *)self->ent.buf + i, j, self->opt, 1);
	return ((t_bool)(v->len > 0));
}

inline void		ls_run(t_ls *s)
{
	size_t		i[2];
	t_ls_entry	*e;
	t_vec		v;
	t_bool		f;

	ft_vec_ctor(&v, sizeof(t_ls_entry));
	i[0] = ls_entry_sort(s->ent.buf, s->ent.len, s->opt, 1);
	f = 0;
	while (i[0] < s->ent.len && (e = (t_ls_entry *)s->ent.buf + i[0]++))
		if (!LS_ISDIR(e))
			ls_entry_dump(e, f = 1, s->opt, 0);
		else if (f ? PUTL & ((f = 0) + 1) : 1)
		{
			if (s->errs.len || s->ent.len > 1)
				(void)(ft_puts(1, e->path) & ft_putl(1, ":"));
			if (!ls_childs(s, &v, e, i[0]) &&
				(i[0] < s->ent.len ? PUTL : 1))
				continue ;
			ls_entry_dump(v.buf, v.len, s->opt, 1);
			i[1] = (i[0] < s->ent.len ? (size_t)(PUTL & 0) : 0);
			while (i[1] < v.len && (e = (t_ls_entry *)v.buf + i[1]++))
				if (!(s->opt & LS_RECU) || !S_ISDIR(e->stat.st_mode))
					ls_entry_dtor(e);
		}
	ft_vec_dtor(&v, NULL);
}
