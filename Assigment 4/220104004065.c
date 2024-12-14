#include <stdio.h>

/* function returning the initial letter of the person’s first name. */
char first_initial(FILE* id_fp, int id){
    int file_id;
    char file_ch;
    id_fp = fopen("second.txt","r");
    
    while((fscanf(id_fp,"%d",&file_id))==1){ /* Reads the student's ID */
        if(id==file_id){
            fscanf(id_fp,"%c",&file_ch); /* Reads the semicolon after the id */
            fscanf(id_fp,"%c",&file_ch); /* Reads the initial letter of the person’s first name.*/
            fclose(id_fp);
            return file_ch;
        }
        /* If id is not equal, reads until the end of the line*/
        else{
            while(fscanf(id_fp,"%c",&file_ch)==1 && file_ch!='\n'){}
        }
    }
    fclose(id_fp);
    return 0;
}

/* function returning the initial letter of the person’s last name. */
char last_initial(FILE* id_fp, int id){
    int file_id;
    char file_ch;
    id_fp = fopen("second.txt","r");
    
    while((fscanf(id_fp,"%d",&file_id))==1){  /* Reads the student's ID */
        if(id==file_id){
            fscanf(id_fp,"%c",&file_ch); /* Reads the semicolon after the id */
            while(fscanf(id_fp,"%c",&file_ch)==1 && file_ch!=';'){}  /* Reads up to the second semicolon after the ID */
            fscanf(id_fp,"%c",&file_ch); /* Reads the initial letter of the person’s last name.*/
            fclose(id_fp);
            return file_ch;
        }
        /* If id is not equal, reads until the end of the line*/
        else{
            while(fscanf(id_fp,"%c",&file_ch)==1 && file_ch!='\n'){}
        }
    }
    fclose(id_fp);
    return 0;
}
/* Returns the id of a person given the first initial. */
int get_id_fi(FILE* id_fp, char first_initial){
    char file_ch;
    int file_id;
    
    while((fscanf(id_fp,"%d",&file_id))==1){; /* Reads the student's ID */
        fscanf(id_fp,"%c",&file_ch); /* Reads the semicolon after the id */
        fscanf(id_fp,"%c",&file_ch); /* Reads the initial letter of the person’s first name.*/
        /* If file_ch is equal, reads until the end of the line and then return the id*/
        if(file_ch==first_initial){
            while(fscanf(id_fp,"%c",&file_ch)==1 && file_ch!='\n'){}
            return file_id;
        }
        while(fscanf(id_fp,"%c",&file_ch)==1 && file_ch!='\n'){} /* Only reads until the end of line */
    }
    return 0;
}
/* Returns the id of a person given the last initial. */
int get_id_li(FILE* id_fp, char last_initial){
    char file_ch;
    int file_id;
    
    while((fscanf(id_fp,"%d",&file_id))==1){ /* Reads the student's ID */
        fscanf(id_fp,"%c",&file_ch);/* Reads the semicolon after the id */
        while(fscanf(id_fp,"%c",&file_ch)==1 && file_ch!=';'){}  /* Reads up to the second semicolon after the ID */
        fscanf(id_fp,"%c",&file_ch); /* Reads the initial letter of the person’s last name.*/
        /* If file_ch is equal, reads until the end of the line and then return the id*/
        if(file_ch==last_initial){
            while(fscanf(id_fp,"%c",&file_ch)==1 && file_ch!='\n'){}
            return file_id;
        }
        while(fscanf(id_fp,"%c",&file_ch)==1 && file_ch!='\n'){} /* Only reads until the end of line */
    }
    return 0;
}
/* Returns the student ID from the beginning to the end of the file */
int only_get_id(FILE *id_fp){
    char file_ch;
    int file_id;
    
    while((fscanf(id_fp,"%d",&file_id))==1){ /* Reads the student's ID */
        while(fscanf(id_fp,"%c",&file_ch)==1 && file_ch!='\n'){}   /*reads until the end of the line and then return the id*/
            return file_id;
    }
    return 0;
}
/* Returns the IDs of people belonging to the requested role. */
int get_id_role(FILE* id_fp, char role_initial){
    char file_ch;
    int file_id,counter_semicolon;
    
    while((fscanf(id_fp,"%d",&file_id))==1){ /* Reads the student's ID */
        counter_semicolon=0;
        /* Read until the semicolon before the role */
        do{
            fscanf(id_fp,"%c",&file_ch);
            if(file_ch==';'){
                counter_semicolon++;
            }
        }while(counter_semicolon!=3);
       
        fscanf(id_fp,"%c",&file_ch); /* Reads the initial letter of the role */
        /* If file_ch is equal, reads until the end of the line and then return the id*/
        if(file_ch==role_initial){
            while(fscanf(id_fp,"%c",&file_ch)==1 && file_ch!='\n'){}
            return file_id;
        }
        while(fscanf(id_fp,"%c",&file_ch)==1 && file_ch!='\n'){} /* Only reads until the end of line */
    }
    return 0;
}
/* Returns the information of the people in the first txt file according to the which parameter and student id .*/
/* corresponding which values ​​1- midterm grade 2- final grade 3- course id 4- classes 5- department*/
float all_data(FILE *info_fp,int student_id,int which){
   
    int counter_semicolon=0,id,course_id,classes,department;
    int midterm1=0,midterm2=0,final=0;;
    float midterm_average=0,result=0;
    char file_ch,semicolon;
    
    FILE* test;
    info_fp = fopen("first.txt","r");
    test = fopen("first.txt","r");
    /* Counts how many semicolons are in each line*/
    while((fscanf(info_fp,"%c",&file_ch))==1){
        counter_semicolon=0;
        while(fscanf(info_fp,"%c",&file_ch)==1 && file_ch!='\n'){
            if(file_ch==';'){
                counter_semicolon++;
            }
        }
        /* If the number of semicolons is 4, the student has 2 midterm grades and takes action accordingly.*/
        if(counter_semicolon==4){
            /*reads all information in the line  */
            fscanf(test,"%d %c %d %c %d %c %d %c %d",&id,&semicolon,&midterm1,&semicolon,&midterm2,&semicolon,&final,&semicolon,&course_id);
            /* If the ids are equal, it returns the requested information. */
            if(id==student_id){
                switch(which){
                    case 1: result = midterm_average=(float)(midterm1+midterm2)/2;  break;
                    case 2:  result = final; break;
                    case 3:  result = course_id; break;
                    default: result = 0; break;
                }
            }
        }
        /* If the number of semicolons is 3, the student has 1 midterm grades and takes action accordingly.*/
        else if(counter_semicolon==3){
            /*reads all information in the line  */
            fscanf(test,"%d %c %d %c %d %c %d",&id,&semicolon,&midterm1,&semicolon,&final,&semicolon,&course_id);
            /* If the ids are equal, it returns the requested information. */
            if(id==student_id){
                switch(which){
                    case 1:  result = midterm1;  break;
                    case 2:  result =final; break;
                    case 3:  result = course_id; break;
                    default: result = 0; break;
                }
            }
        }
        /* If the number of semicolons is 2, that means this person is an instructor .*/
        else if(counter_semicolon==2){
            /*reads all information in the line  */
            fscanf(test,"%d %c %d %c %d ",&id,&semicolon,&classes,&semicolon,&department);
            /* If the ids are equal, it returns the requested information. */
            if(id==student_id){
                switch(which){
                    case 4: result = classes; break;
                    case 5: result = department;  break;
                    default: result = 0; break;
                }
            }
        }
    }
    fclose(info_fp);
    fclose(test);
    return result;
}
/* Calculates the midterm and final averages for the relevant course */
void course_avarage(int course_id,float *all_midterm,float *all_final){
    int counter_semicolon=0,id,file_course_id;
    int midterm1=0,midterm2=0,final=0;;
    int student_counter=0,flag=1;
    char file_ch,semicolon;
    
    FILE* info_fp;
    FILE* test;
    
    info_fp = fopen("first.txt","r");
    test = fopen("first.txt","r");
    *all_final=*all_midterm=0;
    /* Calculates the number of semicolons*/
    while((fscanf(info_fp,"%c",&file_ch))==1 && flag==1){
        counter_semicolon=0;
        while(fscanf(info_fp,"%c",&file_ch)==1 && file_ch!='\n'){
            if(file_ch==';'){
                counter_semicolon++;
            }
        }
        /* If the number of semicolons is 4, the student has 2 midterm grades and takes action accordingly.*/
        if(counter_semicolon==4){
            fscanf(test,"%d %c %d %c %d %c %d %c %d",&id,&semicolon,&midterm1,&semicolon,&midterm2,&semicolon,&final,&semicolon,&file_course_id);
            /* Finds the sum of all midterm and final grades for the relevant course.*/
            if(file_course_id==course_id){
                student_counter++;
                *all_midterm+=(float)(midterm1+midterm2)/2;
                *all_final+=final;
            }
        }
        /* If the number of semicolons is 4, the student has 2 midterm grades and takes action accordingly.*/
        else if(counter_semicolon==3){
            fscanf(test,"%d %c %d %c %d %c %d",&id,&semicolon,&midterm1,&semicolon,&final,&semicolon,&file_course_id);
            /* Finds the sum of all midterm and final grades for the relevant course.*/
            if(file_course_id==course_id){
                student_counter++;
                *all_midterm+=midterm1;
                *all_final+=final;
            }
        }
        /* If the person is not a student, the function terminates. */
        else
            flag=0;
    }
    /* The average is calculated by dividing the totals by the number of people. */
    *all_midterm=(float)*all_midterm/student_counter;
    *all_final=(float)*all_final/student_counter;
    fclose(test);
    fclose(info_fp);
}

