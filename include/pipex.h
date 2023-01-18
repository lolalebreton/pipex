/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-bret <lle-bret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:18:25 by lle-bret          #+#    #+#             */
/*   Updated: 2023/01/18 18:17:56 by lle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_arg {
	char	*file1;
	char	*file2;
	char	*cmd1;
	char	*cmd2;
}	t_arg;

int		execute_cmd(t_arg arg);
void	pipex(t_arg arg);

#endif