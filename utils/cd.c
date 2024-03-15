/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:01:44 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/15 17:50:47 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cd(const char *path)
{
	if (chdir(path))
	{
		perror("cd: ");
		exit(1);
	}
}

void	ft_pwd(void)
{
	char *cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd: ");
		free(cwd);
		exit(1);
	}
	else
	{
		ft_putstr_fd(cwd, STDOUT);
		free(cwd);
		exit(0);
	}
}
