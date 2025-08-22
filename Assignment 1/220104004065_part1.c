#include<stdio.h>

/*Checks whether the received character is in the alphabet or not.*/
int check(char alphabet[61],char ch){
    int i;
    for(i=0;i<61;i++){
        if(ch==alphabet[i]){
            return 1;
        }
    }
    return 0;
}

/*Returns the order of the entered character in our alphabet.*/
int correspond(char alphabet[61],char ch){
    int i;
    for(i=0;i<61;i++){
        if(ch==alphabet[i]){
            return i;
        }
    }
    return 0;
}

/*Calculates key value according to student id*/
int find_key(long int student_id){

    int result=0,temp;

    while(student_id>0){
        result+=student_id%10;
        student_id/=10;
    }
    /* Performs addition until the sum of the digits of the number is less than 10 */
    while(result>9){
        temp=0;
        while(result>0){
            
            temp+=result%10;
            result/=10;
        }
        result=temp;
    }
    return result;
}

/*encrypts the code according to the calculated key value*/
char encrypt_code(char input_C,char alphabet[61],int key_value){
    
            if(check(alphabet,input_C)){
                /*It returns the encrypted version*/
                return alphabet[(correspond(alphabet,input_C)+key_value)%61];
                
            }
            else{
                return input_C;
            }
}

int main(void){
    
    char c; /* input variable*/
    long int student_id=220104004065;
    int key_value;
    int mode=0; /* comment status */
    int one=1;
    int counter=0,temp,num_digit,new,mod,j; /* Required variables to encrypt the number of characters in the comment */
    char alphabet[61] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 
    'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 
    '(', '<', '=', '+', ')', '[', '*', '/', ']', '{', '>', '!', '-', '}', '?', 
    '\\', '&', '|', '%', '_', ';', '"', '#','.', '\'', '0', '1', '2', '3', 
    '4', '5', '6', '7', '8', '9'};
    
    key_value=find_key(student_id);
    
    /* get input */
    while((scanf("%c",&c))==1){
    
        /* check comment status */
        if(mode==1){
            if(c=='*'){
               scanf("%c",&c);
                if(c=='/'){
                    mode=0;
                    printf("@ ");
                    temp=counter;
                    num_digit=0;
                    /* Calculates the number of digits of the comment length */
                    while(temp>0){
                        temp/=10;
                        num_digit++;
                    }
                    new=0;
                    /* Precaution for case where the last digit of the comment length is zero*/
                    counter=counter*10+1;
                    /* invert comment length */
                    for(j=0;j<=num_digit;j++){
                        mod=counter%10;
                        counter/=10;
                        new=new*10+mod;
                    }
                    /* Encrypt comment length step by step*/
                    while(new>=10){
                        mod=new%10;
                        new/=10;
                        printf("%c",encrypt_code(mod+'0',alphabet,key_value));
                    }
                    counter=0;
                }
                /* if not comment line, encrypt '*' character and next character*/
                else{
                    printf("%c",encrypt_code('*',alphabet,key_value));
                    printf("%c",encrypt_code(c,alphabet,key_value));
                }
            }
            else{
                /* calculates the comment length */
                if(c!=' ')
                counter++;
            }
        }
        /* indicating that we are in a comment line*/
        else if(c=='/'){
            scanf("%c",&c);
            if(c=='*'){
                mode=1;
            }
            /* if not comment line, encrypt '/' character and next character*/
            else{
                printf("%c",encrypt_code('/',alphabet,key_value));
                printf("%c",encrypt_code(c,alphabet,key_value));
            }
        }
        else{
            if(one==1){
                printf("Encrypted C code: \n\n");
                one=0;
            }
            /* printing encrypted characters */
            printf("%c",encrypt_code(c,alphabet,key_value));
        }
    }
return 0;
}

