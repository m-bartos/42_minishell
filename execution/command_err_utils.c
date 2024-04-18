/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_err_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:16:35 by aldokezer         #+#    #+#             */
/*   Updated: 2024/04/18 10:03:28 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_path_valid(const char *path)
{
	struct  stat	statbuf;

	if (stat(path, &statbuf) == 0)
		return 1;
	return 0;
}

int	ft_is_path(char *token)
{
	if (token != NULL)
	{
		if (token[0] == '.' || token[0] == '/')
			return (1);
		else
			return (0);
	}
	else
		return (0);
}

void	ft_error(char *cmd_name, char *err_text, int err_code)
{
	char	*error;

	error = ft_strjoin(cmd_name, err_text);
	ft_putstr_fd(error, STDERR);
	free(error);
	exit_minishell(NULL, err_code);
}
