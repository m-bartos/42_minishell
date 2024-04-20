/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_process_execution.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 09:19:32 by aldokezer         #+#    #+#             */
/*   Updated: 2024/04/20 10:40:11 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pre_exec_select_built_cmd(t_cmd *cmd, t_env_list *env_list,
	t_exec_data *data)
{
	char		*cmd_name;

	cmd_name = cmd->execve_cmd[0];
	if (ft_strncmp(cmd_name, "echo", ft_strlen(cmd_name) + 1) == 0)
		ft_echo(cmd, env_list, 0);
	else if (ft_strncmp(cmd_name, "pwd", ft_strlen(cmd_name) + 1) == 0)
		ft_pwd(env_list, 0);
	else if (ft_strncmp(cmd_name, "cd", ft_strlen(cmd_name) + 1) == 0)
		ft_cd(cmd, env_list, 0);
	else if (ft_strncmp(cmd_name, "exit", ft_strlen(cmd_name) + 1) == 0)
		ft_exit_minishell(cmd, env_list, data);
	else if (ft_strncmp(cmd_name, "export", ft_strlen(cmd_name) + 1) == 0)
		ft_export(env_list, cmd, 0);
	else if (ft_strncmp(cmd_name, "unset", ft_strlen(cmd_name) + 1) == 0)
		ft_unset(env_list, cmd, 0);
	else if (ft_strncmp(cmd_name, "env", ft_strlen(cmd_name) + 1) == 0)
		ft_env(env_list, 0);
}

int	ft_is_inbuilt(t_cmd *cmd)
{
	t_token	*token;

	token = cmd->first_token;
	while (token)
	{
		if (token->type == CMD_BUILT)
			return (TRUE);
		token = token->next;
	}
	return (FALSE);
}

void	ft_redir_original_io(t_cmd *cmd, int *ori_in, int *ori_out)
{
	dup2(*ori_in, STDIN);
	dup2(*ori_out, STDOUT);
	close(*ori_in);
	close(*ori_out);
}

void	ft_pre_exec_redir_process_io(t_exec_data *data, t_cmd *cmd)
{
	if (ft_has_in_redir(cmd))
	{
		dup2(data->fd_in, STDIN);
		close (data->fd_in);
	}
	if (ft_has_out_redir(cmd))
	{
		dup2(data->fd_out, STDOUT);
		close(data->fd_out);
	}
}

int	ft_pre_exec(t_cmd_tab *tab, t_mini_data *minidata)
{
	t_exec_data	data;
	t_cmd		*cmd;
	t_env_list	*envs;

	ft_init_exec_data(&data, NULL);
	cmd = tab->first_cmd;
	envs = minidata->env_list;
	if (tab->size == 1 && ft_is_inbuilt(cmd))
	{
		ft_redirect_io(cmd, &data.fd_in, &data.fd_out);
		ft_pre_exec_redir_process_io(&data, cmd);
		ft_pre_exec_select_built_cmd(cmd, envs, &data);
		ft_redir_original_io(cmd, &data.ori_fd_in, &data.ori_fd_out);
		return (1);
	}
	close(data.ori_fd_in);
	close(data.ori_fd_out);
	return (0);
}
