/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qpop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/09 10:20:38 by iwordes           #+#    #+#             */
/*   Updated: 2017/04/09 15:50:24 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libtp_.h>

t_job	*tp_qpop(void)
{
	t_job	*job;

	// 1. Lock the queue
	tp_lock(JOB.lock);

	// 2. Wait for a job
	while (JOB.q == NULL)
		tp_ewait(JOB.ev_new, JOB.lock);

	// 3. Pop the job
	job = JOB.q;
	JOB.q = JOB.q->next;

	// 4. Unlock the queue
	tp_unlock(JOB.lock);

	return (job);
}
