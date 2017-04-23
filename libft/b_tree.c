/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_tree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <wdebs@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 17:55:26 by wdebs             #+#    #+#             */
/*   Updated: 2017/04/03 16:53:23 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		search_bst(t_tree *node, int data)
{
	if (!node)
		return (0);
	if (node->data == data)
		return (1);
	else if (data <= node->data)
		return (search_bst(node->left, data));
	else if (data > node->data)
		return (search_bst(node->right, data));
	return (0);
}

t_tree	*new_node(int data)
{
	t_tree *new_node;

	new_node = (t_tree *)malloc(sizeof(t_tree));
	new_node->data = data;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

t_tree	*insert_bst(t_tree *node, int data)
{
	if (node == NULL)
		node = new_node(data);
	else if (data <= node->data)
		insert_bst(node->left, data);
	else if (data > node->data)
		insert_bst(node->right, data);
	return (node);
}

t_tree	*create_bst(int *arr, int start, int size)
{
	t_tree	*root;
	int		mid;

	root = NULL;
	if (start > size)
		return (NULL);
	mid = start + (size - start) / 2;
	root = insert_bst(root, arr[mid]);
	root->left = create_bst(arr, start, mid - 1);
	root->right = create_bst(arr, mid + 1, size);
	return (root);
}
