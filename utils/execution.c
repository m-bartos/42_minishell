/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:35:56 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/09 15:02:30 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_input_redirection(char *file_name, int *fd_in)
{
	if (access(file_name, F_OK | R_OK) == 0)
		*fd_in = ft_input_file(file_name);
	else
		{
			perror(file_name);
			return (-1);
		}
	return (0);
}

int	ft_output_redirection(char *file_name, int *fd_out)
{
	int	temp_fd;

	temp_fd = ft_output_file(file_name);
	if (temp_fd == -1)
	{
		perror(file_name);
		return (-1);
	}
	else
		*fd_out = temp_fd;
	return (0);
}

int	ft_append_redirection(char *file_name, int *fd_out)
{
	int	temp_fd;

	temp_fd = ft_append_file(file_name);
	if (temp_fd == -1)
	{
		perror(file_name);
		return (-1);
	}
	else
		*fd_out = temp_fd;
	return (0);
}

int	ft_redirects(t_command *cmd, int *fd_in, int *fd_out)
{
	t_token *token;

	token = cmd->first_token;
	while (token)
	{
		if (token->type == R_INFILE)
		{
			if (ft_input_redirection(token->text, fd_in) == -1)
				return (-1);
		}
		else if (token->type == R_OUTFILE)
		{
			if (ft_output_redirection(token->text, fd_out) == -1)
				return (-1);
		}
		else if (token->type == R_OUTFILE_APP)
		{
			if (ft_append_redirection(token->text, fd_out) == -1)
				return (-1);
		}
		token = token->next;
	}
	return (0);
}

void	ft_exec_commands(t_cmd_tab *tab)
{
	t_command	*cmd;
	int	prev_in_fd;
	int	fd_out;
	int	fd[2];

	prev_in_fd = 0;
	fd_out = FD_NULL;
	cmd = tab->first_cmd;
	while (cmd)
	{
		if (ft_redirects(cmd, &prev_in_fd, &fd_out) == -1)
		{
			cmd = cmd->next_cmd;
			// testing
			exit(1);
			continue;
		}
		pipe(fd);
		if (fork() == 0)
		{
			dup2(prev_in_fd, STDIN);
			if ((cmd + 1) != NULL && fd_out == FD_NULL)
				dup2(fd[1], STDOUT);
			else
				dup2(fd_out, STDOUT);
			close(fd[0]);
			execv(cmd->execve_cmd[0], cmd->execve_cmd);
		}
		else
		{
			wait(NULL);
			close(fd[1]);
			prev_in_fd = fd[0];
		}
		cmd = cmd->next_cmd;
	}
}
