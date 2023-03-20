/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 11:15:20 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/03/20 19:22:43 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define BLK "\e[0;90m"
# define RED "\e[0;91m"
# define GRN "\e[0;92m"
# define YEL "\e[0;93m"
# define BLU "\e[0;94m"
# define MAG "\e[0;95m"
# define CYN "\e[0;96m"
# define WHT "\e[0;97m"

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_philo 
{
	pthread_t		*threadtab;
	pthread_mutex_t	*fork;
	int				*index;
	int				nb_of_philo;
	int				*nb_of_meal;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
}	t_philo;

int		error_gestion(int	ac, char ** av);
long	ft_atol(const char *str);

#endif
