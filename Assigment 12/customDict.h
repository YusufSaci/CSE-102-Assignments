
/* Defining a union to hold different types of values */
union Value{
    int val_int;
    float val_fl;
    double val_dl;
    char val_ch;
};

/* Defining a structure to represent an item in the dictionary */
struct item{
    char *key;
    char *dtype;
    int num_of_val;
    union Value *val;
};

/* Defining a structure to represent the custom dictionary */
struct CustomDict{
    struct item *dict_item;
    int size;
    int capacity;
};

/* Function to create a new dictionary */
struct CustomDict *create_dict(){

    struct CustomDict *dict=(struct CustomDict *)malloc(sizeof(struct CustomDict));
     if (dict == NULL) {
        return NULL;
     }
    dict->dict_item=NULL;
    dict->size=0;
    dict->capacity=0;

    return dict;
}

/* Function to load values into the union based on data type */
union Value * load_value( char *type, char *token[], int num ){
    int i;
    union Value *value;

        if(strcmp(type,"int")==0){
            value=(union Value *)malloc((num)*sizeof(union Value)); /* allocates memory for union value */
            for(i=0;i<num;i++){
                value[i].val_int=atoi(token[i]);/* assigns values ​​from array to union value */
            }

        }
            
        if(strcmp(type,"float")==0){
            value=(union Value *)malloc((num)*sizeof(union Value));  /* allocates memory for union value */
            for(i=0;i<num;i++){
                value[i].val_fl=atof(token[i]); /* assigns values ​​from array to union value */
            }
        }
            
        if(strcmp(type,"double")==0){
            value=(union Value *)malloc((num)*sizeof(union Value));  /* allocates memory for union value */
            for(i=0;i<num;i++){
                value[i].val_dl=atof(token[i]); /* assigns values ​​from array to union value */
            }
        }
            
        if(strcmp(type,"char")==0){
            value=(union Value *)malloc((num)*sizeof(union Value));  /* allocates memory for union value */
            for(i=0;i<num;i++){
                value[i].val_ch=token[i][1]; /* assigns values ​​from array to union value */
            }
        }
        return value; 
            
}

/* Function to print values based on data type */
void print_value(char *type,union Value *value, int num_of_val){
    int i=0;
    
        if(strcmp(type,"int")==0){
            for(i=0;i<num_of_val;i++){
                printf("%d ",value[i].val_int);
            }
        }
        if(strcmp(type,"float")==0){
            for(i=0;i<num_of_val;i++){
                printf("%.2f ",value[i].val_fl);
            }
        }
        if(strcmp(type,"double")==0){
           for(i=0;i<num_of_val;i++){
                printf("%.2lf ",value[i].val_dl);
            }
        }
        if(strcmp(type,"char")==0){
            for(i=0;i<num_of_val;i++){
                printf("%c ",value[i].val_ch);
            }
        }
       
}


/* Function to add an item to the dictionary */
void add_item(struct CustomDict* dict, char* key ,union Value* value, char* dtype, int num_of_val){

    int i,flag=1;
 
    /* If there is already an item with the specified key, just update its value.   */
    if(dict->dict_item!=NULL){
        for(i=0;i<dict->size;i++){
            if(strcmp(dict->dict_item[i].key,key)==0){
                dict->dict_item[i].val=value;
                dict->dict_item[i].num_of_val=num_of_val;
                flag=0;
            }
        }
    }

    
    if(flag){

        /* Allocate new space if capacity is reached.*/
        if(dict->size == dict->capacity){
          dict->dict_item=(struct item *)realloc(dict->dict_item,(dict->size+10)*sizeof(struct item));
          dict->capacity+=10;
        }

        /* Allocating memory for key and data type */
        dict->dict_item[dict->size].key=(char *)malloc(strlen(key+1) * sizeof(char));
        dict->dict_item[dict->size].dtype=(char *)malloc(strlen(dtype+1) * sizeof(char));

        /* Insert the values ​​received as parameters into the item*/
        strcpy(dict->dict_item[dict->size].key,key);
        strcpy(dict->dict_item[dict->size].dtype,dtype);
        dict->dict_item[dict->size].num_of_val=num_of_val;

        dict->dict_item[dict->size].val=value;

        (dict->size)++;
        
    }

}

