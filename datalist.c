#include "datalist.h"

struct datalist {
	void*		*data;
	int			size;
	int			writepos;
	int			readpos;
};

struct datalist * datalist_create(int size) {
	struct datalist *list = (struct datalist *)malloc(sizeof(*list));
	list->size = size;
	list->data = (void**)malloc(size*sizeof(void*));
	list->writepos = 0;
	list->readpos = 0;
	return list;
}

void datalist_release(struct datalist *list) {
	if (NULL == list) {
		return ;
	}
	free(list->data);
	free(list);
}

bool datalist_send(struct datalist *list, void *data)
{
	int pos = list->writepos;
	if ( ((pos+1)%list->size) == list->readpos)
	{
		return false;
	}	

	list->data[pos] = data;
	list->writepos = (pos +1)%list->size;

	return true;
}
void* datalist_recv(struct datalist *list)
{
	void *data = NULL;
	int pos = list->readpos;
	if (pos == list->writepos)
	{
		return NULL;
	}
	data = list->data[pos];
	list->readpos = (pos+1)%list->size;

	return data;
}

int datalist_size(struct datalist *list)
{
	return list->size;
	int sz = 0;

	if (list->writepos >= list->readpos) {
		sz = list->writepos - list->readpos;
	}
	else
	{
		sz = list->writepos + list->size - list->readpos;
	}

	return sz;
}
int datalist_readpos(struct datalist *list)
{
	return list->readpos;
}
int datalist_writepos(struct datalist *list)
{
	return list->writepos;
}