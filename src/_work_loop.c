/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _work_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/09 09:47:10 by iwordes           #+#    #+#             */
/*   Updated: 2017/04/09 19:52:24 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libtp_.h>

void	done_(t_tp *tp)
{
	tp_lock(&JOB.lock);
	JOB.cnt -= 1;
	if (JOB.cnt == 0)
		tp_evfire(&JOB.ev_done);
	tp_unlock(&JOB.lock);
}

void	*tp__work_loop(t_tp *tp)
{
	t_tp_job	*job;

	while (1)
	{
		job = tp_qpop(tp);
		job->fn(job->ctx);
		free(job);
		done_(tp);
	}
	return (tp);
}
