/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/08 12:02:20 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

inline void	ft_putchar(char c)
{
	ft_putchar_fd(c, 1);
}
