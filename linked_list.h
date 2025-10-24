#ifndef LINKED_LIST
#define LINKED_LIST

typedef struct SnakeSegment {
    int x;
    int y;
    struct SnakeSegment* next;
    struct SnakeSegment* previous;
} SnakeSegment;

typedef struct {
    SnakeSegment* head;
    SnakeSegment* tail;
    int snake_lenght;
} List;

void init_list(List *list);
void add_first(List *list, int x, int y);
void remove_last(List *list);
void delete_list(List *list);

#endif
