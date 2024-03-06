/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:24:00 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/06 15:24:31 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_prompt(void)
{
	char	*user;
	char	*computer;
	char	*display_line;
	char	*old_display_line;
	char	*relative_path;

	user = getenv("USER");
	computer = getenv("SESSION_MANAGER");
	computer = ft_strchr(computer, '/') + 1;
	computer[6] = '\0';
	display_line = ft_strjoin(user, "@");
	old_display_line = display_line;
	display_line = ft_strjoin(display_line, computer);
	free(old_display_line);
	old_display_line = display_line;
	display_line = ft_strjoin(display_line, ":~");
	free(old_display_line);
	relative_path = getenv("PWD");
	relative_path = relative_path + ft_strlen(getenv("HOME"));
	old_display_line = display_line;
	display_line = ft_strjoin(display_line, relative_path);
	free(old_display_line);
	old_display_line = display_line;
	display_line = ft_strjoin(display_line, "$ ");
	free(old_display_line);
	return (display_line);
}
