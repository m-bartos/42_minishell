/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:35:56 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/14 21:20:00 by aldokezer        ###   ########.fr       */
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

void	ft_open_files(t_command *cmd, int *fd_in, int *fd_out)
{
	t_token *token;

	token = cmd->first_token;
	while (token)
	{
		if (token->type == R_INFILE)
			ft_input_redirection(token->text, fd_in);
		else if (token->type == R_OUTFILE)
			ft_output_redirection(token->text, fd_out);
		else if (token->type == R_OUTFILE_APP)
			ft_append_redirection(token->text, fd_out);
		token = token->next;
	}
	return ;
}

void	ft_exec_built_cmds(t_command *cmd)
{
	char	*error;
	char	*cmd_name;

	cmd_name = cmd->execve_cmd[0];
	error = ft_strjoin(cmd_name, ": command not found\n");
	if (ft_strncmp(cmd->execve_cmd[0], "echo", 5) == 0)
	{
		ft_putstr_fd(cmd->execve_cmd[1], STDOUT);
		exit(EXIT_SUCCESS);
	}
	else
	{
		errno = ENOENT;
		if (errno == ENOENT)
		{
			ft_putstr_fd(error, STDERR);
			free(error);
			exit(CMD_NOT_FOUND);
		}
	}

}

void	ft_cmd_not_found(t_command *cmd)
{
	char	*error;
	char	*cmd_name;

	errno = ENOENT;
	cmd_name = cmd->execve_cmd[0];
	error = ft_strjoin(cmd_name, ": command not found\n");
	if (errno == ENOENT)
	{
		ft_putstr_fd(error, STDERR);
		free(error);
		exit(CMD_NOT_FOUND);
	}
	free(error);
	exit(EXIT_SUCCESS);
}

void	ft_execve(t_command *cmd)
{
	char	*error;
	char	*cmd_name;

	cmd_name = cmd->execve_cmd[0];
	error = ft_strjoin(cmd_name, ": command not found\n");
	if (execve(cmd->execve_cmd[0], cmd->execve_cmd, NULL) - 1)
	{
		errno = ENOENT;
		if (errno == ENOENT)
		{
			ft_putstr_fd(error, STDERR);
			free(error);
			exit(CMD_NOT_FOUND);
		}
	}
}

void	ft_exec_commands(t_command *cmd)
{
	t_token	*token;
	token = cmd->first_token;
	while (token)
	{
		if (token->type == CMD)
			ft_execve(cmd);
		else if (token->type == CMD_BUILT)
			ft_echo(cmd);
			//ft_exec_built_cmds(cmd);
		else if (token->type == CMD_ERR)
			ft_cmd_not_found(cmd);
		token = token->next;
	}
}

void	ft_exit_status(int *status)
{
	if (WIFEXITED(*status))
	{
		ft_putnbr_fd(WEXITSTATUS(*status), 1);
		ft_putstr_fd("\n", 1);
	}
}
// exec function
void	ft_init_exec_data(t_exec_data *exec_data)
{
	exec_data->exit_status = 0;
	exec_data->fd_in = STDIN;
	exec_data->fd_out = STDOUT;
}

void	ft_redir_process_io(t_exec_data *data, t_command *cmd)
{
	dup2(data->fd_in, STDIN);
	if (cmd->next_cmd != NULL && (ft_has_out_redir(cmd) == 0))
		dup2(data->pipe_fd[1], STDOUT);
	else
		dup2(data->fd_out, STDOUT);
	close(data->pipe_fd[0]);
}

void	ft_parent_process(t_exec_data *data)
{
	wait(&data->exit_status);
	data->fd_out = 1;
	close(data->pipe_fd[1]);
	data->fd_in = data->pipe_fd[0];
}

void	ft_exec_input(t_cmd_tab *tab)
{
	t_exec_data data;
	t_command	*cmd;

	ft_init_exec_data(&data);
	cmd = tab->first_cmd;
	while (cmd)
	{
		pipe(data.pipe_fd);
		if (fork() == 0)
		{
			ft_open_files(cmd, &data.fd_in, &data.fd_out);
			ft_redir_process_io(&data, cmd);
			ft_exec_commands(cmd);
		}
		else
			ft_parent_process(&data);
		cmd = cmd->next_cmd;
	}
	//ft_exit_status(&data.exit_status);
}
