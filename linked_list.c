#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

void init_list(List *list){
    list->head = NULL;
    list->tail = NULL;
    list->snake_lenght = 0;
}

void add_first(List *list, int x, int y){
    SnakeSegment *newsegment;
    if(!list->head){
        newsegment = (SnakeSegment*)malloc(sizeof(SnakeSegment));
        list->head = newsegment;
        list->tail = newsegment;
        newsegment->next = NULL;
        newsegment->previous = NULL;
        newsegment->x = x;
        newsegment->y = y;
    }
    else {
        newsegment = (SnakeSegment*)malloc(sizeof(SnakeSegment));
        newsegment->next = list->head;
        list->head->previous = newsegment;
        list->head = newsegment;
        newsegment->x = x;
        newsegment->y = y;
    }
    list->snake_lenght++;
}

void remove_last(List *list){
    if(!list) return;
    SnakeSegment *old = list->tail;
    list->tail = list->tail->previous;
    old->previous->next = NULL;
    free(old);
    list->snake_lenght--;
}

void delete_list(List *list){
    while(list->head){
        SnakeSegment *old = list->tail;
        list->tail = list->tail->next;
        free(old);
    }
    free(list);
}