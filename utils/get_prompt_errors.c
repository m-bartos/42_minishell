/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt_errors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:57:57 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/25 10:32:13 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_var_in_env_list(t_env_list *env_list, char *var_name)
{
	char	*test_var;
	int		is_ok;

	is_ok = TRUE;
	test_var = ft_get_env(env_list, var_name);
	if (test_var == NULL)
	{
		ft_putstr_fd("Cannot find '", 2);
		ft_putstr_fd(var_name, 2);
		ft_putstr_fd("' variable needed for prompt!\n", 2);
		is_ok = FALSE;
	}
	free(test_var);
	return (is_ok);
}

int	is_user(void)
{
	char	*user;
	int		is_ok;

	is_ok = TRUE;
	user = getenv("USER");
	if (user == NULL)
	{
		ft_putstr_fd("Cannot find '", 2);
		ft_putstr_fd("USER", 2);
		ft_putstr_fd("' variable in parent process needed for prompt!\n", 2);
		is_ok = FALSE;
	}
	return (is_ok);
}

int	check_prompt_vars(t_env_list *env_list)
{
	int		is_error;

	is_error = FALSE;
	if (is_user() == FALSE)
		is_error = TRUE;
	if (is_var_in_env_list(env_list, "PWD") == FALSE)
		is_error = TRUE;
	// if (is_var_in_env_list(env_list, "HOME") == FALSE)
	// 	is_error = TRUE;
	return (is_error);
}
