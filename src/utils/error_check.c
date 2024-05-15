/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:29:43 by mbartos           #+#    #+#             */
/*   Updated: 2024/05/15 10:07:12 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file error_check.c
 * @brief Functions for error checking and handling in the minishell.
 *
 * This file contains functions responsible for checking and handling various
 * errors that may occur during the execution of the minishell. It includes
 * functions for detecting unclosed quotes, syntax errors related to
 * redirection, and identifying empty lines.
 */

#include "minishell.h"

/**
 * @brief Checks for unclosed quotes in a given line.
 * 
 * This function checks whether the last character in the input line is within
 * an unclosed pair of single or double quotes. If unclosed quotes are detected,
 * an error message is displayed, and the program exits.
 * 
 * @param line The input line to check for unclosed quotes.
 */
int	check_unclosed_quotes(char *line)
{
	if (in_which_quotes(line, ft_strlen(line)) == IN_SINGLE_QUOTES
		|| in_which_quotes(line, ft_strlen(line)) == IN_DOUBLE_QUOTES)
	{
		ft_putstr_fd("Minishell cannot handle open quotes (\", \').\n", STDERR);
		free(line);
		return (1);
	}
	return (0);
}

/**
 * @brief Exits the program with an error message for redirection errors.
 * 
 * This function is called when a syntax error related to redirection is
 * encountered during command parsing. It displays an error message indicating
 * the unexpected token that caused the error and exits the program.
 * 
 * @param cmd The command table being processed.
 * @param text The text of the unexpected token causing the error.
 */
void	redirection_error(t_cmd *cmd, char *text, t_minidata *minidata)
{
	int	status;

	status = 2;
	ft_update_exit_status(&status, minidata);
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(text, STDERR);
	ft_putstr_fd("'\n", STDERR);
	ft_delete_cmd(cmd);
}

/**
 * @brief Checks for syntax errors related to redirection in a command table.
 * 
 * This function examines a command table for syntax errors related to
 * redirection and pipes. If such errors are detected, it handles
 * the error and exit the program.
 * 
 * @param cmd The command table to check for redirection errors.
 */
int	check_redirection_errors(t_cmd *cmd, t_minidata *minidata)
{
	t_token	*token;

	if (is_pipe_type(cmd->first_token))
	{
		redirection_error(cmd, cmd->first_token->text, minidata);
		return (-1);
	}
	token = cmd->first_token->next;
	while (token != NULL)
	{
		if (((is_operator_type(token) || is_pipe_type(token))
				&& is_redirection_type(token->prev))
			|| (is_pipe_type(token) && is_pipe_type(token->prev)))
		{
			redirection_error(cmd, token->text, minidata);
			return (-1);
		}
		token = token->next;
	}
	if (is_redirection_type(cmd->last_token))
	{
		redirection_error(cmd, "newline", minidata);
		return (-1);
	}
	return (0);
}

/**
 * @brief Checks if a line is empty.
 * 
 * This function checks whether a given line contains only whitespace 
 * characters, indicating an empty line. If the line is empty, it frees
 * the memory allocated for the line and returns 1; otherwise, it returns 0.
 * 
 * @param line The input line to check for emptiness.
 * @return 1 if the line is empty, 0 otherwise.
 */
int	line_error(char *line)
{
	size_t	i;

	if (line == NULL)
		ft_exit_minishell(NULL, NULL, NULL);
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
	{
		if (*line)
			add_history(line);
		return (0);
	}
	return (0);
}
