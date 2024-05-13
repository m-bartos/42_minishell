/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 10:17:25 by mbartos           #+#    #+#             */
/*   Updated: 2024/05/13 16:37:36 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file here_doc.c
 * @brief Functions for handling here-documents in a command table.
 *
 * This file contains functions related to here-documents, a feature in 
 * shell scripting where input is passed into a command from a document 
 * specified within the script itself.
 * Functions here handle the creation, expansion, and cleanup of here-documents.
 */

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
char	*create_and_open_heredoc_file(int i)
{
	char	*filename;
	char	*str_index;

	str_index = ft_itoa_e(i);
	filename = ft_strjoin_e(HEREDOC_FILE, str_index);
	free(str_index);
	return (filename);
}

/**
 * @brief Get the filename and content of a here-doc file based on user input.
 *
 * This function prompts the user to input lines for a here-doc until
 * the specified end-of-file (eof) string is encountered. It creates a temporary
 * file to store the here-doc content and returns its filename.
 *
 * @param eof The end-of-file string marking the end of here-doc input.
 * @param index The index used to create a unique filename for here-doc file.
 * @return The filename of the created here-doc file.
 */
char	*get_heredoc_file(char *eof, int i, t_env_list *env_list)
{
	char	*filename;
	char	*old_line;
	char	*line;
	int		fd;

	filename = create_and_open_heredoc_file(i);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		line = readline("> ");
		if (line == NULL || ft_strncmp(line, eof, ft_strlen(eof) + 1) == 0)
		{
			if (line == NULL)
				ft_putstr_fd("Minishell warning: heredoc delimited by EOF\n", 1);
			free(line);
			break ;
		}
		old_line = line;
		line = ft_strjoin_e(line, "\n");
		free(old_line);
		line = expand_all_vars_in_heredoc_line(line, env_list);
		write(fd, line, ft_strlen(line));
		free(line);
	}
	close(fd);
	free(eof);
	return (filename);
}

/**
 * @brief Expands here-documents in a command struct by replacing them with file
 * input tokens.
 *
 * This function iterates through the tokens of a command, identifying pairs of
 * tokens representing here-documents and their respective end-of-file markers.
 * For each pair found, it replaces the here-doc token with an input redirection
 * token pointing to a temporary file containing the here-doc content.
 *
 * @param cmd The command whose here-documents are to be expanded.
 */
void	expand_heredocs(t_cmd *cmd, t_minidata *minidata)
{
	t_env_list	*env_list;
	t_token		*token;
	char		*next_token_text;
	int			i;

	env_list = minidata->env_list;
	i = 0;
	token = cmd->first_token;
	while (token != NULL)
	{
		if (token->type == HERE_DOC && token->next->type == HERE_DOC_EOF)
		{
			next_token_text = token->next->text;
			free(token->text);
			token->text = ft_strdup_e("<");
			token->type = R_IN;
			token->next->text = get_heredoc_file(next_token_text, i, env_list);
			token->next->type = R_INFILE;
		}
		token = token->next;
		i++;
	}
}
