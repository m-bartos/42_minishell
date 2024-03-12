/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:35:56 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/12 15:37:23 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_has_out_redir(t_command *cmd)
{
	t_token *token;

	token = cmd->first_token;
	while (token)
	{
		//ft_printf("Token: %d\n", token->type);
		if (token->type == R_OUT || token->type == R_OUT_APP)
			return (1);
		token = token->next;
	}
	return (0);
}

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

int	ft_open_files(t_command *cmd, int *fd_in, int *fd_out)
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

void	ft_exec_built_cmds(t_command *cmd, int *fd_out)
{
	// echo test
	if (ft_strncmp(cmd->execve_cmd[0], "echo", 5) == 0)
	{
		ft_putstr_fd(cmd->execve_cmd[1], STDOUT);
		close (*fd_out);
		exit(0);
	}

}

void	ft_cmd_not_found(t_command *cmd)
{
	char	*error;
	char	*cmd_name;

	errno = ENOENT;
	cmd_name = cmd->execve_cmd[0];
	error = ft_strjoin(cmd_name, ": command not found");
	if (errno == ENOENT)
	{
		ft_putstr_fd(error, STDERR);
		free(error);
		exit(EXIT_FAILURE);
	}
	free(error);
	exit(EXIT_SUCCESS);
}

void	ft_exec_commands(t_command *cmd, int *fd_out)
{
	t_token	*token;
	token = cmd->first_token;
	while (token)
	{
		if (token->type == CMD)
			execv(cmd->execve_cmd[0], cmd->execve_cmd);
		else if (token->type == CMD_BUILT)
			ft_exec_built_cmds(cmd, fd_out);
		else if (token->type == CMD_ERR)
			ft_cmd_not_found(cmd);
		token = token->next;
	}
}


// exec function

void	ft_exec_input(t_cmd_tab *tab)
{
	int		exit_status;
	t_command	*cmd;
	int	prev_in_fd;
	int	fd_out;
	int	fd[2];

	prev_in_fd = 0;
	fd_out = STDOUT;
	cmd = tab->first_cmd;
	while (cmd)
	{
		pipe(fd);
		if (fork() == 0)
		{
			if (ft_open_files(cmd, &prev_in_fd, &fd_out) == -1)
				exit(EXIT_FAILURE);

			dup2(prev_in_fd, STDIN);
			// if current command is not last and current command does not have redirections = write to fd[1]
			if (cmd->next_cmd != NULL && (ft_has_out_redir(cmd) == 0))
				dup2(fd[1], STDOUT);
			else
				dup2(fd_out, STDOUT);
			close(fd[0]);
			ft_exec_commands(cmd, &fd_out);
		}
		else
		{
			wait(&exit_status);
			fd_out = 1;
			close(fd[1]);
			prev_in_fd = fd[0];
		}
		cmd = cmd->next_cmd;
		// ft_putstr_fd("\n", 1);
		// ft_putnbr_fd(exit_status, 1);
	}
}
