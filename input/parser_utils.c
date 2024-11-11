/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:17:39 by csubires          #+#    #+#             */
/*   Updated: 2024/11/11 10:41:30 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*read_heredoc(char *delimiter)
{
	char	*join_str;
	char	*read_str;

	join_str = 0;
	while (1)
	{
		read_str = readline(" heredoc> ");
		if (!read_str)
			break ;
		if (!ft_strcmp(read_str, delimiter))
		{
			free(read_str);
			break ;
		}
		if (!join_str)
			join_str = ft_strdup(read_str);
		else
			join_str = ft_strconcat(3, join_str, "\n", read_str);
		free(read_str);
	}
	join_str = ft_strconcat(2, join_str, "\n");
	return (join_str);
}

static void	manage_input(t_exec *exec_cmd, t_dllist **token_ptr)
{
	if ((*token_ptr)->next)
	{
		if (!ft_strcmp((char *)(*token_ptr)->data, "<"))
		{
			if (exec_cmd->heredoc_delimiter)
				dlist_free((void **)&(exec_cmd->heredoc_delimiter));
			*token_ptr = (*token_ptr)->next;
			exec_cmd->input_file = ft_strdup((char *)(*token_ptr)->data);
			if (!file_exists(exec_cmd->input_file))
				ft_fdprint(exec_cmd->out_fd, "%s%s: %s%s\n" \
				, RED, exec_cmd->input_file, ERR_PATH, ENDC);
		}
		else if (!ft_strcmp((char *)(*token_ptr)->data, "<<"))
		{
			if (exec_cmd->input_file)
				dlist_free((void **)&(exec_cmd->input_file));
			*token_ptr = (*token_ptr)->next;
			exec_cmd->heredoc_delimiter = ft_strdup((char *)(*token_ptr)->data);
			exec_cmd->heredoc_data = read_heredoc(exec_cmd->heredoc_delimiter);
		}
	}
}

static void	manage_output(t_exec *exec_cmd, t_dllist *token_ptr[])
{
	if ((*token_ptr)->next)
	{
		if (!ft_strcmp((char *)(*token_ptr)->data, ">") || \
		!ft_strcmp((char *)(*token_ptr)->data, ">>"))
		{
			if (exec_cmd->output_file)
				dlist_free((void **)&(exec_cmd->output_file));
			if (!ft_strcmp((char *)(*token_ptr)->data, ">>"))
				exec_cmd->append_to_fd = 1;
			*token_ptr = (*token_ptr)->next;
			exec_cmd->output_file = ft_strdup((char *)(*token_ptr)->data);
		}
	}
}

void	manage_redirection(t_exec *exec_cmd, t_dllist *token_ptr[])
{
	char	*token_data;

	if (!(*token_ptr)->next)
		return ;
	token_data = (char *)(*token_ptr)->data;
	if (!ft_strcmp((char *)(*token_ptr)->data, "<") || \
		!ft_strcmp(token_data, "<<"))
		manage_input(exec_cmd, token_ptr);
	else if (!ft_strcmp((char *)(*token_ptr)->data, ">") || \
		!ft_strcmp((char *)(*token_ptr)->data, ">>"))
		manage_output(exec_cmd, token_ptr);
}