/* Calculates students' letter grades based on the course average */
void letter_grade(FILE *info_fp, int id,char *midterm_letter, char *final_letter){
    int course_id;
    float student_midterm=0,student_final=0;
    float course_midterm_average,course_final_average;
    info_fp = fopen("first.txt","r");
    
    course_id=all_data(info_fp,id,3);
    student_midterm=all_data(info_fp,id,1);
    student_final=all_data(info_fp,id,2);
   
    course_avarage(course_id,&course_midterm_average,&course_final_average); /* class average is calculated */
    /* By making comparisons, the student's midterm letter grade is determined. */
    if(student_midterm>=90)
        *midterm_letter='A';
    else if(student_midterm<90 && student_midterm > course_midterm_average)
        *midterm_letter='B';
    else if(student_midterm>=40 && student_midterm > course_midterm_average)
        *midterm_letter='C';
    else if(student_midterm>40 && student_midterm < course_midterm_average)
        *midterm_letter='D';
    else if((student_midterm<40 && student_midterm < course_midterm_average))
        *midterm_letter='F';

    /* By making comparisons, the student's final letter grade is determined. */
    if(student_final>=90)
        *final_letter='A';
    else if(student_final<90 && student_final > course_final_average)
        *final_letter='B';
    else if(student_final>=40 && student_final > course_final_average)
        *final_letter='C';
    else if(student_final>40 && student_final < course_final_average)
        *final_letter='D';
    else if((student_final<40 && student_final < course_final_average))
        *final_letter='F';

    fclose(info_fp);
}
/* Returns the appropriate GPA according to the students' calculated letter grades.*/
int average_grade(FILE *info_fp, int id){
   
    char midterm_letter,final_letter;
    float midterm_gpa,final_gpa,total_gpa;
    int int_gpa;
    letter_grade(info_fp, id,&midterm_letter,&final_letter);
    
    switch (midterm_letter) {
        case 'F': midterm_gpa=1.0; break;
        case 'D': midterm_gpa=2.5; break;
        case 'C': midterm_gpa=3.0; break;
        case 'B': midterm_gpa=3.5; break;
        case 'A': midterm_gpa=4.0; break;
    }
    switch (final_letter) {
        case 'F': final_gpa=1.0; break;
        case 'D': final_gpa=2.5; break;
        case 'C': final_gpa=3.0; break;
        case 'B': final_gpa=3.5; break;
        case 'A': final_gpa=4.0; break;
    }
    total_gpa=(final_gpa+midterm_gpa)/2; /* The common GPA of the midterm and  final is calculated */
    if(total_gpa>1 && total_gpa <2.5)
        total_gpa=2.5;
    if(total_gpa>2.5 && total_gpa <3.0)
        total_gpa=3.0;
    if(total_gpa>3 && total_gpa <3.5)
        total_gpa=3.5;
    if(total_gpa>3.5 && total_gpa <4.0)
        total_gpa=4.0;
    
    int_gpa=total_gpa*10;
    return int_gpa;
}
/* Calculates the student's letter grade, which is the midterm and final result */
char letter(FILE* info_fp,int id){
    int gpa;
    char ch;
    gpa=average_grade(info_fp,id);
    switch (gpa) {
        case 10:  ch='F'; break;
        case 25:  ch='D'; break;
        case 30:  ch='C'; break;
        case 35:  ch='B'; break;
        case 40:  ch='A'; break;
    }
    return ch;
}
/* Finds the person's department */
int find_department( FILE* id_fp,int id){
    int file_id;
    int counter_semicolon=0;
    char file_ch;
    int departmant=0;
    id_fp = fopen("second.txt","r");
    while((fscanf(id_fp,"%d",&file_id))==1){ /* Read the persons ID */
        if(file_id==id){
            counter_semicolon=0;
            /* Reads up to the semicolon before the department */
            do{
                fscanf(id_fp,"%c",&file_ch);
                if(file_ch==';'){
                    counter_semicolon++;
                }
            }while(counter_semicolon!=4);
                fscanf(id_fp,"%d",&file_id); /* reads the department */
                departmant=file_id;
            }
        /* If id is not equal, reads until the end of the line*/
        else{
            while(fscanf(id_fp,"%c",&file_ch)==1 && file_ch!='\n'){}
        }
    }
    fclose(id_fp);
    return departmant;
}

