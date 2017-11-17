/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ent.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 13:34:59 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls/ent.h"
#include "ls/ctx.h"

inline uint8_t	ls_ent_ctor(t_ls_ent *self, char *path)
{
	FT_INIT(self, t_ls_ent);
	if (lstat(path, &self->stat) < 0)
		return (1);
	else if (S_ISDIR(self->stat.st_mode) && !(self->u.dir = opendir(path)))
		return (1);
	self->path = path;
	return (0);
}

inline void		ls_ent_dtor(t_ls_ent *self)
{
	if (S_ISDIR(self->stat.st_mode) && self->u.dir)
	{
		closedir(self->u.dir);
		self->u.dir = NULL;
	}
}

inline uint8_t	ls_ent_write(t_ls_ent *self, uint8_t opt)
{
	t_ls_ent		ent;
	struct dirent	*di;
	char			buf[256];

	ft_puts(1, self->path);
	ft_puts(1, "  ");
	if (S_ISDIR(self->stat.st_mode))
		while ((di = readdir(self->u.dir)))
		{
			if (ft_strcmp(di->d_name, ".") == 0)
				continue ;
			if (ft_strcmp(di->d_name, "..") == 0)
				continue ;
			ft_strcpy(buf, self->path);
			ft_strcat(buf, "/");
			ft_strcat(buf, di->d_name);
			if (ls_ent_ctor(&ent, buf))
				continue ;
			ls_ent_write(&ent, opt);
		}
	return (0);
}
