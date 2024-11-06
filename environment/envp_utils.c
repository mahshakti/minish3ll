/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:30:16 by csubires          #+#    #+#             */
/*   Updated: 2024/10/25 12:03:19 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	indx_delimiter(char *envp, char separator)
{
	int		x;

	x = 0;
	while (envp[x])
	{
		if (envp[x] == separator)
			return (x);
		x++;
	}
	return (0);
}

char	**split_env_item(char *envp, char separator)
{
	char	**one_var;
	char	*tmp_envp;
	int		str_len;
	int		indx;

	one_var = 0;
	tmp_envp = (char *)envp;
	indx = indx_delimiter(tmp_envp, separator);
	if (!tmp_envp || !indx || tmp_envp[0] == separator)
		return (0);
	one_var = (char **)ft_calloc(2, sizeof(char *));
	if (!one_var)
		return (0);
	one_var[0] = ft_substr(tmp_envp, 0, indx);
	tmp_envp += ++indx;
	str_len = ft_strlen(tmp_envp);
	one_var[1] = ft_substr(tmp_envp, 0, str_len);
	return (one_var);
}

void	free_env_entry(void *entry)
{
	t_envp	*env_item;

	env_item = (t_envp *)entry;
	free(env_item->key);
	env_item->key = 0;
	free(env_item->value);
	env_item->value = 0;
	free(entry);
	entry = 0;
}
