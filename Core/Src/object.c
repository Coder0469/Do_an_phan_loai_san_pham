#include "object.h"

void Queue_InitQueue(Queue* q) {
    q->front = 0;
    q->rear = -1;
    q->itemCount = 0;
}
void Object_InitObject(Object *o,int color, int time){
	o->color = color;
	o->time = time;
}
int Queue_isFull(Queue* q) {
    return q->itemCount == MAX_SIZE;
}
int Queue_isEmpty(Queue* q) {
    return q->itemCount == 0;
}
int Queue_Push(Queue* q, Object data) {
    if (Queue_isFull(q)) {
        return -1;
    }

    // Nếu rear ở cuối mảng, quay vòng về 0
    if (q->rear == MAX_SIZE - 1) {
        q->rear = -1;
    }

    // Tăng rear và gán giá trị
    q->items[++(q->rear)] = data;
    q->itemCount++;
    return 1;
}
int Queue_Pop(Queue* q) {
    if (Queue_isEmpty(q)) {
        return -1; // Trả về -1 để báo lỗi
    }

//    int data = q->items[q->front];

    // Tăng front, nếu vượt quá kích thước thì quay về 0
    q->front++;
    if (q->front == MAX_SIZE) {
        q->front = 0;
    }

    q->itemCount--;
    return 1;
}
Object Queue_Front(Queue* q){
	return q->items[q->front];
}
