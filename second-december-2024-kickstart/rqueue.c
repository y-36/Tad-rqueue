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
    //complete here!
}

bool rqueue_is_empty(rqueue_t q) {
    //complete here!
}

static node_t create_node(elem_t e) {
    //complete here!
}

rqueue_t rqueue_enqueue(rqueue_t q, elem_t e) {
    node_t new_node = NULL;
    node_t aux = NULL;
    orientation_t prev;
    orientation_t next;
    orientation_t lst;
    assert(q != NULL);
    new_node = create_node(e);
    if(rqueue_is_empty(q)) {
        q->extreme[current(q)] = new_node;
        q->extreme[inverse(q)] = new_node;
    }
    else {
        //complete here!
    }
    return q;
}

elem_t rqueue_fst(rqueue_t q) {
    assert(q != NULL);
    assert(!rqueue_is_empty(q));
    return q->extreme[current(q)]->value;
}

void rqueue_dequeue(rqueue_t q) {
    //complete here!
}

void rqueue_revert(rqueue_t q) {
    //complete here!
}

rqueue_t rqueue_destroy(rqueue_t q) {
    //complete here!
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
