#include <stdio.h>
#include <string.h>

#define MAX_LINE 200
#define MAX_SIZE 256
#define MAX_BIT 9


typedef struct{

    char opcode[10];
    char type;
    char format[20];
    char explanation[70];

}instruction;

typedef struct {

    char memory[MAX_SIZE][MAX_BIT];
    int top;

}Stack;

/* Pushes data to stack.*/
void push(Stack *stack, char operation[]) {

    if (stack->top == MAX_SIZE - 1) {
        printf("Stack overflow!\n");
        return;
    }
    strcpy(stack->memory[++stack->top],operation);
}

/* Fills the stack with zeros.*/
void fill_stack(Stack *stack){
    int i;

    for(i=0;i<MAX_SIZE;i++){
        strcpy(stack->memory[i],"00000000");
    }

}


void initStack(Stack *stack) {
    stack->top = -1;
}

/* Converts decimal number to binary.*/
int to_binary(int decimal_number) {

    if (decimal_number == 0) {
        return 0;
    }
    else {
        return decimal_number % 2 + 10 * to_binary(decimal_number / 2);
    }
}


/* Converts binary number to decimal.*/
int to_decimal(char binary_number[]){

    int i,j,decimal=0,temp,size;
    size=strlen(binary_number)-1;

    for(i=size;i>=0;i--){

        temp=binary_number[i]-'0';

        for(j=0;j<size-i;j++){
            temp*=2;
        }
        decimal+=temp;
    }

    return decimal;
   
}


/* Reads data from file and stores it in sturct.*/
void file_to_struct(instruction instructions[], int n){

    FILE *fileptr;
    char *token;
    char temp[31][MAX_LINE];
    int i=0,j;

    fileptr=fopen("instructions.txt","r");

     while (fgets(temp[i],MAX_LINE,fileptr) != NULL) {
         i++;
         
     }

    /* Divides the data into pieces and stores each piece in the relevant place.*/
    for(i=0;i<n;i++){

        token=strtok(temp[i], "|");
        strcpy(instructions[i].opcode,token);
        

        token=strtok(NULL,"|");
        instructions[i].type=token[0];

        token=strtok(NULL,"|");
        strcpy(instructions[i].format,token);
        
        token=strtok(NULL,"|");
        strcpy(instructions[i].explanation,token);
        
    }
   

}

/* Finds the opcode using the instruction's format. */
int find_opcode(Stack *my_stack,instruction instructions[],char code[]){

    int idx=-1,i;
    char *token;
    char temp[20];
   
    for(i=0;(i<30 && idx==-1);i++){

        strcpy(temp,instructions[i].format);
        
        token=strtok(temp," ");
        
        if(strcmp(token,code)==0){
            idx=i;/* Save the index of the instruction.*/
        }
    }
    if(idx==-1){
        printf("invalid opcode.\n");
        return 0;
    }
    else
    push(my_stack,instructions[idx].opcode); /* Load opcode to memory.*/

    return 1;

}

/* Loads the data in .asm file to memory.*/
void load_memory(Stack *my_stack,char *token){

    char empty[]="00000000",binary[9];
    int decimal,num,i;

    switch(token[0]){

        case 'A':

            decimal=to_binary(MAX_SIZE-7);      /* Convert the address of the registry to binary.*/
            sprintf(binary, "%08d", decimal);
            push(my_stack,binary);      /* Load register to memory.*/
            break;
    
        case 'B':

            decimal=to_binary(MAX_SIZE-6);      /* Convert the address of the registry to binary.*/
            sprintf(binary, "%08d", decimal);
            push(my_stack,binary);          /* Load register to memory.*/
            break;
        
        case 'M':

            if(token[2]=='A'){

                decimal=to_binary(MAX_SIZE-7);    /* Convert the address of the registry to binary.*/
                sprintf(binary, "%08d", decimal);
                push(my_stack,binary);     /* Load register to memory.*/
            }
            else{
                decimal=to_binary(MAX_SIZE-6);    /* Convert the address of the registry to binary.*/
                 sprintf(binary, "%08d", decimal);
                 push(my_stack,binary);     /* Load register to memory.*/
            }
            break;

        default :
           num=0;

            /* Converts a number from char to int.*/
            for(i=0;i<strlen(token);i++){
                num*=10;
                num+=token[i]-'0';
            }
    
            decimal=to_binary(num);
            sprintf(binary, "%08d", decimal);
            push(my_stack,binary);/* push the number to memory.*/
            break;
    }

}

