/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 11:15:20 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/03/22 14:16:28 by pfaria-d         ###   ########.fr       */
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

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef int	t_boolean;
# define TRUE 1
# define FALSE 0

typedef struct s_philo
{
	pthread_t		*threadtab;
	pthread_mutex_t	*fork;
	pthread_mutex_t	voix;
	t_boolean		*can_eat;
	t_boolean		*can_sleep;
	t_boolean		*is_full;
	t_boolean		is_dead;
	size_t			*last_meal;
	int				*index;
	int				nb_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				as_eaten;
}	t_philo;

typedef struct s_values
{
	int		prev;
	int		index;
	size_t	time;
	int		nb_of_meals;
}	t_values;

int		error_gestion(int ac, char **av);
long	ft_atol(const char *str);
t_philo	initializer(char **av);
void	destroy_mutextab(t_philo *p);
int		create_mutextab(t_philo *p);
void	wait_pthreads(t_philo *p);

//		PHILO MAIN		//
size_t	gtime(void);
void	ft_sleep(int timeobj, t_philo *p);
int		all_as_eaten(t_philo *p);

//		PHILO PHASES	//
void	*philosophers(void	*arg);
void	is_sleeping(t_philo *p, t_values *v);
void	is_eating(t_philo *p, t_values *v);

#endif
