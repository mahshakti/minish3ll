/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:19:52 by csubires          #+#    #+#             */
/*   Updated: 2024/11/15 12:53:38 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_input(t_shell *shell)
{
	if (shell->token_list)
		free_tokens(shell);
	if (shell->exec_list)
		dlist_clear(&(shell->exec_list), free_execs);
	if (shell->input)
	{
		free(shell->input);
		shell->input = 0;
	}
	if (shell->prompt)
	{
		free(shell->prompt);
		shell->prompt = 0;
	}
}

static t_shell	*init_shell(char *envp[])
{
	t_shell	*shell;

	shell = ft_calloc(1, sizeof(t_shell));
	if (!shell)
		print_error(-1, shell, ERR_MALLOC);
	shell->error = 0;
	envp_to_dllist(shell, envp);
	return (shell);
}

static char	*get_input(t_shell *shell)
{

	char	*path;

	path = ft_strltrim(get_env_value(shell->env_list, "PWD"), \
	get_env_value(shell->env_list, "HOME"));
	if (!path)
		path = ft_strdup(get_env_value(shell->env_list, "PWD"));
	else
		path = ft_strjoin("~", path);
	shell->prompt = ft_strconcat(7, YELLOW, "@minishell:", GREEN, \
	path, YELLOW, " \n $ ", ENDC);
	free(path);
	// shell->prompt = ft_strjoin("@minishell:", get_env_value(shell->env_list, "PWD"));
	shell->input = readline(shell->prompt);
	if (!shell->input)
	{
		printf("%s%s%s\n", BLUE, MSG_BYE, ENDC);
		return (0);
	}
	if (*(shell->input))
		add_history(shell->input);
	return (shell->input);
}

static void	fill_lists(t_shell *shell)
{
	tokens_to_dllist(shell);
	//if (1)
	//	print_token_list(shell);
	exec_cmd_to_dllist(shell);
	manage_fds(shell);
	//if (1)
	//	print_exec_list(shell);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_shell	*shell;

	(void)argv;
	if (argc != 1)
		print_error(-1, (void *)0, ERR_ARG);
	init_signals();
	shell = init_shell(envp);

	/* BYPASS



	if (argc > 2 && !ft_strcmp(argv[1], "-c"))
	{
		shell->input = ft_strdup(argv[2]);
		fill_lists(shell);
		execute_execs(shell);
		free_input(shell);
		restore_signals();
		free_all(shell);
		return (0);
	}

	 BYPASS */

	while (1 && !shell->error)
	{
		if (get_input(shell) && !is_empty(shell->input))
		{
			fill_lists(shell);
			execute_execs(shell);
			free_input(shell);
		}
	}
	restore_signals();
	free_all(shell);
	return (0);
}
