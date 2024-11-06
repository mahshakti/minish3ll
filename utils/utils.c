/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:45:19 by csubires          #+#    #+#             */
/*   Updated: 2024/11/06 08:52:53 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_empty(char *str)
{
	if (!str)
		return (0);
	while (*str)
		if (!ft_isspace(*str++))
			return (0);
	return (1);
}

int	print_error(int err, t_shell *shell, char *msg)
{
	if (shell)
		shell->error = 1;
	printf("%serr: %s%s", RED, msg, ENDC);
	if (err == -1)
		exit (1);
	return (err);
}

int	file_exists(char *file_name)
{
	struct stat	buffer;

	return (!stat(file_name, &buffer));
}
