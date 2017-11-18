/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdots.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/18 09:55:12 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/fs.h"

inline t_bool	ft_isdots(char const *path)
{
	return ((t_bool)(*path == '.'));
}