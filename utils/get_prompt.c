/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:24:00 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/18 09:59:26 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


// needs to be rewritten
char	*get_prompt(void)
{
	char	*user;
	char	*computer;
	char	*display_line;
	char	*old_display_line;
	char	*relative_path;

	user = getenv("USER"); // use env variable
	computer = getenv("SESSION_MANAGER"); // use env variable
	computer = ft_strchr(computer, '/') + 1;
	computer[6] = '\0';
	display_line = ft_strjoin_e(user, "@");
	old_display_line = display_line;
	display_line = ft_strjoin_e(display_line, computer);
	free(old_display_line);
	old_display_line = display_line;
	display_line = ft_strjoin_e(display_line, ":~");
	free(old_display_line);
	relative_path = getenv("PWD"); // use env variable
	relative_path = relative_path + ft_strlen(getenv("HOME")); // use env variable
	old_display_line = display_line;
	display_line = ft_strjoin_e(display_line, relative_path);
	free(old_display_line);
	old_display_line = display_line;
	display_line = ft_strjoin_e(display_line, "$ ");
	free(old_display_line);
	return (display_line);
}
