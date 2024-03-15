/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory_ops.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:01:44 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/15 20:44:04 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Finds the first argument and uses it as a path for CD
char	*ft_find_arg(t_command *cmd)
{
	t_token	*token;

	token = cmd->first_token;
	while (token)
	{
		if (token->type == ARG)
			return (token->text);
		token = token->next;
	}
	return (NULL);
}

// For pipline commands it has to behave like a separate process so exit() is desirable
void	ft_cd(t_command *cmd)
{
	char	*error;
	char	*path;

	path = ft_find_arg(cmd);
	if (chdir(path) != 0)
	{
		if (errno == ENOENT)
		{
			error = ft_strjoin("cd: no such file or directory: ", path);
			ft_putstr_fd(error, STDERR);
			ft_putstr_fd("\n", STDERR);
			free(error);
			exit(1);
		}
		else
		{
			perror("cd");
			exit(1);
		}
	}
	ft_pwd_no_exit();
	exit (0);
}

// For pipline commands it has to behave like a separate process so exit() is desirable
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
		ft_putstr_fd("\n", STDOUT);
		free(cwd);
		exit(0);
	}
}

// For the main function - the main should not have the cd
// function with exit as it will terminate the process.
// In the main function this function should return as a standard function
void	ft_cd_no_exit(t_command *cmd)
{
	char	*error;
	char	*path;

	path = ft_find_arg(cmd);

	if (chdir(path))
	{
		if (errno == ENOENT)
		{
			error = ft_strjoin("cd: no such file or directory: ", path);
			ft_putstr_fd(error, STDERR);
			ft_putstr_fd("\n", STDERR);
			free(error);
		}
		else
			perror("cd");
	}
}

// For the main function - the main should not have the pwd
// function with exit as it will terminate the main process.
// In the main function this function should return as a standard function
void	ft_pwd_no_exit(void)
{
	char *cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd: ");
		free(cwd);
	}
	else
	{
		ft_putstr_fd(cwd, STDOUT);
		ft_putstr_fd("\n", STDOUT);
		free(cwd);
	}
}
