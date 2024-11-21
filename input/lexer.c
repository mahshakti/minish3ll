/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:39:58 by csubires          #+#    #+#             */
/*   Updated: 2024/11/21 11:09:13 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	check_token(t_shell *shell, char *input, int *x)
{
	int		start;
	int		end;
	char	quote;
	char	before_quote;

	if (input[*x] && (input[*x] == '\'' || input[*x] == '\"'))
	{
		before_quote = input[*x - 1];
		quote = input[*x];
		start = ++(*x);
		while (input[*x] && input[*x] != quote)
			(*x)++;
		end = *x;
		token_to_dllist(shell, start, end, before_quote);
		(*x)++;
	}
}

static void	split_tokens(t_shell *shell, char *input)
{
	int		x;

	if (!*input)
		return ;
	x = 0;
	while (x < (int)ft_strlen(input))
	{
		check_token(shell, input, &x);
		if (x >= (int)ft_strlen(input))
			break ;
		set_redirect(shell, input, &x);
		if (x >= (int)ft_strlen(input))
			break ;
		if (!ft_isprint(input[x]) || ft_isspace(input[x]))
			x++;
		else
			tokenise_arg(shell, input, &x);
	}
}

static void	manage_quotes(char c, int *flag)
{
	if (!*flag)
	{
		if (c == '\'')
			*flag = 1;
		else if (c == '\"')
			*flag = 2;
	}
	else if (*flag == 1 && c == '\'')
		*flag = 3;
	else if (*flag == 2 && c == '\"')
		*flag = 4;
}

static void	replace_with_envp(t_shell *shell)
{
	int		flag;
	int		x;

	x = 0;
	flag = 0;
	while (shell->input[x])
		manage_quotes(shell->input[x++], &flag);
	x = 0;
	while (shell->input[x])
	{
		if ((flag == 0 || flag == 4) && shell->input[x] == '$')
			expand_envp(shell, &x);
		else
			x++;
	}
}

void	tokens_to_dllist(t_shell *shell)
{
	replace_with_envp(shell);
	split_tokens(shell, (char *)shell->input);

}
