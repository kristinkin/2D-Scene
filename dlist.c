#include"dlist.h"
#include<stdlib.h>
#include<stdio.h>

typedef struct DList_Node {
    void* data;
    struct DList_Node* prev;
    struct DList_Node* next;
} DList_Node;

typedef struct DList {
    DList_Node* head;
    DList_Node* tail;
    size_t size;
    size_t itemSize;
} DList;

static void* create_node(DList* dlist, size_t itemSize) {
    DList_Node* new_node = (DList_Node*)malloc(sizeof(DList_Node));
    if (!new_node)
        return NULL;
    new_node->data = malloc(itemSize);
    if (!new_node->data) {
        free(new_node);
        return NULL;
    }
    new_node->prev = NULL;
    new_node->next = NULL;
    dlist->size++;
    return new_node;
}

static void destroy_node(DList* dlist, DList_Node* node, void(*destroy)(void*)) {
    if (destroy) destroy(node->data);
    free(node->data);
    free(node);
    dlist->size--;
}

void* dlist_create(size_t itemSize) {
    if (!itemSize)
        return NULL;
    DList* new_dlist = (DList*)malloc(sizeof(DList));
    if (!new_dlist) 
        return NULL;
    new_dlist->head = NULL;
    new_dlist->tail = NULL;
    new_dlist->size = 0;
    new_dlist->itemSize = itemSize;
    return new_dlist;
}

void dlist_destroy(void* dlist, void(*destroy)(void*)) {
    if (!dlist)
        return;
    dlist_clear(dlist, destroy);
    free(dlist);
}

void* dlist_init(void* dlist, size_t itemSize, void(*destroy)(void*)) {
    if (!dlist)
        return NULL;
    if (!itemSize)
        return NULL;
    if (((DList*)dlist)->head)
        dlist_clear(dlist, destroy);
    ((DList*)dlist)->itemSize = itemSize;
    ((DList*)dlist)->size = 0;
    return dlist;
}

void dlist_clear(void* dlist, void(*destroy)(void*)) {
    if (!dlist)
        return;
    DList_Node* current = ((DList*)dlist)->head;
    while (current) {
        DList_Node* temp = current->next;
        destroy_node(dlist, current, destroy);
        current = temp;
    }
    ((DList*)dlist)->head = NULL;
    ((DList*)dlist)->tail = NULL;
}

size_t dlist_count(const void* dlist) {
    if (!dlist)
        return INVALID;
    return ((DList*)dlist)->size;
}

void* dlist_item(void* dlist, size_t i) {
    DList* dlist_ = dlist;
    if (!dlist_ || i >= dlist_->size)
        return NULL;
    if (i == dlist_->size - 1)
        return dlist_->tail->data;
    DList_Node* current = dlist_->head;
    for (size_t count = 0; count < dlist_->size; count++) {
        if (count == i) return current->data;
        current = current->next;
    }
    return NULL;
}

void* dlist_append(void* dlist) {
    DList* dlist_ = dlist;
    if (!dlist_)
        return NULL;
    DList_Node* new_tail = create_node(dlist_, dlist_->itemSize);
    if (!new_tail)
        return NULL;
    if (dlist_->size - 1 == 0) {
        dlist_->head = new_tail;
        dlist_->tail = new_tail;
    }
    else {
        new_tail->prev = dlist_->tail;
        dlist_->tail->next = new_tail;
        dlist_->tail = new_tail;
    }
    return new_tail->data;
}

void* dlist_prepend(void* dlist) {
    DList* dlist_ = dlist;
    if (!dlist_)
        return NULL;
    DList_Node* new_head = create_node(dlist_, dlist_->itemSize);
    if (!new_head)
        return NULL;
    if (dlist_->size - 1 == 0) {
        dlist_->head = new_head;
        dlist_->tail = new_head;
    }
    else {
        new_head->next = dlist_->head;
        dlist_->head->prev = new_head;
        dlist_->head = new_head;
    }
    return new_head->data;
}

