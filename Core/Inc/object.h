#define MAX_SIZE 1000
typedef struct{
	int time;
	int color;
} Object;
typedef struct {
    Object items[MAX_SIZE];
    int front;
    int rear;
    int itemCount;
} Queue;
void Queue_InitQueue(Queue* q);
void Object_InitObject(Object *o,int color, int time);
int Queue_isFull(Queue* q);
int Queue_isEmpty(Queue* q);
int Queue_Push(Queue* q, Object data);
int Queue_Pop(Queue* q);
Object Queue_Front(Queue* q);
