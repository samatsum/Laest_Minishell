/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 21:25:41 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/28 10:06:04 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		exec_builtin(t_node *node, t_context *ctx);
bool	is_builtin(t_node *node);

/* ************************************************************************** */
int	exec_builtin(t_node *node, t_context *ctx)
{
	int		status;
	char	**argv;

	do_redirect(node->cmd_node->redirects_node, ctx);
	argv = token_list_to_argv(node->cmd_node->args_token);
	if (ft_strcmp(argv[0], "exit") == 0)
		status = builtin_exit(argv, ctx);
	else if (ft_strcmp(argv[0], "export") == 0)
		status = builtin_export(argv, ctx);
	else if (ft_strcmp(argv[0], "unset") == 0)
		status = builtin_unset(argv, ctx);
	else if (ft_strcmp(argv[0], "env") == 0)
		status = builtin_env(argv, ctx);
	else if (ft_strcmp(argv[0], "cd") == 0)
		status = builtin_cd(argv, ctx);
	else if (ft_strcmp(argv[0], "echo") == 0)
		status = builtin_echo(argv);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		status = builtin_pwd(argv, ctx);
	else
		todo("exec_builtin");
	reset_redirect(node->cmd_node->redirects_node);
	free_argv(argv);
	return (status);
}

/* ************************************************************************** */
bool	is_builtin(t_node *node)
{
	const char			*cmd_name;
	static const char	*builtin_commands[] = {"exit", "export", "unset", \
		"env", "cd", "echo", "pwd"};
	unsigned int		i;

	if (node == NULL || node->cmd_node == NULL)
		return (false);
	if (node->cmd_node->args_token == NULL \
		|| node->cmd_node->args_token->word == NULL)
		return (false);
	cmd_name = node->cmd_node->args_token->word;
	i = 0;
	while (i < sizeof(builtin_commands) / sizeof(*builtin_commands))
	{
		if (ft_strcmp(cmd_name, builtin_commands[i]) == 0)
			return (true);
		i++;
	}
	return (false);
}
