#include "filter.h"

int get_average(struct Queue* queue) {
    if (isEmpty(queue)) {
        return 0;
    }
    int sum = 0;
    for (unsigned i = 0; i < queue->size; i++) {
        sum += queue->array[i];
    }
    return sum / queue->size;
}
