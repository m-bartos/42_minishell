/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_ops.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 11:42:36 by aldokezer         #+#    #+#             */
/*   Updated: 2024/04/21 20:23:25 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (node->env_text != NULL)
		{
			if (ft_strncmp(node->env_text, var_name, ft_strlen(var_name)) == 0
				&& *(node->env_text + (ft_strlen(var_name))) == '=')
			{
				free(node->env_text);
				free(node->env_name);
				free(node->env_value);
				node->env_text = NULL;
				node->env_name = NULL;
				node->env_value = NULL;
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

void	ft_add_env(t_env_list *env_list, char *env_text)
{
	t_env	*node;
	char	*env_name;
	char	*env_value;
	int		len_env_name;

	len_env_name = ft_strchr(env_text, '=') - env_text;
	env_name = ft_substr_e(env_text, 0, len_env_name);
	env_value = ft_strdup_e(ft_strchr(env_text, '=') + 1);
	ft_remove_env(env_list, env_name);
	node = malloc(sizeof(t_env));
	if (!node)
	{
		perror("Add env:");
		exit(1);
	}
	ft_init_env(node);
	node->env_text = ft_strdup_e(env_text);
	node->env_name = env_name;
	node->env_value = env_value;
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
		if (env->env_text != NULL)
		{
			if (ft_strncmp(env->env_name, var_name,
					ft_strlen(var_name) + 1) == 0)
			{
				env_value = ft_strdup_e(env->env_value);
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
		if (env->env_text != NULL)
		{
			if (ft_strncmp(env->env_name, "?", strlen(env->env_name) + 1) == 0)
			{
				env = env->next;
				continue ;
			}
			else
			{
				ft_putstr_fd(env->env_text, STDOUT);
				ft_putstr_fd("\n", STDOUT);
			}
		}
		env = env->next;
	}
}

void	ft_remove_env_list(t_env_list *env_list)
{
	t_env	*node;
	t_env	*next_node;

	node = env_list->top;
	while (node)
	{
		next_node = node->next;
		if (node->env_text != NULL)
		{
			free(node->env_text);
			free(node->env_name);
			free(node->env_value);
			node->env_text = NULL;
			node->env_name = NULL;
			node->env_value = NULL;
			node->next = NULL;
			env_list->size--;
		}
		free(node);
		node = next_node;
	}
	free(env_list);
}
