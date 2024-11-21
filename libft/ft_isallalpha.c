/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:37:51 by csubires          #+#    #+#             */
/*   Updated: 2024/04/16 15:48:59 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isallalpha(char *str)
{
	while (*str)
	{
		if ((*str < 'a' || *str > 'z') && (*str < 'A' || *str > 'Z' ))
			return (0);
		str++;
	}
	return (1);
}