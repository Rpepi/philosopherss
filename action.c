/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpepi <rpepi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:55:51 by rpepi             #+#    #+#             */
/*   Updated: 2024/05/28 14:08:35 by rpepi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	message(char *str, t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->writing));
	if (!(philo->data->one_is_dead))
	{
		printf("%lld ", get_current_time() - philo->data->starting_time);
		printf("%i ", philo->id + 1);
		printf("%s\n", str);
	}
	pthread_mutex_unlock(&(philo->data->writing));
	return ;
}

void	thinking(t_philo *philo)
{
	message("is thinking", philo);
}

void	sleeping(t_philo *philo)
{
	message("is sleeping", philo);
	ft_sleep(philo->data->time_to_sleep, philo->data);
}

void	eating(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&(data->fork_mutex[philo->l_fork_id]));
	message("has taken a fork", philo);
	if (data->nb_philos == 1)
	{
		ft_sleep(data->time_to_die, philo->data);
		pthread_mutex_unlock(&(data->fork_mutex[philo->l_fork_id]));
		return ;
	}
	pthread_mutex_lock(&(data->fork_mutex[philo->r_fork_id]));
	message("has taken a fork", philo);
	pthread_mutex_lock(&(data->meals_mutex));
	message("is eating", philo);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(&(data->meals_mutex));
	ft_sleep(data->time_to_eat, philo->data);
	(philo->nb_meals_eated)++;
	pthread_mutex_unlock(&(data->fork_mutex[philo->l_fork_id]));
	pthread_mutex_unlock(&(data->fork_mutex[philo->r_fork_id]));
}
