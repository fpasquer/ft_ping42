#include "libft.h"

void				ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list			*tmp;

	if (lst != NULL && del != NULL)
	{
		while (*lst != NULL)
		{
			tmp = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = tmp;
		}
		free(*lst);
		*lst = NULL;
	}
}
