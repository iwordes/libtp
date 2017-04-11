/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 10:34:53 by iwordes           #+#    #+#             */
/*   Updated: 2017/04/11 10:38:30 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libtp_.h>

void	tp_destroy(t_tp *tp)
{
	t_tp_job	ex;
	unsigned	i;

	i = 0;
	ex.ctx = NULL;
	ex.fn = tp__kill_thread;
	while (i < tp->nth)
	{
		tp_lock(&JOB.lock);
		JOB.q = &ex;
		tp_evfire(&JOB.ev_new);
		tp_unlock(&JOB.lock);
	}
	pthread_mutex_destroy(&JOB.lock);
	pthread_cond_destroy(&JOB.ev_new);
	pthread_cond_destroy(&JOB.ev_done);
	free(tp->th);
	free(tp);
}