/* Function to print the dictionary */
void print_dict(struct CustomDict* dict){
    int i,j;
    for(i=0;i<dict->size;i++){
        printf("%s: ",dict->dict_item[i].key);
       print_value(dict->dict_item[i].dtype,dict->dict_item[i].val,dict->dict_item[i].num_of_val);
        printf ("\n");
    }
}


/* Function to delete an item from the dictionary */
void delete_item(struct CustomDict* dict, char* key){
    int i,j;

    if(dict->dict_item!=NULL){
        for(i=0;i<dict->size;i++){
            if(strcmp(dict->dict_item[i].key,key)==0){

                 /* Freeing memory for key, data type, and value */
                free(dict->dict_item[i].key);
                free(dict->dict_item[i].dtype);
                free(dict->dict_item[i].val);

                 /* Shifting elements to fill the gap */
                for (j = i; j < dict->size - 1; j++) {
                    dict->dict_item[j] = dict->dict_item[j + 1];
                }
                 dict->size--;

                break;
            }
        }
    }
}

/* Function to set a new value for a key in the dictionary */
void set_value(struct CustomDict* dict, char* key, union Value* value, int num_of_val){

    int i;

     if(dict->dict_item!=NULL){
        for(i=0;i<dict->size;i++){
            if(strcmp(dict->dict_item[i].key,key)==0){ /* find the specified key*/
                dict->dict_item[i].val=value; /* update the value*/
                dict->dict_item[i].num_of_val=num_of_val;
                break;
            }
        }
    }
}

/* Function to sort the dictionary by keys */
void sort_dict(struct CustomDict* dict){
    struct item temp;
    int i,j;

    if(dict!=NULL){
          for(i=0;i<dict->size;i++){
              for(j=0;j<dict->size-i-1;j++){
                  if(strcmp(dict->dict_item[j].key,dict->dict_item[j+1].key)>0){
                      temp=dict->dict_item[j+1];
                      dict->dict_item[j+1]=dict->dict_item[j];
                      dict->dict_item[j]=temp;
                  }
              }
          }
      }

}

/* Function to read data from a CSV file and populate the dictionary */
int read_csv(struct CustomDict* dict, const char* filename){

    FILE *fileptr;
    union Value *value;
    char *token_type,*token_key,**token_value;
    char array[100];
    int num,i,j=0;
    

    fileptr=fopen(filename,"r");

    if(fileptr==NULL){
        return 0;
    }

    /* read the file line by line*/
   while(fgets(array,50,fileptr)){

        num=0;
        /* remove the trailing newline character*/
        for(i=0;array[i]!='\0';i++){
            if(array[i]==','){
                num++;
            }
            if(array[i]=='\n')
            array[i]='\0';
        };
        num--;

        token_type=strtok(array,","); /* save the datatype */
        token_key=strtok(NULL,",");/* save the key */

        /* remove the space at the beginning of the key */
        for(j=0;j<strlen(token_key)-1;j++){
            token_key[j]=token_key[j+1];
        }
        token_key[strlen(token_key)-1]='\0';

        token_value=(char **)malloc(num*sizeof(char *));

        /* save the value of each key */
        for(i=0;i<num;i++){
            token_value[i]=strtok(NULL,",");
           
        }
        
       value = load_value(token_type, token_value, num); /* assign values ​​to value union */

       add_item(dict,token_key,value,token_type,num);
        
    }
    fclose(fileptr);
    return 1;
    
}

/* Function to search for an item in the dictionary by its key and return the value of that item. */
union Value* search_item(struct CustomDict* dict, char* key, int *num){

    int i;

     if(dict->dict_item!=NULL){
        for(i=0;i<dict->size;i++){
            if(strcmp(dict->dict_item[i].key,key)==0){
                (*num)=dict->dict_item[i].num_of_val;
                return dict->dict_item[i].val;
                break;
            }
        }
    }

    return NULL;

}

/* Function to free memory allocated for the dictionary */
void free_dict(struct CustomDict* dict){

    int i,k;

    for(i=0;i<dict->size;i++){
        free(dict->dict_item[i].key);
        free(dict->dict_item[i].dtype);
        free(dict->dict_item[i].val);
    }
    free(dict->dict_item);
    free(dict);
}
