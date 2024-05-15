/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 10:17:25 by mbartos           #+#    #+#             */
/*   Updated: 2024/05/15 09:15:38 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Reads user input for heredoc until EOF and writes to a file.
 *
 * This function opens the specified file for writing, reads lines of input from
 * the user until the EOF delimiter is encountered, expands env variables
 * within each line, and writes the processed lines to the file.
 *
 * @param eof: The end-of-file heredoc delimiter string.
 * @param filename: The filename where the heredoc content will be written.
 * @param env_list: A linked list containing environment variables.
 */
void	fill_heredoc_file(char *eof, char *filename, t_env_list *env_list)
{
	char	*old_line;
	char	*line;
	int		fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	clean_cmd(NULL, fd, eof);
	while (1)
	{
		line = readline("> ");
		if (line == NULL || ft_strncmp(line, eof, ft_strlen(eof) + 1) == 0)
		{
			if (line == NULL)
				ft_putstr_fd("Minishell: heredoc delimited by EOF\n", 1);
			free(line);
			line = NULL;
			break ;
		}
		old_line = line;
		line = ft_strjoin_e(line, "\n");
		free(old_line);
		line = expand_all_vars_in_heredoc_line(line, env_list);
		write(fd, line, ft_strlen(line));
		free(line);
	}
}

/**
 * @brief Handles the creation and population of a heredoc file.
 *
 * This function forks a child process to manage the heredoc input and writing
 * to the specified file. It sets up appropriate signal handlers for both the
 * child and parent processes, and waits for the child process to complete.
 *
 * @param eof: The end-of-file delimiter string for the heredoc input.
 * @param filename: The filename where the heredoc content will be written.
 * @param env_list: A linked list containing environment variables.
 */
void	process_heredoc(char *eof, char *filename, t_env_list *env_list)
{
	int	pid;
	int	status;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, handle_sigint_heredoc);
		fill_heredoc_file(eof, filename, env_list);
		clean_cmd(NULL, 0, NULL);
		exit_minishell(NULL, 0);
	}
	signal(SIGINT, handle_sigint_heredoc_parent);
	waitpid(pid, &status, 0);
	signal(SIGINT, sigint_handler);
}

/**
 * @brief Processes and expands heredoc tokens within a command.
 *
 * This function iterates through the tokens in the command. It replaces
 * the heredoc token with a file redirection token, creates a heredoc file with
 * the specified content, and updates the filename token with the created file's
 * name. The function also checks and updates the shell's exit status based on 
 * the heredoc processing outcome.
 *
 * @param cmd: A pointer to the cmd structure containing the tokens to process.
 * @param minidata: A pointer to the structure containing shell-related data.
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
			token->next->text = create_heredoc_filename(i);
			token->next->type = R_INFILE;
			process_heredoc(next_token_text, token->next->text, env_list);
			free(next_token_text);
			if (set_heredoc_exit_status(minidata) == 1)
				return ;
		}
		token = token->next;
		i++;
	}
}
