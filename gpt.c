#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRLEN 100

typedef struct stat_penyakit_t {
    char nama[STRLEN];
    int jumlah;
    struct stat_penyakit_t *next;
} StatPenyakit;

// Helper function to create a new node
StatPenyakit* newNode(const char* nama, int jumlah) {
    StatPenyakit* new_node = (StatPenyakit*)malloc(sizeof(StatPenyakit));
    strcpy(new_node->nama, nama);
    new_node->jumlah = jumlah;
    new_node->next = NULL;
    return new_node;
}

// Helper function to print the linked list
void printList(StatPenyakit* head) {
    StatPenyakit* temp = head;
    while (temp != NULL) {
        printf("Nama: %s, Jumlah: %d\n", temp->nama, temp->jumlah);
        temp = temp->next;
    }
}

// Comparator function for qsort
int compare(const void* a, const void* b) {
    int indexA = *(const int*)a;
    int indexB = *(const int*)b;
    return indexA - indexB;
}

// Function to sort the linked list
StatPenyakit* sortLinkedList(StatPenyakit* head) {
    // Step 1: Count the number of items in the list
    int count = 0;
    StatPenyakit* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }

    // Step 2: Create arrays for jumlah and nama
    int* jumlah = (int*)malloc(count * sizeof(int));
    char** nama = (char**)malloc(count * sizeof(char*));
    for (int i = 0; i < count; i++) {
        nama[i] = (char*)malloc(STRLEN * sizeof(char));
    }

    // Step 3: Populate the arrays
    current = head;
    for (int i = 0; i < count; i++) {
        jumlah[i] = current->jumlah;
        strcpy(nama[i], current->nama);
        current = current->next;
    }

    // Step 4: Sort the arrays using qsort
    for (int i = 0; i < count; i++) {
        for (int j = i + 1; j < count; j++) {
            if (jumlah[i] > jumlah[j]) {
                int temp_jumlah = jumlah[i];
                jumlah[i] = jumlah[j];
                jumlah[j] = temp_jumlah;

                char temp_nama[STRLEN];
                strcpy(temp_nama, nama[i]);
                strcpy(nama[i], nama[j]);
                strcpy(nama[j], temp_nama);
            }
        }
    }

    // Step 5: Reconstruct the linked list
    StatPenyakit* sorted_head = NULL;
    StatPenyakit* sorted_current = NULL;
    for (int i = 0; i < count; i++) {
        StatPenyakit* new_node = newNode(nama[i], jumlah[i]);
        if (sorted_head == NULL) {
            sorted_head = new_node;
            sorted_current = new_node;
        } else {
            sorted_current->next = new_node;
            sorted_current = new_node;
        }
    }

    // Free the temporary arrays
    for (int i = 0; i < count; i++) {
        free(nama[i]);
    }
    free(nama);
    free(jumlah);

    return sorted_head;
}

int main() {
    // Create example list
    StatPenyakit* head = newNode("PenyakitA", 5);
    head->next = newNode("PenyakitB", 3);
    head->next->next = newNode("PenyakitC", 9);
    head->next->next->next = newNode("PenyakitD", 1);
    head->next->next->next->next = newNode("PenyakitE", 8);

    printf("Original List:\n");
    printList(head);

    head = sortLinkedList(head);

    printf("\nSorted List:\n");
    printList(head);

    return 0;
}
