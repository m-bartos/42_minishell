/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd_paths.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 09:12:15 by mbartos           #+#    #+#             */
/*   Updated: 2024/05/15 13:59:23 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file make_cmd_paths.c
 * @brief Functions for making command paths in a command table.
 *
 * This file contains the implementation of functions used to make command paths
 * for each CMD token in a given command table.
 */

#include "minishell.h"

/**
 * @brief Retrieves the path of a command token.
 *
 * This function retrieves the path of a command token by searching through 
 * the directories specified in the PATH environmental variable. If the command
 * is found in one of the directories and is executable, its full path 
 * is returned. If not found or not executable, NULL is returned.
 *
 * @param token The command token for which to retrieve the path.
 * @return The full path of the command if found and executable, otherwise NULL.
 */
char	*get_cmd_path(t_token *token, t_env_list *env_list)
{
	char	*str_path;
	char	*temp_path;
	char	**arr_of_paths;
	int		i;

	temp_path = ft_get_env(env_list, "PATH");
	if (temp_path == NULL)
		return (NULL);
	arr_of_paths = ft_split_e(temp_path, ':');
	free(temp_path);
	i = 0;
	while (arr_of_paths[i] != NULL)
	{
		temp_path = ft_strjoin_e(arr_of_paths[i], "/");
		str_path = ft_strjoin_e(temp_path, token->text);
		free(temp_path);
		if (access(str_path, X_OK) == 0)
			break ;
		free(str_path);
		str_path = NULL;
		i++;
	}
	ft_free_array(arr_of_paths);
	return (str_path);
}

/**
 * @brief Expands the path of a command token.
 *
 * This function checks if the provided path in the command token is executable. 
 * If the path is a regular file and has executable permissions, it updates
 * the token's type to CMD. If the path is not executable or does not exist,
 * it attempts to retrieve the full path using the `get_cmd_path` function
 * from the specified environment list. If successful, the token's text is
 * updated with the full path, and its type is set to CMD. If the path is 
 * invalid or cannot be resolved, the token's type is set to CMD_ERR.
 *
 * @param token A pointer to the command token to expand the path for.
 * @param env_list A pointer to the environment list.
 */
void	expand_token_cmd_path(t_token *token, t_env_list *env_list)
{
	char		*cmd_path;
	struct stat	path_stat;

	if (token->text == NULL || token->text[0] == '\0')
		return ;
	if (stat(token->text, &path_stat) == 0)
	{
		if (S_ISREG(path_stat.st_mode) == 0)
		{
			token->type = CMD_ERR;
			if (token->text[0] == '.' || token->text[0] == '/')
				return ;
		}
		else if (access(token->text, F_OK | X_OK) == 0)
			return ;
	}
	cmd_path = get_cmd_path(token, env_list);
	if (cmd_path == NULL)
		token->type = CMD_ERR;
	else
	{
		token->type = CMD;
		free(token->text);
		token->text = cmd_path;
	}
}

/**
 * @brief Makes command paths for each CMD token in the given command table.
 *
 * This function traverses through the command table and expands the paths
 * of CMD tokens by calling the `expand_token_cmd_path` function for each 
 * CMD token encountered.
 *
 * @param cmd_tab The command table to make command paths for.
 */
void	make_cmd_paths(t_cmd_tab *cmd_tab, t_minidata *minidata)
{
	t_env_list	*env_list;
	t_cmd		*cmd;
	t_token		*token;

	env_list = minidata->env_list;
	cmd = cmd_tab->first_cmd;
	while (cmd != NULL)
	{
		token = cmd->first_token;
		while (token != NULL)
		{
			if (token->type == CMD)
			{
				expand_token_cmd_path(token, env_list);
			}
			token = token->next;
		}
		cmd = cmd->next;
	}
}
