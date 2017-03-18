#pragma once

#include "os.h"

struct datalist;

struct datalist * datalist_create(int size);
void datalist_release(struct datalist *list);
bool datalist_send(struct datalist *list, void *data);
void* datalist_recv(struct datalist *list);
int datalist_size(struct datalist *list);
int datalist_readpos(struct datalist *list);
int datalist_writepos(struct datalist *list);

