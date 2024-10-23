/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisimony <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:10:07 by lisimony          #+#    #+#             */
/*   Updated: 2024/10/15 15:10:08 by lisimony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	int			id;
	long long	current_time;

	id = philo->id;
	pthread_mutex_lock(philo->right_fork);
	print_status("has taken a fork", philo, id);
	pthread_mutex_lock(philo->left_fork);
	print_status("has taken a fork", philo, id);
	philo->eating = 1;
	print_status("is eating", philo, id);
	pthread_mutex_lock(philo->meal_lock);
	current_time = get_time();
	philo->last_meal = current_time;
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_sleep(t_philo *philo)
{
	print_status("is sleeping", philo, philo->id);
	ft_usleep(philo->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	print_status("is thinking", philo, philo->id);
}
