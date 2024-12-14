#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Hospital {
    char *name;
    char cities_served[3];
};


struct Hospital *create_hospital(char *ename, int id,char locations[][3], int i) {
    struct Hospital *hos;
    int j;

    hos = (struct Hospital*)malloc(sizeof(struct Hospital));
    if (hos == NULL)  return NULL;
      
    hos->name = (char *)malloc((strlen(ename) + 5) * sizeof(char));
    if (hos->name == NULL)  return NULL;
    
    sprintf(hos->name, ename, id);
    
    for(j=0;j<3;j++){
            hos->cities_served[j]=locations[i][j];
    }

    return hos;
}

/* Checks whether the city has been saved before.*/
int check_city_array(char array[], char input,int num_of_city) {
    int i;

    for ( i = 0; i < num_of_city; i++) {
        if (array[i]==input) {
            return 1;
        }
    }
    return 0;
}

/* Save cities covered by hospitals.*/
int save_city(char arr[], char cities[], char input, int num_of_city) {
    int i,j;

    for ( i = 0; i < num_of_city; i++) {

        if (input==cities[i]) {
            if (check_city_array(arr, input,num_of_city) == 0){ /*Save if the city has not been saved before */
                for ( j = 0; j < num_of_city; j++) {

                    if (arr[j] == '\0') {
                        arr[j]=input;
                        break;
                    }
                }
                return 1;
            }
        }
    }
    return 0;
}

/* Checks whether the selected hospitals cover all cities.*/
int is_covered(struct Hospital **hospitals ,int arr[], char cities[], char locations[][3], int num_hos,int num_of_city, int start,int counter,char check_array[]) {
    int i,j,result;
    int original_city_counter = counter;
   
    /* Check that all cities are covered*/
    if(counter==num_of_city){
        return 1;
    }

    if(start==num_hos){
        return 0;
    }

    /* Determines the number of cities covered.*/
    for (j = 0; j < 3; j++) {
        if ( save_city(check_array, cities, locations[arr[start]][j],num_of_city) == 1) {
             counter++;
        }
    }
    
    result= is_covered(hospitals,arr, cities, locations, num_hos,num_of_city,start+1,counter,check_array);

    /* If all cities are covered, return 1.*/
    if (result) {
        return 1;
    }
    
    else{
        return is_covered(hospitals,arr, cities, locations, num_hos,num_of_city,start+1,original_city_counter,check_array);
    }
}

/* find the subset that its number of element as many as maximum number of hospitals.*/
int findSubsets(struct Hospital **hospitals,int arr[], int n, int subset[], int subset_size, int index, int num_hos, char cities[], char locations[][3],int num_of_city) {
    

    /*Check if the desired subset is found*/
    if (subset_size == num_hos) {
     
         char *check_array;
         int return_value,i;
    
         check_array=(char*)malloc(num_of_city*sizeof(char));/* Creating an array to record covered hospitals*/
        if (check_array == NULL)  return 0;

        for(i=0;i<num_of_city;i++){
            check_array[i]='\0';
        }

        return_value = is_covered(hospitals,subset, cities, locations, num_hos,num_of_city,0,0,check_array);
        free(check_array);
        
        return return_value;
    }

    if (index == n) {
        return 0;
    }

    subset[subset_size] = arr[index];/* create subset array */

    /*It creates all subclusters in a recursive manner.*/
    if (findSubsets(hospitals,arr, n, subset, subset_size + 1, index + 1, num_hos, cities, locations,num_of_city)) {
        return 1;
    }

    if (findSubsets(hospitals,arr, n, subset, subset_size, index + 1, num_hos, cities, locations,num_of_city)) {
        return 1;
    }

    return 0;
}

int main() {

    char cities[] = { 'A', 'B', 'C', 'D', 'E', 'F'};
    char locations[][3] = { {'A', 'B', 'C'}, {'A', 'C', 'D'}, {'B', 'F'} ,{'C', 'E', 'F'} };
    int *arr,i,j;
    int *subset;
    int num,num_of_city;

    num=sizeof(locations)/(3*sizeof(char)); /* Calculates the number of hospitals.*/
    num_of_city=sizeof(cities)/(sizeof(char)); /* calculates the number of cities.*/


    int num_hos;
    struct Hospital **hospitals;

    printf("\nEnter the maximum number of hospitals that can be constructed: ");
    scanf("%d", &num_hos);

    if(num_hos>num){
        printf("There are not that many hospitals\n");
        return 0;
    }

    arr=(int *)malloc(num*sizeof(int));
    if (arr == NULL)  return 0;
    subset=(int *)malloc(num*sizeof(int));
    if (subset == NULL)  return 0;

     for ( i = 0; i < num; i++) {
        arr[i] = i;
    }

    hospitals = (struct Hospital**)malloc(num * sizeof(struct Hospital*));
    if (hospitals == NULL)  return 0;

    for ( i = 0; i < num; i++) {
        hospitals[i] = create_hospital("Hospital - %d", i + 1,locations,i); /* assigns hospitals*/
    }

    if (findSubsets(hospitals,arr, num, subset, 0, 0, num_hos, cities, locations,num_of_city)) {
        printf("Yes,can offer health care to all!\n");

        /* Prints the cities covered by the selected hospitals.*/
         for(i=0;i<num_hos;i++){

            printf("\n%s\n",hospitals[subset[i]]->name);
            printf("hospital location: ");

            for(j=0;j<3;j++){
                printf("%c",hospitals[subset[i]]->cities_served[j]);
            }
        }
        printf("\n\n");
    }

    else {
        printf("No,some cities are not covered.\n\n");
    }
    
    /* clear memory*/
    for ( i = 0; i < num_hos; i++) {
        free(hospitals[i]->name);
        free(hospitals[i]);
    }
    
    free(arr);
    free(subset);
    free(hospitals);

    return 0;
}
