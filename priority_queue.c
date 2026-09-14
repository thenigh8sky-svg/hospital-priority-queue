
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATIENTS 100

typedef struct {
    char name[50];
    int priority;
} Patient;

typedef struct {
    Patient heap[MAX_PATIENTS];
    int size;
} PriorityQueue;

void swap(Patient *a, Patient *b) {
    Patient temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_up(PriorityQueue *pq, int index) {
    if (index == 0) return;
    
    int parent = (index - 1) / 2;
    if (pq->heap[index].priority < pq->heap[parent].priority) {
        swap(&pq->heap[index], &pq->heap[parent]);
        heapify_up(pq, parent);
    }
}

void heapify_down(PriorityQueue *pq, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    
    if (left < pq->size && pq->heap[left].priority < pq->heap[smallest].priority) {
        smallest = left;
    }
    
    if (right < pq->size && pq->heap[right].priority < pq->heap[smallest].priority) {
        smallest = right;
    }
    
    if (smallest != index) {
        swap(&pq->heap[index], &pq->heap[smallest]);
        heapify_down(pq, smallest);
    }
}

void add_patient(PriorityQueue *pq, char *name, int priority) {
    if (pq->size >= MAX_PATIENTS) {
        printf("Queue is full!\n");
        return;
    }
    
    strcpy(pq->heap[pq->size].name, name);
    pq->heap[pq->size].priority = priority;
    heapify_up(pq, pq->size);
    pq->size++;
}

char* treat_next_patient(PriorityQueue *pq) {
    if (pq->size == 0) {
        return NULL;
    }
    
    static char result[50];
    strcpy(result, pq->heap[0].name);
    
    pq->heap[0] = pq->heap[pq->size - 1];
    pq->size--;
    
    if (pq->size > 0) {
        heapify_down(pq, 0);
    }
    
    return result;
}

int main() {
    PriorityQueue pq;
    pq.size = 0;
    
    printf("=== Adding Patients ===\n");
    add_patient(&pq, "P1", 3);
    printf("Added P1 (Priority 3)\n");
    
    add_patient(&pq, "P2", 1);
    printf("Added P2 (Priority 1)\n");
    
    add_patient(&pq, "P3", 2);
    printf("Added P3 (Priority 2)\n");
    
    add_patient(&pq, "P4", 1);
    printf("Added P4 (Priority 1)\n");
    
    add_patient(&pq, "P5", 3);
    printf("Added P5 (Priority 3)\n");
    
    add_patient(&pq, "P6", 2);
    printf("Added P6 (Priority 2)\n");
    
    printf("\n=== Treating Patients (in order) ===\n");
    char *patient;
    int count = 0;
    
    while ((patient = treat_next_patient(&pq)) != NULL) {
        printf("%s\n", patient);
        count++;
        
        if (count == 2) {
            printf("\n*** Adding Emergency Patient P7 (Priority 1) ***\n");
            add_patient(&pq, "P7", 1);
            printf("P7 should be treated next!\n\n");
        }
    }
    
    return 0;
}
