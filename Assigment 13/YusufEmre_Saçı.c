#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Definition of the menu structure */
typedef struct menu {
    char *class;
    char *order; 
    char *family;
    char *genus;
    char *species;
    struct menu* next;  /* Pointer to the next node in the linked list */
} menu;

/* Function to swap the contents of two menu structures */
void swap(menu *first, menu *second) {
    char *temp;

    /* Swap the 'class' field */
    temp = first->class;
    first->class = second->class;
    second->class = temp;

    /* Swap the 'order' field */
    temp = first->order;
    first->order = second->order;
    second->order = temp;

    /* Swap the 'family' field */
    temp = first->family;
    first->family = second->family;
    second->family = temp;

    /* Swap the 'genus' field */
    temp = first->genus;
    first->genus = second->genus;
    second->genus = temp;

    /* Swap the 'species' field */
    temp = first->species;
    first->species = second->species;
    second->species = temp;
}

/* Function to sort the linked list based on a specified criteria */
void sort_list(menu *list, char *arr) {
    int mode, flag;
    menu *temp;
    menu *last = NULL; /* Pointer to mark the end of the sorted section */

    /* Determine the sorting mode based on the input criteria */
    if (strcmp(arr, "class") == 0) mode = 1;
    if (strcmp(arr, "order") == 0) mode = 2;
    if (strcmp(arr, "family") == 0) mode = 3;
    if (strcmp(arr, "genus") == 0) mode = 4;
    if (strcmp(arr, "species") == 0) mode = 5;

    /* Bubble sort algorithm */
    do {
        temp = list;
        flag = 0;

        /* Iterate through the list and compare adjacent elements */
        while (temp->next != last) {
            switch (mode) {
                case 1: 
                    if (strcmp(temp->class, temp->next->class) > 0) swap(temp, temp->next);  
                    flag = 1; 
                    break;
                case 2: 
                    if (strcmp(temp->order, temp->next->order) > 0) swap(temp, temp->next);
                    flag = 1; 
                    break;
                case 3: 
                    if (strcmp(temp->family, temp->next->family) > 0) swap(temp, temp->next);
                    flag = 1; 
                    break;
                case 4: 
                    if (strcmp(temp->genus, temp->next->genus) > 0) swap(temp, temp->next); 
                    flag = 1;
                    break;
                case 5: 
                    if (strcmp(temp->species, temp->next->species) > 0) swap(temp, temp->next);
                    flag = 1; 
                    break;
            }
            temp = temp->next;
        }

        last = temp; /* Update the end of the sorted section */
    } while (flag);
}

/* Function to create a new item in the list */
menu *create_item(char cl[], char or[], char fa[], char ge[], char sp[]) {
    menu *new;
    new = (menu *)malloc(sizeof(menu));
    new->next = NULL;

    /* Allocate memory for each field and copy the input values */
    new->class = (char *)malloc((strlen(cl) + 1) * sizeof(char));
    new->order = (char *)malloc((strlen(or) + 1) * sizeof(char));
    new->family = (char *)malloc((strlen(fa) + 1) * sizeof(char));
    new->genus = (char *)malloc((strlen(ge) + 1) * sizeof(char));
    new->species = (char *)malloc((strlen(sp) + 1) * sizeof(char));

    strcpy(new->class, cl);
    strcpy(new->order, or);
    strcpy(new->family, fa);
    strcpy(new->genus, ge);
    strcpy(new->species, sp);

    return new;
}

/* Function to add a new item to the list */
menu *add_item(menu *list, char cl[], char or[], char fa[], char ge[], char sp[]) {
    menu *new = create_item(cl, or, fa, ge, sp);

    /* If the list is empty, the new item becomes the first item */
    if (list == NULL) {
        list = new;
    } else {
        menu *temp = list;
        /* Traverse to the end of the list and add the new item */
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new;
    }
    return list;
}

