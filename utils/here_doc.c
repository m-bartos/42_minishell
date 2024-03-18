/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 10:17:25 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/18 10:15:43 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	*expand_all_vars_in_heredoc_line(char *str)
{
	char	*str_old;
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			str_old = str;
			str = get_str_with_one_expanded_var(str, &i);
			free(str_old);
		}
		else
			i++;
	}
	return (str);
}

char	*create_and_open_heredoc_file(int index)
{
	char	*filename;
	char	*str_index;

	str_index = ft_itoa_e(index);
	filename = ft_strjoin_e(HEREDOC_FILE, str_index);
	free(str_index);
	return (filename);
}

char	*get_heredoc_file(char *eof, int index)
{
	char	*filename;
	char	*old_line;
	char	*line;
	int		fd;

	filename = create_and_open_heredoc_file(index);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		line = readline("> ");
		if (ft_strncmp(line, eof, ft_strlen(eof) + 1) == 0)
		{
			free(line);
			break ;
		}
		old_line = line;
		line = ft_strjoin_e(line, "\n");
		free(old_line);
		line = expand_all_vars_in_heredoc_line(line);
		write(fd, line, ft_strlen(line));
		free(line);
	}
	close(fd);
	free(eof);
	return (filename);
}

void	expand_heredocs(t_cmd *cmd)
{
	t_token	*token;
	int		index;

	index = 0;
	token = cmd->first_token;
	while (token != NULL)
	{
		if (token->type == HERE_DOC && token->next->type == HERE_DOC_EOF)
		{
			free(token->text);
			token->text = ft_strdup("<");
			token->type = R_IN;
			token->next->text = get_heredoc_file(token->next->text, index);
			token->next->type = R_INFILE;
		}
		token = token->next;
		index++;
	}
}
