/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsar <nsar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 12:10:03 by mnikolov          #+#    #+#             */
/*   Updated: 2022/10/20 15:41:19 by nsar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//change
#include "../../includes/minishell.h"

static	int	ft_str_isdigit(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
	if (ft_atoi(str) >= 256)
		exit(ft_atoi(str) - 256);
	return (1);
}

void	ft_error_exit(char **cmd)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(cmd[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

void	ft_error_exit2(t_lst *li)
{
	ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	g_ms.exit = 127;
	if (li->pipe)
		exit(g_ms.exit);
}

void	ft_exit(char **cmd, t_lst *li)
{
	int	status;
	int	i;

	i = 0;
	status = 0;
	write(1, "exit\n", 6);
	if (cmd[1] && !ft_str_isdigit(cmd[1]))
	{
		status = 255;
		ft_error_exit(cmd);
	}
	while (cmd[i])
		i++;
	if (i > 2)
	{
		ft_error_exit2(li);
		return ;
	}
	else if (cmd[1] && ft_str_isdigit(cmd[1]))
		status = ft_atoi(cmd[1]);
	free_all(li);
	exit(status);
}
