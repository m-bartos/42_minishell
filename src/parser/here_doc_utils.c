/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 09:13:49 by mbartos           #+#    #+#             */
/*   Updated: 2024/05/15 09:15:48 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Unlinks here-doc files in the command table.
 *
 * This function traverses the command table and unlinks any temporary files
 * created for here-documents used as input redirection. It identifies here-doc
 * files by their filenames, which start with the prefix specified by
 * the HEREDOC_FILE macro.
 *
 * @param cmd_tab The command table possibly referencing here-doc files.
 */
void	unlink_heredoc_files(t_cmd_tab *cmd_tab)
{
	t_cmd	*cmd;
	t_token	*token;
	char	*text;

	cmd = cmd_tab->first_cmd;
	while (cmd)
	{
		token = cmd->first_token;
		while (token)
		{
			text = token->text;
			if (token->type == R_INFILE
				&& ft_strncmp(text, HEREDOC_FILE, ft_strlen(HEREDOC_FILE)) == 0)
				unlink(text);
			token = token->next;
		}
		cmd = cmd->next;
	}
}

/**
 * @brief Expands environment variables within a line of here-doc input.
 *
 * This function expands environment variables within a line of here-doc input
 * by replacing occurrences of '$' followed by variable names with their 
 * corresponding values.
 *
 * @param str The line of here-doc input to expand environment variables in.
 * @param env_list: A linked list containing environment variables.
 * @return The line with expanded environment variables.
 */
char	*expand_all_vars_in_heredoc_line(char *str, t_env_list *env_list)
{
	char	*str_old;
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			str_old = str;
			str = expand_one_var_in_str(str, &i, env_list);
			free(str_old);
		}
		else
			i++;
	}
	return (str);
}

/**
 * @brief Creates and opens a temporary file for a here-doc.
 *
 * This function generates a filename for a here-doc file based on the provided
 * index, creates the file, and returns its filename. The filename is created
 * using a prefix specified by the HEREDOC_FILE macro followed by the index
 * converted to a string.
 *
 * @param index The index used to create a unique filename for here-doc file.
 * @return The filename of the created here-doc file.
 */
char	*create_heredoc_filename(int i)
{
	char	*filename;
	char	*str_index;

	str_index = ft_itoa_e(i);
	filename = ft_strjoin_e(HEREDOC_FILE, str_index);
	free(str_index);
	return (filename);
}

/**
 * @brief Updates the exit status of the shell based on heredoc termination.
 *
 * This function checks if a SIGINT signal was received during heredoc process
 * and updates the shell's exit status accordingly. It restores the default
 * signal handler and returns a 1 if the SIGINT signal was received.
 *
 * @param minidata: A structure containing shell-related data.
 * @return 1 if SIGINT was received, 0 otherwise.
 */
int	set_heredoc_exit_status(t_minidata *minidata)
{
	int	status;

	status = 0;
	if (g_sigint_received == 130)
	{
		signal(SIGINT, sigint_handler);
		status = g_sigint_received;
		ft_update_exit_status(&status, minidata);
		return (1);
	}
	return (0);
}
