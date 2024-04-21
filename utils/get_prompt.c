/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:24:00 by mbartos           #+#    #+#             */
/*   Updated: 2024/04/21 14:20:35 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_hostname(void)
{
	int		fd;
	int		length;
	char	*temp_hostname;
	char	*hostname;

	fd = open(HOSTNAME_FILE, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Need hostname file to construct the prompt!\n", 2);
		perror(HOSTNAME_FILE);
		exit_minishell(NULL, EXIT_FAILURE);
	}
	temp_hostname = get_next_line(fd);
	close (fd);
	if (ft_strchr(temp_hostname, '.'))
		length = ft_strchrnul (temp_hostname, '.') - temp_hostname;
	else
		length = ft_strlen(temp_hostname) - 1;
	hostname = ft_substr_e(temp_hostname, 0, length);
	free(temp_hostname);
	return (hostname);
}

char	*get_user_and_computer()
{
	char	*user;
	char	*computer;
	char	*display_line;
	char	*old_display_line;

	user = getenv("USER");
	computer = get_hostname();
	display_line = ft_strjoin_e(user, "@");
	old_display_line = display_line;
	display_line = ft_strjoin_e(display_line, computer);
	free(old_display_line);
	free(computer);
	return (display_line);
}

char	*get_relative_path()
{
	char	*absolute_path;
	char	*relative_path;
	char	*home;
	char	*path_start;

	absolute_path = getcwd(NULL, 0);
	home = getenv("HOME");
	if (home == NULL)
		relative_path = ft_strjoin_e(":", absolute_path);
	else
	{
		relative_path = absolute_path;
		if (ft_strlen(absolute_path) >= ft_strlen(home))
		{
			relative_path = absolute_path + ft_strlen(home);
			path_start = ft_strdup_e(":~");
		}
		else
			path_start = ft_strdup_e(":");
		relative_path = ft_strjoin_e(path_start, relative_path);
		free(path_start);
	}
	free(absolute_path);
	return (relative_path);
}

char	*get_prompt(t_minidata *minidata)
{
	t_env_list	*env_list;
	char		*user_computer;
	char		*display_line;
	char		*old_display_line;
	char		*relative_path;

	env_list = minidata->env_list;
	if (check_prompt_vars(env_list) == TRUE)
	{
		display_line = ft_strdup_e("minishell$ ");
		return (display_line);
	}
	user_computer = get_user_and_computer();
	relative_path = get_relative_path();
	display_line = ft_strjoin_e(user_computer, relative_path);
	free(user_computer);
	free(relative_path);
	old_display_line = display_line;
	display_line = ft_strjoin_e(display_line, "$ ");
	free(old_display_line);
	return (display_line);
}
