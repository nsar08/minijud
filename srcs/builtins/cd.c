/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsar <nsar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:33:24 by mnikolov          #+#    #+#             */
/*   Updated: 2022/10/20 15:33:55 by nsar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*cd_only(t_lst *ms)
{
	char	*path;

	path = get_env_value("HOME", ms);
	if (!path)
	{
		g_ms.exit = 1;
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (NULL);
	}
	return (path);
}

int	change(char *tmp, t_lst *ms)
{
	char	*temp_join;
	
	temp_join = ft_strjoin("OLDPWD=", tmp);
	ft_export(temp_join, ms);
	free(temp_join);
	temp_join = ft_strjoin("PWD=", getcwd(tmp, PATH_MAX));
	ft_export(temp_join, ms);
	free(temp_join);
	return (0);
}

int	ft_cd(char *path, t_lst *ms)
{
	char	tmp[PATH_MAX];
	char	*nwd;

	getcwd(tmp, PATH_MAX);
	if (!path)
		nwd = cd_only(ms);
	else
		nwd = path;
	if (chdir(nwd))
	{
		g_ms.exit = 1;
		msg_error("minishell: cd:", ' ', nwd);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (-1);
	}
	change(tmp, ms);
	return (0);
}
