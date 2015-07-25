#include "hash.h"
hash_header_ptr hash_tables[HASH_TABLE_LEN];
/*
	哈希表初始化
*/
void init_hash_table()
{
	char i=0;
	for(i=0;i<HASH_TABLE_LEN;++i)
	{
		hash_tables[i]=init_hash_header_node();
		hash_tables[i]->next=NULL;
	}
}
void hashshow()
{
	link_node_ptr node;
	int i;
	for(i=0;i<HASH_TABLE_LEN;++i)
	{
		node=hash_tables[i]->next;
		while(node!=NULL)
		{
			printf("%d\n",node->fd);
			printf("%i\n",node->i);
			node=node->next;
		}
	}
}
/*
	表头初始化
*/
hash_header_ptr init_hash_header_node()
{
	hash_header_ptr node;
	node=(hash_header_ptr)malloc(sizeof(hash_header));
	node->next=NULL;
	return node;
}

/*
	节点初始化
*/
link_node_ptr init_link_node()
{
	link_node_ptr node;
	node=(link_node_ptr)malloc(sizeof(link_node));
	node->next=NULL;
	return node;
}

/*
	接收更新函数 
*/
/*
	找到1表示可加入0表示-1出错
*/
int append_link_node(int fd,struct epolldata *mid)
{
	char pos=fd%10;
	int l=0;
	if(hash_tables[pos]->next==NULL)
	{
		link_node_ptr node=init_link_node();
		node->next=NULL;
		node->fd=fd;
		node->mid=mid;
		hash_tables[pos]->next=node;
		return 0;
	}
	else
	{
		link_node_ptr nodd;
		nodd=hash_tables[pos]->next;
		while(nodd!=NULL)
		{
			if(nodd->fd==fd)
			{
				l=1;
				return 1;
			}
			else
			{
				nodd=nodd->next;
			}
		}
		if((nodd==NULL)&&(l==0))
		{
			link_node_ptr node=init_link_node();
			node->next=NULL;
			link_node_ptr nod;
			nod=hash_tables[pos]->next;
			node->fd=fd;
			node->mid=mid;
			hash_tables[pos]->next=node;
			node->next=nod;
			return 0;
		}
	}
	return -1;
}
/*
	查找hash函数
*/
/*
	找到返回节点未找到返回NULL
*/
link_node_ptr find_hash_node(int fd)
{
	int pos=fd%10;
	if(hash_tables[pos]->next==NULL)
	{
		return NULL;
	}
	else
	{
		link_node_ptr nodd;
		nodd=hash_tables[pos]->next;
		while(nodd!=NULL)
		{
			if(nodd->fd==fd)
			{
				return nodd;
			}
			else
			{
				nodd=nodd->next;
			}
		}
		return NULL;
	}
}

/*
	节点删除函数
*/
int delete_link_node(int fd)
{
	int pos=0;
	pos=fd%10;
	if(hash_tables[pos]->next->fd==fd)
	{
		link_node_ptr delete_node;
		delete_node=hash_tables[pos]->next;
		hash_tables[pos]->next=hash_tables[pos]->next->next;
		free(delete_node);
		delete_node=NULL;
		return 1;
	}
	else
	{
		link_node_ptr dnode;
		dnode=hash_tables[pos]->next;
		while(dnode!=NULL)
		{
			if(dnode->next->fd!=fd)
			{
				dnode=dnode->next;
			}
			else
			{
				link_node_ptr ddnode;
				ddnode=dnode->next;
				dnode=ddnode->next;
				free(ddnode);
				ddnode=NULL;
				return 1;
			}
		}
	}
	return 0;
}


/*
	哈希表清理
*/
void drop_hash()
{
	link_node_ptr node;
	short i=0;
	link_node_ptr node_next;
	for(i=0;i<HASH_TABLE_LEN;++i)
	{
		node=hash_tables[i]->next;
		while(1)
		{
			if(node==NULL)
			{
				hash_tables[i]->next=NULL;
				break;
			}
			node_next=node->next;
			free(node);
			node=node_next;
		}
	}
}

