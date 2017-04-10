/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evwait.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/09 15:31:26 by iwordes           #+#    #+#             */
/*   Updated: 2017/04/09 20:07:01 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libtp_.h>

void	tp_evwait(t_tp_evt *ev, t_tp_mut *lock)
{
	pthread_cond_wait(ev, lock);
}
