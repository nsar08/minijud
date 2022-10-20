/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsar <nsar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:03:41 by mnikolov          #+#    #+#             */
/*   Updated: 2022/10/20 12:39:14 by nsar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_builtin(char *str)
{
	if (!ft_strcmp(str, "cd"))
		return (1);
	if (!ft_strcmp(str, "echo"))
		return (1);
	if (!ft_strcmp(str, "env"))
		return (1);
	if (!ft_strcmp(str, "exit"))
		return (1);
	if (!ft_strcmp(str, "export"))
		return (1);
	if (!ft_strcmp(str, "pwd"))
		return (1);
	if (!ft_strcmp(str, "unset"))
		return (1);
	return (0);
}

//change
void	exec_builtin(t_cmd *node, t_lst *ms)
{
	if (ft_strequ(node->cmd, "export\0") && node->av[1])
		node->exit = ft_export(node->av[1], ms);
	else if (ft_strequ(node->cmd, "export\0") && node->av[1] == NULL)
		sort_export(ms);
	else if (ft_strequ(node->cmd, "unset\0") && node->av[1])
		ft_unset(node->av[1], ms);
	else if (ft_strequ(node->cmd, "echo\0"))
		ft_echo(node->av);
	else if (ft_strequ(node->cmd, "exit\0"))
		ft_exit(node->av, ms);
	else if (ft_strequ(node->cmd, "env\0"))
		ft_env(ms);
	else if (ft_strequ(node->cmd, "cd\0"))
		ft_cd(node->av[1], ms);
	else if (ft_strequ(node->cmd, "pwd\0"))
		pwd();
}