int main() {
    char ch,initial;
    int i,id,check=0,grade,course_id=0;
    float midterm,final;
    FILE* id_fp;
    FILE* info_fp;
    id_fp = fopen("second.txt","r");
    if(!id_fp){
        printf("file could not open");
        return 0;
    }
    info_fp = fopen("first.txt","r");
    if(!info_fp){
        printf("file could not open");
        return 0;
    }
 
    printf("\n********************* MENU ************************\n");
    printf("'p': Print all the users pass or fail.\n");
    printf("'n': Print only the user with a specific first initial.\n");
    printf("'g': Calculate the GPA of a given student.\n");
    printf("'c': Print whether each user passed or failed the same class.\n");
    printf("'t': Print the number of classes for the instructor.\n");
    printf("'d': Print the department of all persons according to the role.\n");
    printf("'l': Print the course_id of a given student.\n");
    printf("'e': Quit the program.\n");
    
    while(1){
        printf("\n---------------------------------------------\n");
        printf("\nEnter the choice: ");
        scanf(" %c",&ch);
        /* Performs the relevant action according to the option */
        switch(ch){
            case 'p':
                id_fp = fopen("second.txt","r");
                info_fp = fopen("first.txt","r");
                course_avarage(102,&midterm,&final);  /* Calculates the midterm and final average of the course 102 */
                printf("\nCourse 102 midterm average %.2f , final average %.2f\n",midterm,final);
                printf("\nSTUDENT ID | COURSE ID | LETTER GRADE | STATUS \n");
                printf("---------- | --------- | ------------ | ------ \n");
                /*reads the students' IDs one by one and prints the student IDs of the students whose course IDs are equal to 102, their course IDs, their letter grades and whether they pass.*/
                do{
                    id=only_get_id(id_fp);
                    if(id!=0){
                        course_id=all_data(info_fp,id,3);
                        if(course_id==102){
                            printf("%d      %d            %c         ",id,course_id,letter(info_fp,id));
                            grade=average_grade(info_fp,id); /* Calculates the gpa of the student */
                            /* If it is equal to 10, that is, the letter grade F, it fails, otherwise it passes. */
                            if(grade==10)
                                printf("FAIL\n");
                            else
                                printf("PASS\n");
                        }
                    }
                }while(id && course_id!=0);
                fclose(id_fp);
                fclose(info_fp);
                id_fp = fopen("second.txt","r");
                course_avarage(108,&midterm,&final); /* Calculates the midterm and final average of the course 108 */
                printf("\nCourse 108 midterm average %.2f , final average %.2f\n",midterm,final);
                printf("\nSTUDENT ID | COURSE ID | LETTER GRADE | STATUS \n");
                printf("---------- | --------- | ------------ | ------ \n");
                /*reads the students' IDs one by one and prints the student IDs of the students whose course IDs are equal to 108, their course IDs, their letter grades and whether they pass.*/
                do{
                    id=only_get_id(id_fp);
                    if(id!=0){
                        course_id=all_data(info_fp,id,3);
                        if(course_id==108){
                            printf("%d      %d            %c         ",id,course_id,letter(info_fp,id));
                            grade=average_grade(info_fp,id); /* Calculates the gpa of the student */
                            /* If it is equal to 10, that is, the letter grade F, it fails, otherwise it passes. */
                            if(grade==10)
                                printf("FAIL\n");
                            else
                                printf("PASS\n");}
                    }
                }while(id && course_id!=0);
                fclose(id_fp);
                break;
            case 'n':
                id_fp = fopen("second.txt","r");
                printf("Enter a letter for the initial(first name): ");
                scanf(" %c",&initial);
                printf("\nSTUDENT ID | COURSE ID | LETTER GRADE | STATUS \n");
                printf("---------- | --------- | ------------ | ------ \n");
                /* It finds the IDs of the students whose first letter is taken and prints their IDs, course IDs, letter grades and whether they passed or not. */
                do{
                    id=get_id_fi(id_fp,initial); /*Finds the ID of the student whose first letter is entered. */
                    if(id!=0){
                        course_id=all_data(info_fp,id,3);
                        if(course_id==0){
                            break;
                        }
                        printf("%d      %d            %c         ",id,course_id,letter(info_fp,id));
                        grade=average_grade(info_fp,id); /* Calculates the gpa of the student */
                        /* If it is equal to 10, that is, the letter grade F, it fails, otherwise it passes. */
                        if(grade==10)
                            printf("FAIL\n");
                        else
                            printf("PASS\n");
                    }
                }while(id);
                fclose(id_fp);
                break;
            case 'c':
                id_fp = fopen("second.txt","r");
                printf("Enter a course id: ");
                scanf("%d",&course_id);
                course_avarage(course_id,&midterm,&final);
                printf("course midterm average %.2f , final average %.2f\n",midterm,final);
                printf("\nSTUDENT ID | COURSE ID  | STATUS \n");
                printf("---------- | ---------  | ------ \n");
                /* Prints whether the students with the taken course ID have passed or not. */
                do{
                    id=only_get_id(id_fp);
                    if(id!=0){
                        check=all_data(info_fp,id,3);
                        if(check==course_id){
                            printf("%d     %d         ",id,course_id);
                            grade=average_grade(info_fp,id); /* Calculates the gpa of the student */
                            /* If it is equal to 10, that is, the letter grade F, it fails, otherwise it passes. */
                            if(grade==10)
                                printf("FAIL\n");
                            else
                                printf("PASS\n");
                        }
                    }
                }while(id && check!=0);
                fclose(id_fp);
                break;
            case 'g':
                printf("Enter id for student GPA: ");
                scanf(" %d",&id);
                printf("\nSTUDENT ID | GPA  \n");
                printf("---------- | ---- \n");
                printf("%d    %.2f\n",id,(float)average_grade(info_fp,id)/10); /* Prints the GPA of the student whose ID is received */
                break;
            case 't':
                printf("Enter id for number of classes for the instructor: ");
                scanf(" %d",&id);
                printf("\nINSTRUCTOR ID | NUM OF CLASSES  \n");
                printf("------------- | --------------- \n");
                printf("%d              %.0f\n",id,all_data(info_fp,id,4)); /* Prints the number of courses of the instructor with the id taken */
                break;
            case 'd':
                id_fp = fopen("second.txt","r");
                printf("Enter a letter for the initial (role): ");
                scanf(" %c",&initial);
                printf("\nPERSON ID | DEPARTMENT \n");
                printf("--------- | ---------- \n");
                /* It prints the department and id of the students who have the initial letter of the role taken. */
                do{
                    i=get_id_role(id_fp,initial);
                    if(i!=0){
                        printf("%d     %d\n",i,find_department(id_fp,i));
                    }
                }while(i);
                fclose(id_fp);
                break;
            case 'l':
                printf("Enter id for course id: ");
                scanf(" %d",&id);
                check=all_data(info_fp,id,3); /* If the check is 0, that person is not a student */
                if(check!=0){
                    printf("\nSTUDENT ID | COURSE ID  \n");
                    printf("---------- | ---------- \n");
                    printf("%d      %.0f\n",id,all_data(info_fp,id,3)); /* prints the id and course id of the student with the received id */
                }
                else
                    printf("person is no student.\n");
                break;
            case 'e':
                printf("Program terminated\n");
                return 0;
            default:
                printf("invalid choice.\n");
                break;
        }
    }
    return 0;
}
