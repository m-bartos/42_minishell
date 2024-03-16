/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_ops.c.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 11:42:36 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/16 22:45:35 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @brief Removes an environment variable by name.
 *
 * Searches and nullifies the value of a variable by name. The node remains.
 *
 * @param env_list Pointer to the environment list.
 * @param var_name Name of the variable to remove.
 * @return 0 if found and nullified, 1 otherwise.
 */

int	ft_remove_env(t_env_list *env_list, char *var_name)
{
	t_env	*node;

	node = env_list->top;
	while (node)
	{
		if (node->value != NULL)
		{
			if (ft_strncmp(node->value, var_name, ft_strlen(var_name)) == 0
				&& *(node->value + (ft_strlen(var_name))) == '=')
			{
				free(node->value);
				node->value = NULL;
				env_list->size--;
				return (0);
			}
		}
		node = node->next;
	}
	return (1);
}

/**
 * @brief Removes an environment variable by full string.
 *
 * Searches and nullifies the value of a variable by
 * 			its full string. Node remains.
 *
 * @param env_list Pointer to the environment list.
 * @param str Full string of the variable to remove.
 * @return 0 if found and nullified, 1 otherwise.
 */

int	ft_remove_str(t_env_list *env_list, char *str)
{
	t_env	*node;

	node = env_list->top;
	while (node)
	{
		if (node->value != NULL)
		{
			if (ft_strncmp(node->value, str, ft_strlen(str)) == 0)
			{
				free(node->value);
				node->value = NULL;
				env_list->size--;
				return (0);
			}
		}
		node = node->next;
	}
	return (1);
}

/**
 * @brief Adds a new environment variable.
 *
 * Adds or updates an environment variable in the list.
 *
 * @param env_list Pointer to the list where the variable will be added.
 * @param env String of the environment variable to add.
 */

void	ft_add_env(t_env_list *env_list, char *env)
{
	t_env	*node;

	ft_remove_str(env_list, env);
	node = malloc(sizeof(t_env));
	if (!node)
	{
		perror("Add env:");
		exit(1);
	}
	ft_init_env(node);
	node->value = ft_strdup(env);
	node->next = env_list->top;
	env_list->top = node;
	env_list->size++;
}

/**
 * @brief Retrieves the value of an environment variable.
 *
 * Searches for a variable by name, returning its value. Caller must free
 * the returned string.
 *
 * @param env_list Pointer to the environment list.
 * @param var_name Name of the variable.
 * @return Newly allocated string with the value, or NULL.
 */

char	*ft_get_env(t_env_list *env_list, char *var_name)
{
	t_env	*env;
	char	*env_value;

	env = env_list->top;
	while (env)
	{
		if (env->value != NULL)
		{
			if (ft_strncmp(env->value, var_name, ft_strlen(var_name)) == 0
				&& *(env->value + (ft_strlen(var_name))) == '=')
			{
				env_value = env->value;
				while (*env_value != '=')
					env_value++;
				env_value++;
				env_value = ft_strdup(env_value);
				return (env_value);
			}
		}
		env = env->next;
	}
	return (NULL);
}

/**
 * @brief Lists all environment variables.
 *
 * Iterates and prints each variable in the list to standard output.
 *
 * @param env_list Pointer to the list of environment variables.
 */

void	ft_list_env(t_env_list *env_list)
{
	t_env	*env;

	env = env_list->top;
	while (env)
	{
		if (env->value != NULL)
		{
			ft_putstr_fd(env->value, STDOUT);
			ft_putstr_fd("\n", STDOUT);
		}
		env = env->next;
	}
}

/**
 * @brief Converts an array of strings to a list of variables.
 *
 * Each string representing an environment variable is added to the list.
 *
 * @param env_list Pointer to the environment list.
 * @param envp Array of strings of environment variables.
 */

void	ft_convert_arr_to_list(t_env_list *env_list, char **envp)
{
	while (*envp)
	{
		ft_add_env(env_list, *envp);
		envp++;
	}
}

/**
 * @brief Converts a list of variables to an array of strings.
 *
 * Creates an array of strings from the list, ending with NULL.
 *
 * @param env_list Pointer to the environment list.
 * @return Array of strings representing the environment variables.
 */

char	**ft_convert_list_to_arr(t_env_list *env_list)
{
	int		i;
	char	**envp;
	t_env	*env;

	i = 0;
	envp = malloc(sizeof(char *) * (env_list->size + 1));
	if (!envp)
	{
		perror("Convert list to arr: ");
		exit(1);
	}
	env = env_list->top;
	while (env)
	{
		if (env->value != NULL)
		{
			envp[i] = env->value;
			i++;
		}
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}
