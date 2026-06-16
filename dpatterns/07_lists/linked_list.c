/* Doubly Linked List implementation */
#include<stdio.h>
#include<stdlib.h>

struct Node  {
    int counter;
    struct Node* next;
    struct Node* prev;
};

/*  Pointer to head node. */
struct Node* head;

/*  Create a new Node   */
struct Node* create_node (int x) {
    struct Node* node =  (struct Node*)malloc(sizeof(struct Node));
    node->counter = x;
    node->prev = NULL;
    node->next = NULL;
    return node;
}


/*  Insert a Node at head of doubly linked list */
void push_front(int x) {
    struct Node* new_node = create_node(x);
    if(head == NULL) {
        head = new_node;
        return;
    }
        head->prev = new_node;
        new_node->next = head;
        head = new_node;
    }


/*  Insert a Node at tail of Doubly linked list */
void push_back(int x) {
    struct Node* temp = head;
    struct Node* new_node = create_node(x);
    if(head == NULL) {
        head = new_node;
        return;
    }
    while(temp->next != NULL) temp = temp->next; // Go To last Node
    temp->next = new_node;
    new_node->prev = temp;
}



/*  Print all the elements in linked list in forward order */
void print_forward() {
    struct Node* temp = head;
    printf("Forward: ");
    while(temp != NULL) {
        printf("%d ",temp->counter);
        temp = temp->next;
    }
    printf("\n");
}



/*  Prints all elements in linked list in reverse order */
void print_backward() {
    struct Node* temp = head;

    if(temp == NULL) return; // empty list, exit

    /* Going to last Node */
    while(temp->next != NULL) {
        temp = temp->next;
    }

    printf("Reverse: ");
    while(temp != NULL) {
        printf("%d ",temp->counter);
        temp = temp->prev;
    }
    printf("\n");
}

/*  Prints head and tail pointers  */
void print_pointers() {
    printf("Head: %p \n", head );
    printf("Head->next : %p \n", head->next );
    printf("Head->prev : %p \n", head->prev );
    printf("Head->counter : %d \n", head->counter );
    printf("Head->next->counter : %d \n", head->next->counter );
    printf("*******************\n \n");


    struct Node* temp = head;
    if(temp == NULL) return; // empty list, exit

    /* Going to last Node */
    while(temp->next != NULL) {
        temp = temp->next;
    }

    printf("Tail: %p \n", temp );
    printf("Tail->next : %p \n", temp->next );
    printf("Tail->prev : %p \n", temp->prev );
    printf("Tail->counter : %d \n", temp->counter );
    printf("Tail->prev->counter : %d \n", temp->prev->counter );
    printf("*******************\n \n");

}


int main() {

    head = NULL; // empty list. set head as NULL.

    /* Insert at back and print both directions */
    push_back(2);
    print_forward();
    print_backward();

    push_back(4);
    print_forward();
    print_backward();

    push_back(6);
    print_forward();
    print_backward();

    push_front(10);
    print_forward();
    print_backward();

    print_pointers();
    return 0;
}

