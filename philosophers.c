/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 11:08:27 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/03/21 18:44:44 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	millisecondsuwu(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

void	ft_sleep(int timeobj, t_philo *p)
{
	size_t	time;

	time = millisecondsuwu();
	while (millisecondsuwu() - time < (size_t)timeobj && p->is_dead == FALSE)
		usleep(60);
}

int	all_as_eaten(t_philo *p)
{
	int	i;

	i = 0;
		while (i < p->as_eaten)
			if (p->is_full[i++] == FALSE)
				return (1);
	if (p->as_eaten == -1)
		return (1);
	return (0);
}

void	*test(void	*arg)
{
	t_philo *p;
	int	prev;
	int	index;
	size_t	time;
	int	nb_of_meals;
	size_t	last_meal;

	nb_of_meals = 0;
	time = millisecondsuwu();
	last_meal = millisecondsuwu();
	p = (t_philo *)arg;
	index = *(int *)p->index;
	prev = index - 1;
	if (index == 0)
		prev = p->nb_of_philo - 1;
	while (all_as_eaten(p) && p->is_dead == FALSE)
	{
		if (p->can_eat[index] == FALSE && p->is_dead == FALSE)
		{
			pthread_mutex_lock(&p->fork[prev]);
			pthread_mutex_lock(&p->voix);
			if (p->is_dead == FALSE)
				printf(MAG "%lu %d has taken a fork\n", millisecondsuwu() - time, index + 1);
			pthread_mutex_unlock(&p->voix);
			pthread_mutex_lock(&p->fork[index]);
			pthread_mutex_lock(&p->voix);
			if (p->is_dead == FALSE)
				printf(MAG "%lu %d has taken a fork\n", millisecondsuwu() - time, index + 1);
			pthread_mutex_unlock(&p->voix);
			p->can_eat[index] = TRUE;
			nb_of_meals++;
			if (nb_of_meals >= p->as_eaten && p->as_eaten != -1)
				p->is_full[index] = TRUE;
			pthread_mutex_lock(&p->voix);
			if (p->is_dead == FALSE)
				printf(BLU "%lu %d is eating\n", millisecondsuwu() - time, index + 1);
			pthread_mutex_unlock(&p->voix);
			last_meal = millisecondsuwu();
			ft_sleep(p->time_to_eat, p);
			pthread_mutex_unlock(&p->fork[prev]);
			pthread_mutex_unlock(&p->fork[index]);
			p->can_sleep[index] = TRUE;
		}
		else if (p->can_sleep[index] == TRUE && p->is_dead == FALSE)
		{
			pthread_mutex_lock(&p->voix);
			if (p->is_dead == FALSE)
				printf(CYN "%lu %d is sleeping\n", millisecondsuwu() - time, index + 1);
			pthread_mutex_unlock(&p->voix);
			ft_sleep(p->time_to_sleep, p);
			p->can_eat[index] = FALSE;
			p->can_sleep[index] = FALSE;
			pthread_mutex_lock(&p->voix);
			if (p->is_dead == FALSE)
				printf(GRN "%lu %d is thinking\n", millisecondsuwu() - time, index + 1);
			pthread_mutex_unlock(&p->voix);
		}
		if (millisecondsuwu() - last_meal > (size_t)p->time_to_die && p->is_dead == FALSE)
		{
			p->is_dead = TRUE;
			pthread_mutex_lock(&p->voix);
			printf(RED "%lu %d died\n", millisecondsuwu() - time, index + 1);
			pthread_mutex_unlock(&p->voix);
		}
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
		{
			usleep(12);
			return (1);
		}
		free(p->index);
		i++;
	}
	return (0);
}

int main(int ac, char **av)
{
	t_philo	p;

	if (error_gestion(ac, av))
		return (1);
	p = initializer(av);
	pthread_mutex_init(&p.voix, NULL);
	if (create_mutextab(&p))
		return (free(p.threadtab), free(p.fork), 1);
	if (create_threadtab(&p))
		return (free(p.threadtab), free(p.fork), 1);
	wait_pthreads(&p);
	destroy_mutextab(&p);
	return (0);
}
