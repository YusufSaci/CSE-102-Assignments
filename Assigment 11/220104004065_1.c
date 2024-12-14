#include <stdio.h>

/* recursive function that returns the number of paths that can be used to return to 
the dispatch centre from the starting position specified by the user*/
int num_paths_home(int street, int avenue){
    
    if(street==1 || avenue==1){
        return 1;
    }

    return num_paths_home(street-1,avenue)+num_paths_home(street,avenue-1);

}

int main(){

    int street,avenue;

    printf("Enter the street number: ");
    scanf("%d",&street);
    printf("street: %d\n",street);

    printf("Enter the avenue number: ");
    scanf("%d",&avenue);
    printf("avenue: %d\n",avenue);

    printf("Number of optimal paths to take back home: %d\n",num_paths_home(street,avenue));

    return 0;
}