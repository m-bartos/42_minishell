/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 10:00:15 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/21 15:49:28 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @brief Checks if a command has output redirection.
 *
 * Iterates through command tokens to determine if there is any form of
 * output redirection (overwrite or append).
 *
 * @param cmd Pointer to the command structure.
 * @return 1 if output redirection exists, 0 otherwise.
 */

int	ft_has_out_redir(t_cmd *cmd)
{
	t_token	*token;

	token = cmd->first_token;
	while (token)
	{
		if (token->type == R_OUT || token->type == R_OUT_APP)
			return (1);
		token = token->next;
	}
	return (0);
}

/**
 * @brief Sets up input redirection from a file.
 *
 * Opens the specified file for input redirection. If the file cannot be
 * accessed, prints an error and exits the program.
 *
 * @param file_name Name of the file to redirect input from.
 * @param fd_in Pointer to the file descriptor for input redirection.
 */

void	ft_input_redirection(char *file_name, int *fd_in)
{
	if (access(file_name, F_OK | R_OK) == 0)
		*fd_in = ft_input_file(file_name);
	else
	{
		perror(file_name);
		exit(EXIT_FAILURE);
	}
	return ;
}

/**
 * @brief Sets up output redirection to a file.
 *
 * Opens or creates the specified file for output redirection, overwriting
 * its contents. If the operation fails, prints an error and exits.
 *
 * @param file_name Name of the file to redirect output to.
 * @param fd_out Pointer to the file descriptor for output redirection.
 */

void	ft_output_redirection(char *file_name, int *fd_out)
{
	int	temp_fd;

	temp_fd = ft_output_file(file_name);
	if (temp_fd == -1)
	{
		perror(file_name);
		exit(EXIT_FAILURE);
	}
	else
		*fd_out = temp_fd;
	return ;
}

/**
 * @brief Sets up output redirection to append to a file.
 *
 * Opens or creates the specified file for output redirection, appending
 * to its contents. If the operation fails, prints an error and exits.
 *
 * @param file_name Name of the file to append output to.
 * @param fd_out Pointer to the file descriptor for appending output.
 */

void	ft_append_redirection(char *file_name, int *fd_out)
{
	int	temp_fd;

	temp_fd = ft_append_file(file_name);
	if (temp_fd == -1)
	{
		perror(file_name);
		exit(EXIT_FAILURE);
	}
	else
		*fd_out = temp_fd;
	return ;
}

/**
 * @brief Redirects input and output based on command tokens.
 *
 * Processes command tokens to set up input, output, and append redirections
 * for the command execution environment.
 *
 * @param cmd Pointer to the command structure.
 * @param fd_in Pointer to the file descriptor for input redirection.
 * @param fd_out Pointer to the file descriptor for output redirection.
 */

void	ft_redirect_io(t_cmd *cmd, int *fd_in, int *fd_out)
{
	t_token	*token;

	token = cmd->first_token;
	while (token)
	{
		if (token->type == R_INFILE)
		{
			if (*fd_in != STDIN_FILENO)
				close(*fd_in);
			ft_input_redirection(token->text, fd_in);
		}
		else if (token->type == R_OUTFILE)
		{
			if (*fd_out != STDOUT_FILENO)
				close(*fd_out);
			ft_output_redirection(token->text, fd_out);
		}
		else if (token->type == R_OUTFILE_APP)
		{
			if (*fd_out != STDOUT_FILENO)
				close(*fd_out);
			ft_append_redirection(token->text, fd_out);
		}
		token = token->next;
	}
	return ;
}
