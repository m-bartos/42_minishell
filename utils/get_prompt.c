/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:24:00 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/19 12:16:13 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_computer(t_env_list *env_list)
{
	char	*ses_manager;
	char	*computer;
	char	*str_start;
	char	*str_end;
	size_t	len;

	ses_manager = ft_get_env(env_list, "SESSION_MANAGER");
	str_start = ft_strchr(ses_manager, '/') + 1;
	str_end = ft_strchr(ses_manager, ':');
	len = str_end - str_start;
	computer = ft_substr_e(str_start, 0, len);
	free(ses_manager);
	return (computer);
}

char	*get_user_and_computer(t_env_list *env_list)
{
	char	*user;
	char	*computer;
	char	*display_line;
	char	*old_display_line;
	char	*relative_path;

	user = ft_get_env(env_list, "USER");
	computer = get_computer(env_list);
	display_line = ft_strjoin_e(user, "@");
	free(user);
	old_display_line = display_line;
	display_line = ft_strjoin_e(display_line, computer);
	free(old_display_line);
	free(computer);
	old_display_line = display_line;
	display_line = ft_strjoin_e(display_line, ":~");
	free(old_display_line);
	return (display_line);
}

char	*get_relative_path(t_env_list *env_list)
{
	char	*absolute_path;
	char	*relative_path;
	char	*home;

	absolute_path = ft_get_env(env_list, "PWD");
	home = ft_get_env(env_list, "HOME");
	relative_path = absolute_path + ft_strlen(home);
	relative_path = ft_strdup_e(relative_path);
	free(absolute_path);
	free(home);
	return (relative_path);
}

// needs to be rewritten
char	*get_prompt(t_mini_data *minidata)
{
	t_env_list	*env_list;
	char		*user_computer;
	char		*display_line;
	char		*old_display_line;
	char		*relative_path;

	env_list = minidata->env_list;
	user_computer = get_user_and_computer(env_list);
	relative_path = get_relative_path(env_list);
	display_line = ft_strjoin_e(user_computer, relative_path);
	free(user_computer);
	free(relative_path);
	old_display_line = display_line;
	display_line = ft_strjoin_e(display_line, "$ ");
	free(old_display_line);
	return (display_line);
}
