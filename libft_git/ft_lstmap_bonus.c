/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcotza <thcotza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 18:43:28 by thcotza           #+#    #+#             */
/*   Updated: 2025/10/19 18:09:06 by thcotza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*cp;
	void	*res;

	cp = NULL;
	if (!lst || !f || !del)
		return (0);
	while (lst)
	{
		res = f(lst->content);
		new = ft_lstnew(res);
		if (!new)
		{
			del(res);
			ft_lstclear(&cp, del);
			return (0);
		}
		ft_lstadd_back(&cp, new);
		lst = lst->next;
	}
	return (cp);
}
