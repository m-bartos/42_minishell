/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:29:43 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/18 11:27:24 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_unclosed_quotes(char *line)
{
	if (in_which_quotes(line, ft_strlen(line)) == IN_SINGLE_QUOTES
		|| in_which_quotes(line, ft_strlen(line)) == IN_DOUBLE_QUOTES)
	{
		ft_putstr_fd("Minishell cannot handle open quotes (\", \').\n", STDERR);
		free(line);
		printf(RESET);
		exit(31);
	}
}

void	exit_redirection_error(t_cmd *cmd, char *text)
{
	ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
	ft_putstr_fd(text, STDERR);
	ft_putstr_fd("'\n", STDERR);
	ft_delete_cmd(cmd);
	printf(RESET);
	exit(2);
}

void	check_redirection_errors(t_cmd *cmd)
{
	t_token	*token;

	token = cmd->first_token->next;
	while (token != NULL)
	{
		if (((is_operator_type(token) || is_pipe_type(token))
				&& is_redirection_type(token->prev))
			|| (is_pipe_type(token) && is_pipe_type(token->prev)))
		{
			exit_redirection_error(cmd, token->text);
		}
		token = token->next;
	}
	if (is_redirection_type(cmd->last_token))
		exit_redirection_error(cmd, "newline");
}

int	is_empty_line(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (is_whitespace(line[i]))
			i++;
		else
			break ;
	}
	if (line[i] == '\0')
	{
		free(line);
		return (1);
	}
	else
		return (0);
}