/* The program uploads the data at the location indicated by the counter into the IR.*/
void fetch(Stack my_stack,char *PC1,char *PC2,char *IR1,char *IR2,char *IR3){

    int i=0,decimal;
    char binary[17];

    strcpy(binary,PC2);
    strcat(binary,PC1);

    decimal=to_decimal(binary);

    strcpy(IR1,my_stack.memory[decimal]);
    strcpy(IR2,my_stack.memory[decimal+1]);
    strcpy(IR3,my_stack.memory[decimal+2]);

    decimal+=3; /* increase PC.*/
    decimal=to_binary(decimal);

    sprintf(binary, "%016d", decimal);
    strncpy(PC2,binary,8);
    PC2[8]='\0';
    strncpy(PC1,&binary[8],8);
    PC1[8]='\0';
    

}

/* it tries to understand what the data in the IR is.*/
void decode(char *IR1,char *IR2,char *IR3,char *reg1,char *reg2,int *num,int *which_op){

    int num1,num2,flag1=0,flag2=0;
    char temp[9],binary1[9],binary2[9];

    num1=to_binary(MAX_SIZE-7);
    sprintf(binary1, "%08d", num1);

    num2=to_binary(MAX_SIZE-6);
    sprintf(binary2, "%08d", num2);
 
    strcpy(temp,IR1);

    *which_op=to_decimal(temp); /* Understands which operation is happening*/

    strcpy(temp,IR2);

    /* Determines registers or numbers for second part of IR.*/
    if(strcmp(temp,binary1)==0){
        *reg1='A';
    }

    else if(strcmp(temp,binary2)==0){
        *reg1='B';
    }
    else {
        flag1=1;
        *num=to_decimal(temp);

    }

    strcpy(temp,IR3);
    
    /* Determines registers or numbers for third part of IR*/
    if(strcmp(temp,binary1)==0){
        *reg2='A';
    }

    else if(strcmp(temp,binary2)==0){
        *reg2='B';
    }
    else if(flag1!=1){
        flag2=1;
        *num=to_decimal(temp);

    }

}

