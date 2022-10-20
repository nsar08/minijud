/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsar <nsar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 12:07:01 by mnikolov          #+#    #+#             */
/*   Updated: 2022/10/20 16:12:58 by nsar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_env(t_lst *ms)
{
	t_env	*tmp;
	char	*value;

	tmp = ms->env;
	while (tmp)
	{
		if (ft_strchr(tmp->value, '='))
		{
			ft_putstr_fd(tmp->value, 1);
			ft_putchar_fd('\n', 1);
		}
		tmp = tmp->next;
	}
}
