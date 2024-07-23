/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vyepremy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 21:09:27 by vyepremy          #+#    #+#             */
/*   Updated: 2024/07/23 22:03:31 by vyepremy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#define USAGE "Usage: \n\
	./philosophers [NUM_PHILOS] [FASTING_TIME] [EAT_TIME] [SLEEP_TIME] [[NUM_MEALS]] \
	"
#define MALLOC_ERROR "Malloc Error"

typedef struct	s_data
{


} t_data;

typedef struct	s_philo
{


} t_philo;

size_t	ft_strlen(const char *c)
{
	size_t	size;

	size = 0;
	while (c[size] != '\0')
		++size;
	return (size);
}

void	message(char *msg)
{
	write(1, msg, ft_strlen(msg));
}

int	init_args(int argc, char **argv, t_data *data)
{
	int	n_philosophers;
	int	fasting_time;
	int	eating_time;
	int	sleeping_time;
	int	n_dinners;

	return (0);
}

t_philo *init_philos(t_data *data)
{
	return (NULL);
}

void	start_dinner(t_philo *philos)
{

}

int	main(int argc, char **argv)
{
	t_philo	*philos;
	t_data	data;

	if (init_args(argc, argv, &data) == 0)
	{
		philos = init_philos(&data);
		if (philos)
			start_dinner(philos);
		else
			message(MALLOC_ERROR);
	}
	else
		message(USAGE);
	return (0);
}