void dlist_removeFirst(void* dlist, void(*destroy)(void*)) {
    DList* dlist_ = dlist;
    if (!dlist_)
        return;
    if (!dlist_->head)
        return;
    DList_Node* temp = dlist_->head;
    if (dlist_->size == 1) {
        dlist_->head = NULL;
        dlist_->tail = NULL;
    }
    else {
        dlist_->head->next->prev = NULL;
        dlist_->head = dlist_->head->next;
    }
    destroy_node(dlist_, temp, destroy);
}

void dlist_removeLast(void* dlist, void(*destroy)(void*)) {
    DList* dlist_ = dlist;
    if (!dlist_)
        return;
    if (!dlist_->tail)
        return;
    DList_Node* temp = dlist_->tail;
    if (dlist_->size == 1) {
        dlist_->head = NULL;
        dlist_->tail = NULL;
    }
    else {
        dlist_->tail->prev->next = NULL;
        dlist_->tail = dlist_->tail->prev;
    }
    destroy_node(dlist_, temp, destroy);
}

size_t dlist_first(const void* dlist) {
    if (!dlist)
        return dlist_stop(dlist);
    return (size_t)((DList*)dlist)->head;
}

size_t dlist_last(const void* dlist) {
    if (!dlist)
        return dlist_stop(dlist);
    return (size_t)((DList*)dlist)->tail;
}

size_t dlist_next(const void* dlist, size_t item_id) {
    if (!dlist || item_id == dlist_stop(dlist))
        return dlist_stop(dlist);
    return (size_t)((DList_Node*)item_id)->next;
}

size_t dlist_prev(const void* dlist, size_t item_id) {
    if (!dlist || item_id == dlist_stop(dlist))
        return dlist_stop(dlist);
    return (size_t)((DList_Node*)item_id)->prev;
}

size_t dlist_stop(const void* dlist) {
    return (size_t)NULL;
}

void* dlist_current(const void* dlist, size_t item_id) {
    if (!dlist || item_id == dlist_stop(dlist))
        return NULL;
    return ((DList_Node*)item_id)->data;
}

void* dlist_insertAfter(void* dlist, size_t item_id) {
    DList* dlist_ = dlist;
    if (!dlist_)
        return NULL;
    if ((DList_Node*)item_id == dlist_->tail || dlist_->size == 0) {
        return dlist_append(dlist_);
    }
    if (item_id == dlist_stop(dlist_)) {
        if (!dlist_->size) {
            return dlist_append(dlist_);
        }
        else return NULL;
    }
    DList_Node* current = (DList_Node*)item_id;
    DList_Node* new_node = create_node(dlist_, dlist_->itemSize);
    if (!new_node) 
        return NULL;
    new_node->prev = current;
    new_node->next = current->next;
    if (current->next) 
        current->next->prev = new_node;
    current->next = new_node;
    return new_node->data;
}

void* dlist_insertBefore(void* dlist, size_t item_id) {
    DList* dlist_ = dlist;
    if (!dlist_)
        return NULL;
    if ((DList_Node*)item_id == dlist_->head || dlist_->size == 0) {
        return dlist_prepend(dlist_);
    }
    if (item_id == dlist_stop(dlist))
        return NULL;
    DList_Node* current = (DList_Node*)item_id;
    DList_Node* new_node = create_node(dlist_, dlist_->itemSize);
    if (!new_node)
        return NULL;
    new_node->next = current;
    new_node->prev = current->prev;
    if (current->prev)
        current->prev->next = new_node;
    current->prev = new_node;
    return new_node->data;
}

void dlist_erase(void* dlist, size_t item_id, void(*destroy)(void*)) {
    DList* dlist_ = dlist;
    if (!dlist_ || item_id == dlist_stop(dlist_))
        return;
    if (dlist_->size == 0)
        return;
    DList_Node* current = (DList_Node*)item_id;
    if (current->prev)
        current->prev->next = current->next;
    if (current->next) 
        current->next->prev = current->prev;
    if (current == dlist_->head)
        dlist_->head = current->next;
    if (current == dlist_->tail)
        dlist_->tail = current->prev;
    destroy_node(dlist_, current, destroy);
}