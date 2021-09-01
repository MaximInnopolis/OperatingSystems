#include <stdio.h>
#include <stdlib.h>

struct Node{
    int number;
    struct Node* next;
};

void print_list(struct Node* node){
    while (node != NULL) {
        printf("%d\n", node->number);
        node = node->next;
    }
}

void insert_node(struct  Node* head, int value){
    struct Node* new_node = NULL;
    new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->number = value;
    new_node->next = NULL;
    head->next = new_node;
}

void delete_node(struct  Node* head, int value){
    struct Node* tmp = head, *previous;

    if (tmp != NULL && tmp->number == value) {
        head = tmp->next;
        free(tmp);
        return;
    }

    while (tmp != NULL && tmp->number != value) {
        previous = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL)
        return;

    previous->next = tmp->next;

    free(tmp);
}

int main() {

    struct Node* head1 = NULL;
    head1 = (struct Node*)malloc(sizeof(struct Node));
    head1->number = 1;
    head1->next = NULL;

    insert_node(head1,2);
    insert_node(head1,3);
    delete_node(head1,2);
    print_list(head1);
    return 0;
}
