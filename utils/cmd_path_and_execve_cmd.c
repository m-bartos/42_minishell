/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path_and_execve_cmd.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 10:26:48 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/10 10:28:27 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_cmd_path(t_token *ptr_token)
{
	char	*path;
	char	*temp_path;
	char	**arr_of_paths;
	int		i;

	temp_path = getenv("PATH");
	arr_of_paths = ft_split(temp_path, ':');
	i = 0;
	while (arr_of_paths[i] != NULL)
	{
		temp_path = ft_strjoin(arr_of_paths[i], "/");
		path = ft_strjoin(temp_path, ptr_token->text);
		free(temp_path);
		if (access(path, X_OK) == 0)
			break ;
		free(path);
		i++;
	}
	if (arr_of_paths[i] == NULL)
		ptr_token->type = CMD_ERR;
	else
	{
		free(ptr_token->text);
		ptr_token->text = path;
	}
	free_array(arr_of_paths);
}

void	make_cmd_paths(t_cmd_tab *cmd_tab)
{
	t_cmd	*ptr_cmd;
	t_token	*ptr_token;

	ptr_cmd = cmd_tab->first_cmd;
	while (ptr_cmd != NULL)
	{
		ptr_token = ptr_cmd->first_token;
		while(ptr_token != NULL)
		{
			if (ptr_token->type == CMD)
			{
				expand_cmd_path(ptr_token);
			}
			ptr_token = ptr_token->next;
		}
		ptr_cmd = ptr_cmd->next;
	}
}

int	count_cmd_length(t_cmd *cmd)
{
	t_token	*ptr_token;
	int		length;

	ptr_token = cmd->first_token;
	length = 0;
	while(ptr_token != NULL)
	{
		if (ptr_token->type == CMD || ptr_token->type == ARG)
			length++;
		else if (ptr_token->type == CMD_ERR)
			return (-1);
		ptr_token = ptr_token->next;
	}
	return (length);
}

void	make_execve_array(t_cmd *cmd)
{
	t_token	*ptr_token;
	char	**arr_of_cmds;
	int		length;
	int		index;

	length = count_cmd_length(cmd);
	if (length == -1)
	{
		cmd->execve_cmd = NULL;
		return ;
	}
	arr_of_cmds = (char **) malloc(sizeof(char *) * (length + 1));
	ptr_token = cmd->first_token;
	index = 0;
	while(index < length)
	{
		if (ptr_token->type == CMD || ptr_token->type == ARG)
			arr_of_cmds[index++] = ptr_token->text;
		ptr_token = ptr_token->next;
	}
	arr_of_cmds[index] = NULL;
	cmd->execve_cmd = arr_of_cmds;
}

void	make_execve_cmds(t_cmd_tab *cmd_tab)
{
	t_cmd	*ptr_cmd;

	ptr_cmd = cmd_tab->first_cmd;
	while (ptr_cmd != NULL)
	{
		make_execve_array(ptr_cmd);
		ptr_cmd = ptr_cmd->next;
	}
}
