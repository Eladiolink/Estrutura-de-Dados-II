#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 5

typedef struct Node Node;

struct Node {
    int info;
    Node * left;
    Node * right;
    Node * father;
};

Node nodes[MAX_NODES];

Node * avail_node = NULL;

Node * alloc_node() {
    Node * n = avail_node;
    if (avail_node != NULL)
        avail_node = avail_node->right;
    return n;
}

void free_node(Node * n) {
    if (n != NULL) {
        n->right = avail_node;
        avail_node = n;
    }
}

void print_avail() {
    printf("l -> ");
    for (Node * n = avail_node; n != NULL; n = n->right)
        printf("%d -> ", abs(&(nodes[0]) - n));
    printf("NULL\n");
}

void init_heap() {
    avail_node = &(nodes[0]);
    for (int n = 0; n < (MAX_NODES-1); n++)
        nodes[n].right = &(nodes[n+1]);
    nodes[MAX_NODES-1].right = NULL;
}

Node * make_tree(int x) {
    Node * n = alloc_node();
    if (n != NULL) {
        n->info = x;
        n->left = NULL;
        n->right = NULL;
        n->father = NULL;
    }
    return n;
}

void set_left(Node *t, Node *l) {
    if (t != NULL && l != NULL) {
        t->left = l;
        l->father = t;
    }
}

void set_right(Node *t, Node *r) {
    if (t != NULL && r != NULL) {
        t->right = r;
        r->father = t;
    }
}

void pre_ordem(Node *t, void (*visit)(Node *n)) {
    if (t != NULL) {
        visit(t);
        pre_ordem(t->left, visit);
        pre_ordem(t->right, visit);
    }
}

void pos_ordem(Node *t, void (*visit)(Node *n)) {
    if (t != NULL) {
        pos_ordem(t->left, visit);
        pos_ordem(t->right, visit);
        visit(t);
    }
}

void em_ordem(Node *t, void (*visit)(Node *n)) {
    if (t != NULL) {
        em_ordem(t->left, visit);
        visit(t);
        em_ordem(t->right, visit);
    }
}

void print_tree_visit(Node *n) {
    printf("%d -> ", n->info);
}

void print_tree(Node *t) {
    pre_ordem(t, print_tree_visit);
    printf("\n");
}

int main() {
    init_heap();
    /*
    print_avail();
    
    Node * n1 = alloc_node(); print_avail();
    Node * n2 = alloc_node(); print_avail();
    Node * n3 = alloc_node(); print_avail();
    Node * n4 = alloc_node(); print_avail();
    Node * n5 = alloc_node(); print_avail();
    Node * n6 = alloc_node(); print_avail();
    printf("n6: %p\n", n6);
    
    free_node(n5); print_avail();
    free_node(n1); print_avail();
    free_node(n2); print_avail();
    free_node(n4); print_avail();
    free_node(n3); print_avail();
    */
    
    Node * t1 = make_tree(10);
    Node * t2 = make_tree(11);
    Node * t3 = make_tree(12);
    
    set_left(t1, t2);
    set_right(t1, t3);
    print_tree(t1);
    
    
    return 0;
}