/* implements the specified action */
int execute(Stack *my_stack,int which_op,char *A,char *B,char reg1,char reg2,int num,char *PC1,char *PC2){

    char binary[9],binary2[17];
    int num1,num2,i,n=0;
    char *reg_first;
    char *reg_second;

    if(reg1=='A')
        reg_first=A;
    
    else if(reg1=='B')
        reg_first=B;
    
    if(reg2=='A')
        reg_second=A;
    
    else if(reg2=='B')
        reg_second=B;
    
    /* implements the specified action.*/
    switch(which_op){
        /* It adds first and second register values then stores the result in first register.*/
         case 1:  
            num1=to_decimal(reg_first);
            num2=to_decimal(reg_second);
            num=num1+num2;
            num=to_binary(num);
            sprintf(reg_first,"%08d",num);
        break;

        /*It adds register first and given number then stores the result in first register.*/
        case 2:
            num1=to_decimal(reg_first);
            num=num1+num;
            num=to_binary(num);
            sprintf(reg_first,"%08d",num);
        break;

        /*It adds register first and a number that stored in memory address second register then stores the result in first register.*/
        case 3:
            num1=to_decimal(reg_first);
            num2=to_decimal(my_stack->memory[to_decimal(reg_second)]);
            num=num1+num2;
            num=to_binary(num);
            sprintf(reg_first,"%08d",num);
        break;

        /* It ands first and second register values then stores the result in first register.*/
        case 4:
            for (i = 0;i < 8;i++) {
                reg_first[i] &= reg_second[i];
             }
        break;

        /* It ands register first and given number then stores the result in first register.*/
        case 5:
             num=to_binary(num);
             sprintf(binary,"%08d",num);
             for (i = 0;i < 8;i++) {
                reg_first[i] &= binary[i];
             }
        break;
        
        /*It ands register first and a number that stored in memory address second register then stores the result in first register.*/
        case 6:
            strcpy(binary,my_stack->memory[to_decimal(reg_second)]);

            for (i = 0;i < 8;i++) {
                reg_first[i] &= binary[i];
             }
        break;

        /* It does or operation between register first and second, then stores the result in first register.*/
        case 7:
            for (i = 0;i < 8;i++) {
                reg_first[i] |= reg_second[i];
             }
        break;

        /* It does or operation between register first and given number, then stores the result in first register.*/
        case 8:
             num=to_binary(num);
             sprintf(binary,"%08d",num);
             for (i = 0;i < 8;i++) {
                reg_first[i] |= binary[i];
             }
        break;

        /*It does or operation between register first and the value inside the memory address second register, then stores the result in first register.*/
        case 9:
            strcpy(binary,my_stack->memory[to_decimal(reg_second)]);
        
            for (i = 0;i < 8;i++) {
                reg_first[i] |= binary[i];
            }
        break;

        /*It does subtraction operation between first and second registers, then stores the result in first register.*/
        case 10:
            num1=to_decimal(reg_first);
            num2=to_decimal(reg_second);
            num=num1 - num2;
            num=to_binary(num);
            sprintf(reg_first,"%08d",num);
        break;

        /*It does subtraction operation between register first and given number, then stores the result in first register.*/
        case 11:
             num1=to_decimal(reg_first);
             num=num1 - num;
             num=to_binary(num);
             sprintf(reg_first, "%08d", num);
        break;

        /*It does subtraction operation between register first and the value inside the memory address second register, then stores the result in first register.*/
        case 12:
            num1=to_decimal(reg_first);
            strcpy(binary,my_stack->memory[to_decimal(reg_second)]);
            num2=to_decimal(binary);

            num=num1 - num2;
            num=to_binary(num);
            sprintf(reg_first, "%08d", num);
        break;

        /*Increment first register by 1.*/
        case 13:
            num1=to_decimal(reg_first)+1;
            num=to_binary(num1);
            sprintf(reg_first,"%08d",num);
        break;

        /* Decrement second register by 1.*/
        case 14:
            num1=to_decimal(reg_first)-1;
            num=to_binary(num1);
            sprintf(reg_first,"%08d",num);
        break;
        
        /*Shift register first value to the left num times.*/
        case 15:
             num1=to_decimal(reg_first);
                 for(i=0;i<num;i++){
                    num1*=2;
                 }
            num1=to_binary(num1);
            sprintf(reg_first,"%08d",num1);
        break;

        /*Shift register first value to the rigth num times.*/
        case 16:
            num1 = to_decimal(reg_first);
            for ( i = 0; i < num; i++) {
                num1 /= 2;
            }
            num1 = to_binary(num1);
            sprintf(reg_first, "%08d", num1);
        break;

        /*Branch on line first register if first register and second register equal.*/
        case 17:
            if(strcmp(reg_first,reg_second)==0){
                num= (to_decimal(reg_first)-1)*3;
                if(num==-3){
                    num+=3;
                }
                num= to_binary(num);
                sprintf(binary2, "%016d", num);
                strncpy(PC2,binary2,8);
                PC2[8]='\0';
                strncpy(PC1,&binary2[8],8);
                PC1[8]='\0';
            }
        break;

        /* Branch on line first register if first register and second register not equal.*/
        case 18:
            if(strcmp(reg_first,reg_second)!=0){
                num= (to_decimal(reg_first)-1)*3;
                if(num==-3){
                    num+=3;
                }
                num= to_binary(num);
                sprintf(binary2, "%016d", num);
                strncpy(PC2,binary2,8);
                PC2[8]='\0';
                strncpy(PC1,&binary2[8],8);
                PC1[8]='\0';
            }
        break;
        /*Jump to specific line number which is first register + second register.*/
        case 19:
             num1 = to_decimal(reg_first);
             num2 = to_decimal(reg_second);
             num = (num1+num2-1)*3;
             if(num==-3){
                num+=3;
             }
             num=to_binary(num);
             sprintf(binary2, "%016d", num);
             strncpy(PC2,binary2,8);
             PC2[8]='\0';
             strncpy(PC1,&binary2[8],8);
             PC1[8]='\0';
        break;
        
        /*It does nor operation between register first and second, then stores the result in first register.*/
        case 20:
            num1=to_decimal(reg_first); num2=to_decimal(reg_second);
            num1=to_binary(num1); num2=to_binary(num2);
            if(num1>num2)
                num=num1;
            else
                num=num2;
            while(num>0){
                    num/=10;
                    n++;
                }
            for (i = 0; i < 8; i++) {
                reg_first[i] |= reg_second[i];
            }
            for (i = 7; i > 7-n; i--) {
                reg_first[i] = (!(reg_first[i]-'0')+'0');
            }
        break;

        /*t loads the value from memory address second register into register first.*/
        case 21:
            strcpy(reg_first,my_stack->memory[to_decimal(reg_second)]);
        break;

        /*It stores the value to memory address second register from register first.*/
        case 22:
            strcpy(my_stack->memory[to_decimal(reg_second)],reg_first);
        break;

        /*t swaps register first and second.*/
        case 23:
            strcpy(binary,reg_first);
            strcpy(reg_first,reg_second);
            strcpy(reg_second,binary);
        break;

        /*t checks whether first register is less than second register.*/
        case 24:
            num1=to_decimal(reg_first);
            num2=to_decimal(reg_second);
            if(num1<num2){
                strcpy(reg_first,"00000001");
            }
            else
                strcpy(reg_first,"00000000");
        break;

        /*It check whether first register is greater than second register.*/
        case 25:
            num1=to_decimal(reg_first);
            num2=to_decimal(reg_second);
            if(num1>num2){
                strcpy(reg_first,"00000001");
            }
            else
                strcpy(reg_first,"00000000");
        break;
                
        /*It prints the value of register first register. The value need to be converted to decimal number.*/
        case 26:
            num=to_decimal(reg_first);
            printf("Result of execution: %d\n",num);
        break;

        /*It prints the value of num. The value need to be converted to decimal number.*/
        case 27:
            printf("Result of execution: %d\n",num);
        break;

        /*It prints the value from memory address first register. The value need to be converted to decimal number.*/
        case 28:
            num=to_decimal(my_stack->memory[to_decimal(reg_first)]);
            printf("Resul of execution: %d\n",num);
        break;

        /*Load num value to first register*/
        case 29:
            num=to_binary(num);
            sprintf(reg_first, "%08d", num);
        break;
       
       /*It ends the program.*/
        case 30:
            return 0;
        break;

    }

    return 1;
    
}