/* Function to modify an item in the list */
menu *modify_list(menu *l) {
    menu *temp = l;
    char array[50];
    char cl[50];
    char or[50];
    char fa[50];
    char ge[50];
    char sp[50];

    printf("Enter species information to modify:\n");
    printf("Old Species: ");
    fgets(array, 50, stdin);
    array[strlen(array) - 1] = '\0'; /* Remove newline character */
    printf("\nEnter new information: \n");

    printf("New Class: ");
    fgets(cl, 50, stdin);
    cl[strlen(cl) - 1] = '\0';

    printf("New Order: ");
    fgets(or, 50, stdin);
    or[strlen(or) - 1] = '\0';

    printf("New Family: ");
    fgets(fa, 50, stdin);
    fa[strlen(fa) - 1] = '\0';

    printf("New Genus: ");
    fgets(ge, 50, stdin);
    ge[strlen(ge) - 1] = '\0';

    printf("New Species: ");
    fgets(sp, 50, stdin);
    sp[strlen(sp) - 1] = '\0';

    /* Traverse the list to find the item to be modified */
    while (temp->next != NULL && strcmp(temp->species, array) != 0) {
        temp = temp->next;
    }

    if (temp != NULL) {
        /* Reallocate memory and update the item */
        temp->class = (char *)realloc(temp->class, (strlen(cl) + 1) * sizeof(char));
        temp->order = (char *)realloc(temp->order, (strlen(or) + 1) * sizeof(char));
        temp->family = (char *)realloc(temp->family, (strlen(fa) + 1) * sizeof(char));
        temp->genus = (char *)realloc(temp->genus, (strlen(ge) + 1) * sizeof(char));
        temp->species = (char *)realloc(temp->species, (strlen(sp) + 1) * sizeof(char));

        strcpy(temp->class, cl);
        strcpy(temp->order, or);
        strcpy(temp->family, fa);
        strcpy(temp->genus, ge);
        strcpy(temp->species, sp);
        printf("Species modified successfully.\n");
    } else {
        printf("Could not find information with the features you are looking for.\n");
    }

    return l;
}

/* Function to delete an item from the list */
menu *del_item(menu *l, char arr[]) {
    menu *cp, *bp;
    cp = bp = l;

    /* Traverse the list to find the item to be deleted */
    while (cp != NULL && strcmp(cp->species, arr) != 0) {
        bp = cp;
        cp = cp->next;
    }
    if (cp != NULL) {
        /* If the item to be deleted is the first item */
        if (cp == bp) l = cp->next;
        else bp->next = cp->next;

        /* Free the allocated memory */
        free(cp->class);
        free(cp->order);
        free(cp->family);
        free(cp->genus);
        free(cp->species);
        free(cp);
    }
    
    return l;
}

/* Function to free all memory associated with the list */
void free_menu(menu *l) {
    menu *temp;
    while (l != NULL) {
        temp = l;
        l = l->next;
        /* Free the allocated memory for each field */
        free(temp->class);
        free(temp->order);
        free(temp->family);
        free(temp->genus);
        free(temp->species);
        free(temp);
    }
}

/* Function to print the contents of the list */
void print_menu(menu *l) {
    menu *temp = l;
    if (l != NULL) {
        while (temp != NULL) {
            printf("Class: %s\n", temp->class);
            printf("Order: %s\n", temp->order);
            printf("Family: %s\n", temp->family);
            printf("Genus: %s\n", temp->genus);
            printf("Species: %s\n", temp->species);
            printf("\n\n");
            temp = temp->next;
        }
    }
}

/* Main function to provide a menu for user interaction */
int main() {
    menu *information = NULL;
    char cl[50];
    char or[50];
    char fa[50];
    char ge[50];
    char sp[50];
    char arr[50];
    int num;

    printf("************* MENU **************\n\n");
    printf("1-Add species to list.\n");
    printf("2-Print the list.\n");
    printf("3-Sort the list according to something.\n");
    printf("4-Modify the list.\n");
    printf("5-Delete all information of the selected species.\n");
    printf("6-Exit.\n");

    do {
        printf("------------------------------------------\n");
        printf("Choose: ");
        scanf("%d", &num);
        getchar(); /* Consume the newline character */
        printf("\n");

        switch (num) {
            case 1:
                printf("\nEnter species information: \n");
                printf("Class: ");
                fgets(cl, 50, stdin);
                cl[strlen(cl) - 1] = '\0';

                printf("Order: ");
                fgets(or, 50, stdin);
                or[strlen(or) - 1] = '\0';

                printf("Family: ");
                fgets(fa, 50, stdin);
                fa[strlen(fa) - 1] = '\0';

                printf("Genus: ");
                fgets(ge, 50, stdin);
                ge[strlen(ge) - 1] = '\0';

                printf("Species: ");
                fgets(sp, 50, stdin);
                sp[strlen(sp) - 1] = '\0';

                information = add_item(information, cl, or, fa, ge, sp);
                break;

            case 2:
                print_menu(information);
                break;

            case 3:
                printf("Enter list criteria (class, order, family, genus, species ): ");
                scanf("%s", arr);
                sort_list(information, arr);
                print_menu(information);
                break;

            case 4:
                information = modify_list(information);
                break;

            case 5:
                printf("Enter the species to delete: ");
                fgets(arr, 50, stdin);
                arr[strlen(arr) - 1] = '\0';
                information = del_item(information, arr);
                break;

             case 6:
                free_menu(information);
                return 0;
                break;

             default:
                printf("invalid input try again.\n");
                break;
        }

    } while (num != 6);

    

    return 0;
}
