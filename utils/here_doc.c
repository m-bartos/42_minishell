/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 10:17:25 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/09 21:55:26 by mbartos          ###   ########.fr       */
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
		write(fd, line, ft_strlen(line));
		free(line);
	}
	close(fd);
	free(eof);
	return (filename);
}

void	expand_heredocs(t_cmd *cmd)
{
	// while loop through cmd_tab
	// check token if there is here_doc type and EOF
	// handle one here doc - make new file, readline and write in it, close it
	// if another here doc is in the same cmd - rewrite the file

	t_token	*ptr_token;
	int		index;

	index = 0;
	ptr_token = cmd->first_token;
	while(ptr_token != NULL)
	{
		if (ptr_token->type == HERE_DOC && ptr_token->next->type == HERE_DOC_EOF)
		{
			free(ptr_token->text);
			ptr_token->text = ft_strdup("<");
			ptr_token->type = R_IN;
			ptr_token->next->text = get_heredoc_file(ptr_token->next->text, index);
			ptr_token->next->type = R_INFILE;
		}
		ptr_token = ptr_token->next;
		index++;
	}
	// how to unlink the files? When, where?
}