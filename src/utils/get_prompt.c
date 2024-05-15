/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:24:00 by mbartos           #+#    #+#             */
/*   Updated: 2024/05/15 09:56:47 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Retrieves the hostname of the current machine.
 * 
 * This function reads the hostname from a predefined file, extracts the
 * hostname up to the first dot, and returns it as a dynamically allocated
 * string. If the hostname file cannot be opened, it prints an error message
 * and exits the minishell.
 * 
 * @return A dynamically allocated string containing the hostname.
 */
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

/**
 * @brief Constructs a string with the current user and computer name.
 * 
 * This function retrieves the username from the environment variables and
 * the hostname using `get_hostname`. It concatenates these two strings in
 * the format "user@computer" and returns the result as a dynamically
 * allocated string.
 * 
 * @return A dynamically allocated string in the format "user@computer".
 */
char	*get_user_and_computer(void)
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

/**
 * @brief Gets the relative path from home directory to current directory.
 * 
 * This function retrieves the current working directory and the user's home
 * directory from the environment variables. It constructs a relative path that
 * starts with ":~" if the current directory is within the home directory, 
 * or with ":" otherwise. The relative path is returned as a dynamically
 * allocated string.
 * 
 * @return A dynamically allocated string representing the relative path.
 */
char	*get_relative_path(void)
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

/**
 * @brief Constructs the shell prompt string.
 * 
 * This function constructs the shell prompt string using the user and computer
 * name, and the relative path from the home directory to the current directory.
 * It checks if prompt variables are set in the environment, and if so, returns
 * "minishell$ ". Otherwise, it constructs the prompt string in the format 
 * "user@computer:relative_path$ ".
 * 
 * @param minidata A pointer to the structure containing shell-related data.
 * @return A dynamically allocated string representing the shell prompt.
 */
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
