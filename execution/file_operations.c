/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 22:05:51 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/17 10:22:52 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @brief Opens a file for reading.
 *
 * Attempts to open the specified file in read-only mode. If the operation
 * fails, -1 is returned.
 *
 * @param file_name Name of the file to open.
 * @return File descriptor of the opened file, or -1 on failure.
 */

int	ft_input_file(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (-1);
	else
		return (fd);
}

/**
 * @brief Opens or creates a file for writing, overwriting existing content.
 *
 * Opens the specified file in write-only mode, creating it if it does not
 * exist and truncating it to zero length if it does. Sets the file's
 * permissions to user read/write/execute, group read, and others read.
 *
 * @param file_name Name of the file to open or create.
 * @return File descriptor of the opened or created file, or -1 on failure.
 */

int	ft_output_file(char *file_name)
{
	int	fd;

	fd = open(file_name, O_WRONLY | O_CREAT
			| O_TRUNC, S_IRWXU | S_IRGRP | S_IROTH);
	if (fd == -1)
		return (-1);
	else
		return (fd);
}

/**
 * @brief Opens or creates a file for appending data.
 *
 * Opens the specified file in write-only append mode, creating it if it does
 * not exist. Data written to the file is appended to its end. Sets the file's
 * permissions to user read/write/execute, group read, and others read.
 *
 * @param file_name Name of the file to open or create.
 * @return File descriptor of the opened or created file, or -1 on failure.
 */

int	ft_append_file(char *file_name)
{
	int	fd;

	fd = open(file_name, O_APPEND | O_CREAT
			| O_WRONLY, S_IRWXU | S_IRGRP | S_IROTH);
	if (fd == -1)
		return (-1);
	else
		return (fd);
}
