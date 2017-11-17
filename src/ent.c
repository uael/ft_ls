/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ent.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 18:50:52 by null             ###   ########.fr       */
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
	ft_vec_ctor(&self->childs, sizeof(t_ls_ent));
	return (0);
}

inline void		ls_ent_dtor(t_ls_ent *self)
{
	ft_vec_dtor(&self->childs, (void (*)(void *))ls_ent_dtor);
	if (S_ISDIR(self->stat.st_mode) && self->u.dir)
	{
		closedir(self->u.dir);
		self->u.dir = NULL;
	}
}

uint8_t			ls_write_reg(t_ls_ctx *ctx, t_ls_ent *self)
{
	char			*bn;

	(void)ctx;
	if ((bn = ft_strrchr(self->path, '/')))
		++bn;
	else
		bn = (char *)self->path;
	(void)(ft_puts(1, bn) + ft_puts(1, "  "));
	return (0);
}

uint8_t			ls_write_dir(t_ls_ctx *ctx, t_ls_ent *self)
{
	t_ls_ent		ent;
	struct dirent	*de;
	char			buf[256];
	char			*bn;

	(void)ctx;
	if ((bn = ft_strrchr(self->path, '/')))
		++bn;
	else
		bn = (char *)self->path;
	(void)(ft_puts(1, bn) + ft_putl(1, ":"));
	while ((de = readdir(self->u.dir)))
	{
		if (ft_strcmp(de->d_name, ".") == 0)
			continue ;
		if (ft_strcmp(de->d_name, "..") == 0)
			continue ;
		ft_strcpy(buf, self->path);
		ft_strcat(buf, "/");
		ft_strcat(buf, de->d_name);
		if (ls_ent_ctor(&ent, buf))
			continue ;
		ls_write_reg(ctx, &ent);
		if ((ctx->opts & FT_LS_RECU) && S_ISDIR(ent.stat.st_mode))
			ft_vec_pushc(&self->childs, &ent);
		else
			ls_ent_dtor(&ent);
	}
	return (0);
}
