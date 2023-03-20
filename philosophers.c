/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 11:08:27 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/03/20 20:30:41 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	wait_pthreads(t_philo *p)
{
	int	i;

	i = 0;
	while (i < p->nb_of_philo)
		pthread_join(p->threadtab[i++], NULL);
	return ;
}

void	*test(void	*arg)
{
	t_philo *p;
	int	prev;
	int	index;
	int	i;

	i = 0;
	p = (t_philo *)arg;
	index = *(int *)p->index;
	prev = index - 1;
	if (index == 0)
		prev = p->nb_of_philo - 1;
	while (p->nb_of_meal[index] == -100 || p->nb_of_meal[index]-- > 0)
	{
		pthread_mutex_lock(&p->fork[prev]);
		pthread_mutex_lock(&p->fork[index]);
		printf("%d took 2 forks\n", index + 1);
		usleep(100000);
		pthread_mutex_unlock(&p->fork[prev]);
		pthread_mutex_unlock(&p->fork[index]);
		printf("meals %d\n", p->nb_of_meal[index]);
	}
	return (NULL);
}

int	create_threadtab(t_philo *p)
{
	int	i;

	i = 0;
	while (i < p->nb_of_philo)
	{
		p->index = malloc(sizeof(int));
		*p->index = i;
		if (i % 2)
			usleep(100);
		if (pthread_create(&p->threadtab[i], NULL, &test, (void *)p) != 0)
			return (1);
		free(p->index);
		i++;
	}
	return (0);
}

int	create_mutextab(t_philo *p)
{
	int	i;

	i = 0;
	while (i < p->nb_of_philo)
		if (pthread_mutex_init(&p->fork[i++], NULL) != 0)
			return (1);
	return (0);
}

void	destroy_mutextab(t_philo *p)
{
	int	i;

	i = 0;
	while (i < p->nb_of_philo)
		pthread_mutex_destroy(&p->fork[i++]);
}

void	initialize_meals(t_philo *p, int nb_of_meals)
{
	int	i;

	i = 0;
	while (i < p->nb_of_philo)
		p->nb_of_meal[i++] = nb_of_meals;
}

int main(int ac, char **av)
{
	t_philo	p;

	if (error_gestion(ac, av))
		return (1);
	p.nb_of_philo = ft_atol(av[1]);
	p.threadtab = malloc(sizeof(pthread_t) * ft_atol(av[1]));
	p.nb_of_meal = malloc(sizeof(pthread_mutex_t) * p.nb_of_philo);
	p.fork = malloc(sizeof(pthread_mutex_t) * p.nb_of_philo);
	p.time_to_die = ft_atol(av[2]);
	p.time_to_eat = ft_atol(av[3]);
	p.time_to_sleep = ft_atol(av[4]);
	initialize_meals(&p, -100);
	if (av[5])
		initialize_meals(&p, ft_atol(av[5]));
	if (create_mutextab(&p))
		return (free(p.threadtab), free(p.fork), 1);
	if (create_threadtab(&p))
		return (free(p.threadtab), free(p.fork), 1);
	wait_pthreads(&p);
	destroy_mutextab(&p);
	return (0);
}
