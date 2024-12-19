#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "rqueue.h"
#include "assert.h"

struct _node_t {
    struct _node_t * links[2];
    elem_t value;
};

typedef struct _node_t * node_t;
typedef int orientation_t;

struct _rqueue_t {
    node_t extreme[2];
    orientation_t orientation;
};

static orientation_t current(rqueue_t q) {
    return q->orientation;
}

static orientation_t inverse(rqueue_t q) {
    return 1 - q->orientation;
}

rqueue_t rqueue_empty() {
    //complete!
    rqueue_t q = malloc(sizeof(struct _rqueue_t));
    if (!q) {
        perror("Failed to create queue");
        exit(EXIT_FAILURE);
    }
    q->extreme[0] = NULL;
    q->extreme[1] = NULL;
    q->orientation = 0; // Initially node q
    return q;
}

bool rqueue_is_empty(rqueue_t q) {
    //complete!
    return q->extreme[0] == NULL && q->extreme[1] == NULL;
}

static node_t create_node(elem_t e) {
    //complete!
    node_t node = malloc(sizeof(struct _node_t));
    if (!node) {
        perror("Failed to create node");
        exit(EXIT_FAILURE);
    }
    node->value = e;
    node->links[0] = NULL;
    node->links[1] = NULL;
    return node;
}

rqueue_t rqueue_enqueue(rqueue_t q, elem_t e) {
    assert(q != NULL);
    node_t new_node = create_node(e);
    orientation_t curr = current(q);  
    orientation_t opp = inverse(q); 

    if (rqueue_is_empty(q)) {
        // Init the new node in the two extreme
        q->extreme[0] = new_node;
        q->extreme[1] = new_node;
    } else {
        // add the new node and refresh extreme current 
        q->extreme[curr]->links[curr] = new_node;
        new_node->links[opp] = q->extreme[curr];
        q->extreme[curr] = new_node;
    }
    return q;
}

elem_t rqueue_fst(rqueue_t q) {
    assert(q != NULL);
    assert(!rqueue_is_empty(q));
    return q->extreme[current(q)]->value;
}

void rqueue_dequeue(rqueue_t q) {
    //complete!
    if (rqueue_is_empty(q)) return;

    node_t to_free = q->extreme[current(q)];
    q->extreme[current(q)] = to_free->links[inverse(q)];

    if (q->extreme[current(q)]) {
        q->extreme[current(q)]->links[current(q)] = NULL;
    } else {
        q->extreme[inverse(q)] = NULL; // Queue is now empty
    }
    free(to_free);
}

void rqueue_revert(rqueue_t q) {
    //complete!
    q->orientation = inverse(q);
}

rqueue_t rqueue_destroy(rqueue_t q) {
    //complete!
    while (!rqueue_is_empty(q)) {
        rqueue_dequeue(q);
    }
    free(q);
    return NULL;
}

void rqueue_dump(rqueue_t q) {
    orientation_t next;
    orientation_t fst;
    node_t aux = NULL;
    elem_t elem;
    assert(q != NULL);
    next = inverse(q);
    fst  = current(q);
    aux = q->extreme[fst];
    printf("\n Queue:");
    while(aux != NULL) {
        elem = aux->value;
        printf("%d ",elem);
        aux = aux->links[next];
    }
    printf("\n");
}
