/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 22:05:51 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/09 00:46:56 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_input_file(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (-1);
	else
		return (fd);
}

int	ft_output_file(char *file_name)
{
	int	fd;

	fd = open(file_name, O_WRONLY | O_CREAT, S_IRWXU | S_IRGRP | S_IROTH);
	if (fd == -1)
		return (-1);
	else
		return (fd);
}

int	ft_append_file(char *file_name)
{
	int	fd;

	fd = open(file_name, O_APPEND | O_CREAT | O_WRONLY, S_IRWXU | S_IRGRP | S_IROTH);
	if (fd == -1)
		return (-1);
	else
		return (fd);
}