/* Loads the data in the .asm file to memory .*/
int file_to_memory(char filename[],Stack *my_stack,instruction instructions[]){

    FILE *fileptr;
    char temp[30],line[30],*token;
    char empty[]="00000000";
    int num,i=0,flag;

    fileptr=fopen(filename,"r"); /* open the file.*/

    if(fileptr==NULL){
        printf("The file could not be opened.\n");
        return -1;
    }

    while((fgets(line,30,fileptr) != NULL)){    /* Reads data line by line*/

        if(line[strlen(line)-1]=='\n'){     /* remove the \n character.*/
            line[strlen(line)-1]='\0';
        }

        strcpy(temp,line);
        
 
        token=strtok(line," ");     /* Get the first part of the format*/
        
        if(token!=NULL){
        
            flag=find_opcode(my_stack,instructions,token);      /* find the opcode of first part.*/

            if(flag==0){
                return 0;
            }

            token=strtok(temp," ");
            token=strtok(NULL," ");  /* Get the second part of the format.*/
    
            if(token==NULL){
                push(my_stack,empty);
             }
            else{
                load_memory(my_stack,token);    /* Load the binary equivalent of the second part into memory */
            }
   
            token=strtok(NULL, " ");    /* Get the third part of the format.*/

            if(token==NULL){
                push(my_stack,empty);
             }
            else{
                load_memory(my_stack,token);    /* Load the binary equivalent of the third part into memory */
            }
        }
        
    }
    fclose(fileptr);
    return 1;
}


int main(){

    char *A,*B,reg1,reg2,*IR1,*IR2,*IR3,*PC1,*PC2;
    char file_name[30],line[30];
    int num,which_op,flag;

    instruction instructions[30];
    Stack my_stack;

    file_to_struct(instructions,30);

    /* Uses lower part of stack for registers, PC and IR*/
    A=my_stack.memory[MAX_SIZE-7];
    B=my_stack.memory[MAX_SIZE-6];
    PC1=my_stack.memory[MAX_SIZE-5];
    PC2=my_stack.memory[MAX_SIZE-4];
    IR1=my_stack.memory[MAX_SIZE-3];
    IR2=my_stack.memory[MAX_SIZE-2];
    IR3=my_stack.memory[MAX_SIZE-1];
   
  do{

    printf("Enter a file name: ");
    scanf("%s",file_name);

    initStack(&my_stack);
    fill_stack(&my_stack);
    flag=file_to_memory(file_name,&my_stack,instructions);

    if(flag==0 || flag==-1){
        return 0;
    }

    strcpy(my_stack.memory[100],"00000101");
    strcpy(my_stack.memory[101],"00000110");

    /* operations are performed sequentially */
    do{

        fetch(my_stack,PC1,PC2,IR1,IR2,IR3);
        decode(IR1,IR2,IR3,&reg1,&reg2,&num,&which_op);
    
    }while(execute(&my_stack,which_op,A,B,reg1,reg2,num,PC1,PC2));

    do{
        printf("Do you want to execute another assembly code: press (1) for yes,press (0) for exit: ");
        scanf("%d",&num);
        if(num!=0 && num!=1){
            printf("invalid input.\n");
        }
        
    }while(num!=0 && num!=1);

  }while(num==1);

   return 0;
}

