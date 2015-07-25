#ifndef HASH
#define HASH 1
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header.h"

#define HASH_TABLE_LEN 10           //哈希表散列长度10

typedef struct _link_node
{
	int fd;
	int i;
	struct epolldata *mid;
	struct _link_node *next;
}link_node,*link_node_ptr;      	//自定义链表




typedef struct _hash_header
{
	struct _link_node *next;
}hash_header,*hash_header_ptr;  	// 哈希表

extern hash_header_ptr hash_tables[HASH_TABLE_LEN];       //哈希队列初始化

void drop_hash(void);
void init_hash_table(void);
link_node_ptr find_hash_node(int);
int delete_link_node(int );
int append_link_node(int,struct epolldata *);
link_node_ptr init_link_node(void);
void hashshow();
hash_header_ptr init_hash_header_node(void);

#endif
