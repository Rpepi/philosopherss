/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpepi <rpepi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:56:26 by rpepi             #+#    #+#             */
/*   Updated: 2024/06/14 16:07:23 by rpepi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_routine(void *pointer)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)pointer;
	data = philo->data;
	if (philo->id % 2 && data->nb_philos > 1)
		usleep(15000);
	while (!data->one_is_dead && !data->all_have_eat)
	{
		eating(philo);
		sleeping(philo);
		message("is thinking", data, philo->id);
	}
	return (NULL);
}

int	create_threads(t_data *data)
{
	int		i;

	i = 0;
	data->starting_time = curr_time();
	while (i < data->nb_philos)
	{
		if (pthread_create(&(data->philos[i].thread),
				NULL, ft_routine, &(data->philos[i])))
			return (1);
		data->philos[i].last_meal = curr_time();
		i++;
	}
	dead_check(data, data->philos);
	exit_threads(data, data->philos);
	return (0);
}

void	dead_check(t_data *data, t_philo *philo)
{
	int	i;

	while (!data->all_have_eat)
	{
		i = -1;
		while (++i < data->nb_philos && !data->one_is_dead)
		{
			pthread_mutex_lock(&(data->meals_mutex));
			if (time_diff(philo[i].last_meal, curr_time()) > data->time_to_die)
			{
				message("died", data, philo->id);
				data->one_is_dead = 1;
			}
			pthread_mutex_unlock(&(data->meals_mutex));
		}
		if (data->one_is_dead)
			break ;
		i = 0;
		while (data->nb_meals && i < data->nb_philos
			&& philo[i].nb_meals_eated == data->nb_meals)
			i++;
		data->all_have_eat = (i == data->nb_philos);
	}
}

void	exit_threads(t_data *data, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < data->nb_philos)
		pthread_join(philo[i].thread, NULL);
	i = -1;
	while (++i < data->nb_philos)
		pthread_mutex_destroy(&(data->fork_mutex[i]));
	pthread_mutex_destroy(&(data->writing));
	pthread_mutex_destroy(&(data->meals_mutex));
}
