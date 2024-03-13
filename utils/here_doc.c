/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 10:17:25 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/12 12:57:33 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_heredoc_file(char *eof, int index)
{
	char	*filename;
	char	*str_index;
	char	*old_line;
	char	*line;
	int		fd;

	line = NULL;
	str_index = ft_itoa(index);
	filename = ft_strjoin(".heredoc_cmd_", str_index);
	free(str_index);
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
		line = ft_strjoin(line, "\n");
		free(old_line);
		line = expand_all_vars_in_str(line);
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
	while(token != NULL)
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
	// how to unlink the files? When, where?
}