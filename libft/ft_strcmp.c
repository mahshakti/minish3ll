/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:17:04 by csubires          #+#    #+#             */
/*   Updated: 2024/10/15 10:11:33 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(char *s1, char *s2)
{
	size_t	x;

	x = 0;
	while (s1[x] && s2[x] && s1[x] == s2[x])
		x++;
	return (s1[x] - s2[x]);
}