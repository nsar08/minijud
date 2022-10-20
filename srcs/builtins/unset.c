/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsar <nsar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 12:10:08 by mnikolov          #+#    #+#             */
/*   Updated: 2022/10/20 16:09:40 by nsar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	find_var(char *str, t_env **cur)
{
	t_env	*new;
	int		j;

	while (*cur)
	{
		new = (*cur)->next;
		if (new)
		{
			j = ft_strncmp(new->value, str, ft_strlen(str));
			if (!j)
			{
				(*cur)->next = new->next;
				free_value(new);
				return (1);
			}
		}
		*cur = (*cur)->next;
	}
	return (0);
}

void	free_value(t_env *env)
{
	free(env->value);
	free(env);
	env = 0;
}

void	ft_unset(char *str, t_lst *ms)
{
	t_env	*cur;
	int		k;

	cur = ms->env;
	k = ft_strncmp(cur->value, str, ft_strlen(str));
	if (!k)
	{
		ms->env = ms->env->next;
		free_value(cur);
		ms->n_env--;
		return ;
	}
	else if (find_var(str, &cur))
		ms->n_env--;
}
