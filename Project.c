# include <stdio.h>
# include <string.h>
# include <stdlib.h>

long int select_choice,Total=0;
char first_name[20],last_name[20],email[50],password_1[50],password_2[50],contact_no[20];

void login();
void signup();
int validation();
void Shop();
void Fashion();
void Electronics();
void Cart();

int main() {
    printf("--------Welcome to Online Shopping Site------\n\n");
    printf("--------Select from the following Options-----\n\n\n");   //Selecting the task
    printf("1.  Login (if you already signed up)\n");
    printf("2.  Signup (if you are a new customer)\n");
    printf("3.  Exit\n\n=>");

    scanf("%d",&select_choice);

    switch(select_choice)
    {
        case 1:
        login();
        break;

        case 2:
        signup();
        break;

        case 3:
        printf("\nThank You for Visiting.\n");
        printf("Have a Nice Day\n");
        break;

        default:
        printf("\nInvalid Entry !\n");
    }
    return 0;
}

int validation()
{
    int flag;

    Email:
    printf("Email = ");         //Entering the email of the user.
    scanf("\n");
    gets(email);
    flag=1;
    
    if(strlen(email)!=0)          //checking the valid expression of email.
    {
        int i=0, at_1=0, dot_1=0, j=0;
        while(i<strlen(email))
        {
            if(email[i]>='A' || email[i]<='Z' || email[i]>='a' ||email[i]<='z'||email[i]=='@'||email[i]=='.'||email[i]>='0'||email[i]<='9')
            {                     
                if(email[i]=='@')  // checking the presence of alphabets, digits, an at and a dot in email.        
                {
                    at_1++;
                }
                else if(email[i]=='.')
                {
                    dot_1++;
                }
                flag=1;
            }
            else
            {
                flag=0;
                printf("Invalid Email !\n\n");
                goto Email;
            }
            i++;
        }
        if(at_1==1 && dot_1==1)
        {
            flag=1;
        }
        else
        {
            flag=0;
            printf("Invalid Email !\n\n");
            goto Email;
        }

        int at_2=0, dot_2=0;
        while(j<strlen(email))
        {                           // Checking that @ is present before the dot(.) in email.
            if(email[j]=='@')
            {
                at_2=j;
            }
            else if(email[j]=='.')
            {
                dot_2=j;
            }
            j++;
        }
        if(at_2 > dot_2)
        {
            printf("Invalid email !\n\n");
            goto Email;
        }
    }
    else
    {
        printf("No email address found!\n\n");
        goto Email;
    }

    Password:
    printf("Password = ");            //Entering password
    scanf("\n");
    gets(password_1);
    printf("Confirm Password = ");   //Entering confirm password
    scanf("\n");
    gets(password_2);
    flag=1;

    int lower=0, upper=0, special=0, digit=0;
    if(password_1!='\0' || password_2!='\0')              //whether any of the password is not entered.
    {
        if(strcmp(password_1,password_2)==0)              // if password and confirmed password are not same.
        {
            flag=1;
        }
        else
        {
            flag=0;
            printf("Confirmed Password didin't matched the Password !\n\n");      
            goto Password;
        }  
        for(int i=0;i<strlen(password_1);i++)                     
        {                                                                 //checking the correct format for a strong password.
            if(password_1[i]>=' ' && password_1[i]<'~')                   // condition for any special case letter.
            {
                if(password_1[i]>='A' && password_1[i]<='Z')              //condition for upper case letter.
                {
                    upper++;
                }
                else if(password_1[i]>='a' && password_1[i]<='z')         //condition for lower case letter.
                {
                    lower++;
                }
                else if(password_1[i]>='0' && password_1[i]<='9')         //condition for numerical.
                {
                    digit++;
                }
                else                                                      
                {
                    special++;
                }
            }
            else
            {
                flag=0;
                printf("Invalid Password !\n\n");
                goto Password;
            }
        }
    }
    
    else
    {
        printf("Password not found !\n\n");
        goto Password;
    }

    if(upper==0 || lower==0 || digit==0 || special==0)
    {
        flag=0;
        printf("Invalid Password Format!\n\n");
        goto Password;
    }
    


    FILE *fptr_1;
    fptr_1 = fopen("Email_data.txt","r");            //Checking the presence of account in the backend data, entered by the user.
    flag=1;
    int count_1 = 0;

    for(int i=0;email[i]!='\0';i++)
    {
        if(flag==0)
        {
            fscanf(fptr_1,"\n");
            i=0;
            count_1++;
        }
        char ch_email = fgetc(fptr_1);

        if(ch_email==EOF)
        {
            flag=0;
            break;
        }
        else
        {
            if(email[i]==ch_email)
            {
                flag=1;
            }
            else
            {
                flag=0;
            }
        }
    }
    fclose(fptr_1);

    int flag_new=1;
    FILE *fptr_2;
    fptr_2 = fopen("Password_data.txt","r");
    int count_2 = 0;

    for(int i=0;password_1[i]!='\0';i++)              //Checking the presence of password registered with the respected email address.
    {
        if(flag_new==0)
        {
            i=0;
            count_2++;
        }
        char ch_password = fgetc(fptr_2);
        
        if(ch_password==EOF)
        {
            flag_new=0;
            break;
        }
        else
        {
            if(password_1[i]==ch_password)
            {
                flag_new=1;
            }
            else
            {
                flag_new=0;
            }
        }
    }
    fclose(fptr_2); 

    if(flag_new==1 || flag==1)
    {
        if(flag_new==1 && flag==1 && count_1==count_2)
        {
            return 1;
        }
        else if(flag==0 || flag_new==0)
        {
            printf("\nEmail or password is incorrect.\n");
            goto Email;

        }
    }
    else
    {
        return 0;
    }
}

void signup()
{
    int flag;

    printf("\n\nPlease Enter your Account Details\n");
    First:
    printf("First Name = ");     //Entering the first name of the user
    scanf("%s",&first_name);

    while(1)                       //Checking whether the entered name is in alphabets or not?
    {
        if(strlen(first_name)!=0)
        {
            for(int i=0;first_name[i]!='\0';i++)
            {
                if(first_name[i]>='A' || email[i]<='Z' || email[i]>='a' ||first_name[i]<='z')
                {
                    flag=1;
                }
                else
                {
                    flag=0; 
                    break;
                }
            }
            
            if(flag==1)
            {
                break;
            }
            else
            {
                printf("Please Enter a valid Name !\n\n");
                goto First;
            }
        }
        else 
        {
            printf("No First Name found!\n\n");
            goto First;
        }
    }

    Last:
    printf("Last Name = ");      //Entering the last name of the user
    scanf("%s",&last_name);

    while(1)                        //Checking whether the entered name is in alphabets or not?
    {
        if(strlen(last_name)!=0)
        {
            for(int i=0;last_name[i]!='\0';i++)
            {
                if(last_name[i]>='A' || email[i]<='Z' || email[i]>='a' ||first_name[i]<='z')
                {
                    flag=1;
                }
                else
                {
                    flag=0; 
                    break;
                }
            }
            
            if(flag==1)
            {
                break;
            }
            else
            {
                printf("Please Enter a valid Name !\n\n");
                goto Last;
            }
        }
        else 
        {
            printf("No Last Name found!\n\n");
            goto Last;
        }
    }

    Contact:
    printf("Contact no. = ");
    // scanf("%d",&contact_no);
    // printf("%d\n",contact_no);
    scanf("\n");
    gets(contact_no);
    int count=0;

    if(strlen(contact_no)==10)
    {
        for(int i=0;(int)contact_no[i]>=48 && (int)contact_no[i]<=57;i++)
        {
            count++;
        }
        if(count!=10)
        {
            printf("\nInvalid Contact Number !\n");
            goto Contact;
        }
    }
    else
    {
        printf("\nInvalid Contact Number !\n");
        goto Contact;
    }

    
    // long int copied = contact_no

    // int count =0;
    // for(int i=0 ; i<10 && contact_no!=0 ; i++)
    // {
    // printf("\n%ld",contact_no);     
    // contact_no = contact_no / 10;
    //     count++;
    // }
    // if(count==10)
    // {
    //     flag=1;
    // }
    // else if(count==0)
    // {
    //     flag=0;
    //     printf("Contact no. Not Found !\n\n");
    //     goto Contact;
    // }
    // else
    // {
    //     printf("%ld\n",count);
    //     flag=0;
    //     printf("Invalid Contact no.\n\n");
    //     goto Contact;
    // }

    int x = validation();
    if(x==1)
    {
        printf("\nAccount already Exists.\n");
        login();
    }
    else
    {
        FILE *fptr_1;
        FILE *fptr_2;

        fptr_1 = fopen("Email_data.txt","a");
        fptr_2 = fopen("Password_data.txt","a");

        fprintf(fptr_1,"\n%s",email);
        fprintf(fptr_2,"\n%s",password_1);

        fclose(fptr_1);
        fclose(fptr_2);

        printf("\n\n Acount Created Succesfully. \n\n");
        login();
    }
    
}

void login()
{
    int login_choice,flag;
    printf("----------WELCOME TO THE LOGIN PAGE----------\n");
    printf("          Enter your Login Details            \n");

    int x = validation();

    switch(x)
    {
        case 1:
        Fashion();
        break;

        case 0:
        printf("\nAccount Doesn't Exist.\n");
        printf("Please register your Account.\n");
        signup();
        break;
    }

}

// void Shop()
// {
//     printf("\n-------------- Welcome To The Home Page of The Online Shopping Site of Branded Clothes.-------------\n");

//     Shop:
//     printf("\nSelect interested one from the following categories : \n");
//     printf("\n1 Fashion Products\n2 Electronic Products \n3 Food Products \n4 Exit\n");

//     int Shop_choice;
//     scanf("%d",&Shop_choice);

//     switch(Shop_choice)
//     {
//         case 1:
//         Fashion();
//         break;
        
//         case 2:
//         Electronics();
//         break;
//     }

// }

void Fashion()
{
    printf("\n-------------- Welcome To The Home Page of The Online Shopping Site of Branded Clothes.-------------\n");

    Fashion:
    printf("\n Select any one Category from the following fashion Products :\n");
    printf("\n1 Suits\n2 Shirts,T-Shirts and Jackets\n3 Trousers,Jeans and Pants\n4 Footwear\n5 Cart\n6 Exit\n");

    int Fashion_choice;
    scanf("%d",&Fashion_choice);

    switch(Fashion_choice)
    {
        case 1:
        Suits:
        printf("\nAvailable Brands :\n");
        printf("\n1 Raymond : 8499/-\n2 Van Hausen : 12999/-\n3 Gucci : 15999/-\n4 Tommy Hilfiger : 13499/-\n5 Cart \n6 Back\n");

        int Fashion_1;
        int Fashion_2;
        int Fashion_3;
        scanf("%d",&Fashion_1);

        switch(Fashion_1)
        {
            case 1:
            Total+= 8499;
            goto Suits;
            break;

            case 2:
            Total+= 12999;
            goto Suits;
            break;

            case 3:
            Total+= 15999;
            goto Suits;
            break;

            case 4:
            Total+= 13499;
            goto Suits;
            break;

            case 5:
            Cart();
            break;

            case 6:
            goto Fashion;
            break;

            default:
            printf("Invalid Choice !");
        }
        break;

        case 2:

        Fashion2:
        
        printf("\n1 Shirts\n2 T-Shirts\n3 Jackets\n4 Back\n");
        scanf("%d",&Fashion_2);

        if(Fashion_2==1)
        {
            goto Shirts;
        }
        else if(Fashion_2==2)
        {
            goto TShirts;
        }
        else if(Fashion_2==3)
        {
            goto Jackets;
        }
        else if(Fashion_2==4)
        {
            goto Fashion;
        }
        else
        {
            printf("\nInvalid Entry Found !\n");
            goto Fashion2;

        }
        Shirts:
        printf("\nAvailable Brands :\n");
        printf("\n1 Nike : 4499/-\n2 Puma : 3999/-\n3 Gucci : 6999/-\n4 Tommy Hilfiger : 3499/-\n5 Cart \n6 Back\n");

        int Shirts_choice;
        scanf("%d",&Shirts_choice);
        switch(Shirts_choice)
        {
            case 1:
            Total+= 4499;
            goto Shirts;
            break;

            case 2:
            Total+= 3999;
            goto Shirts;
            break;

            case 3:
            Total+= 6999;
            goto Shirts;
            break;

            case 4:
            Total+= 3499;
            goto Shirts;
            break;

            case 5:
            Cart();
            break;

            case 6:
            goto Fashion2;
            break;

            default:
            printf("Invalid Choice !");
        }

        TShirts:
        printf("\nAvailable Brands :\n");
        printf("\n1 Nike : 3499/-\n2 Puma : 2999/-\n3 Gucci : 5999/-\n4 Tommy Hilfiger : 2499/-\n5 Cart \n6 Back\n");

        int TShirts_choice;
        scanf("%d",&TShirts_choice);
        switch(TShirts_choice)
        {
            case 1:
            Total+= 3499;
            goto TShirts;
            break;

            case 2:
            Total+= 2999;
            goto TShirts;
            break;

            case 3:
            Total+= 5999;
            goto TShirts;
            break;

            case 4:
            Total+= 2499;
            goto TShirts;
            break;

            case 5:
            Cart();
            break;

            case 6:
            goto Fashion2;
            break;

            default:
            printf("Invalid Choice !");
        }

        Jackets:
        printf("\nAvailable Brands :\n");
        printf("\n1 Nike : 6499/-\n2 Puma : 5999/-\n3 Gucci : 6999/-\n4 Tommy Hilfiger : 5499/-\n5 Cart \n6 Back\n");

        int Jackets_choice;
        scanf("%d",&Jackets_choice);
        switch(Jackets_choice)
        {
            case 1:
            Total+= 6499;
            goto Jackets;
            break;

            case 2:
            Total+= 5999;
            goto Jackets;
            break;

            case 3:
            Total+= 6999;
            goto Jackets;
            break;

            case 4:
            Total+= 5499;
            goto Jackets;
            break;

            case 5:
            Cart();
            break;

            case 6:
            goto Fashion2;
            break;

            default:
            printf("Invalid Choice !");
        }
        break;

        case 3:


        Fashion3:
        printf("\n1 Trousers\n2 Jeans\n3 Pants\n4 Back\n");
        scanf("%d",&Fashion_3);
        if(Fashion_3==1)
        {
            goto Trousers;
        }
        else if(Fashion_3==2)
        {
            goto Jeans;
        }
        else if(Fashion_3==3)
        {
            goto Pants;
        }
        else if(Fashion_3==4)
        {
            goto Fashion;
        }
        else
        {
            printf("\nInvalid Entry Found !\n");
            goto Fashion3;

        }
        Trousers:
        printf("\nAvailable Brands :\n");
        printf("\n1 Peter England : 2499/-\n2 Nike : 2999/-\n3 Addidas : 1999/-\n4 Tommy Hilfiger : 1499/-\n5 Cart \n6 Back\n");

        int Trousers_choice;
        scanf("%d",&Trousers_choice);
        switch(Trousers_choice)
        {
            case 1:
            Total+= 2499;
            goto Trousers;
            break;

            case 2:
            Total+= 2999;
            goto Trousers;
            break;

            case 3:
            Total+= 1999;
            goto Trousers;
            break;

            case 4:
            Total+= 1499;
            goto Trousers;
            break;

            case 5:
            Cart();
            break;

            case 6:
            goto Fashion3;
            break;

            default:
            printf("Invalid Choice !");
        }

        Jeans:
        printf("\nAvailable Brands :\n");
        printf("\n1 Peter England : 2999/-\n2 Nike : 3999/-\n3 Addidas : 3499/-\n4 Tommy Hilfiger : 2499/-\n5 Cart \n6 Back\n");

        int Jeans_choice;
        scanf("%d",&Jeans_choice);
        switch(Jeans_choice)
        {
            case 1:
            Total+= 2999;
            goto Jeans;
            break;

            case 2:
            Total+= 3999;
            goto Jeans;
            break;

            case 3:
            Total+= 3499;
            goto Jeans;
            break;

            case 4:
            Total+= 2499;
            goto Jeans;
            break;

            case 5:
            Cart();
            break;

            case 6:
            goto Fashion3;
            break;

            default:
            printf("Invalid Choice !");
        }

        Pants:
        printf("\nAvailable Brands :\n");
        printf("\n1 Peter England : 3499/-\n2 Nike : 4499/-\n3 Addidas : 3999/-\n4 Tommy Hilfiger : 2999/-\n5 Cart \n6 Back\n");

        int Pants_choice;
        scanf("%d",&Pants_choice);
        switch(Pants_choice)
        {
            case 1:
            Total+= 3499;
            goto Pants;
            break;

            case 2:
            Total+= 4499;
            goto Pants;
            break;

            case 3:
            Total+= 3999;
            goto Pants;
            break;

            case 4:
            Total+= 2999;
            goto Pants;
            break;

            case 5:
            Cart();
            break;

            case 6:
            goto Fashion3;
            break;

            default:
            printf("Invalid Choice !");
        }
        break;

        case 4:
        Footwear:
        printf("\nAvailable Brands :\n");
        printf("\n1 Nike : 8499/-\n2 Adidas : 12999/-\n3 Jordan : 15999/-\n4 Puma : 13499/-\n5 Cart \n6 Back\n");

        // int Fashion_1;
        scanf("%d",&Fashion_1);

        switch(Fashion_1)
        {
            case 1:
            Total+= 8499;
            goto Footwear;
            break;

            case 2:
            Total+= 12999;
            goto Footwear;
            break;

            case 3:
            Total+= 15999;
            goto Footwear;
            break;

            case 4:
            Total+= 13499;
            goto Footwear;
            break;

            case 5:
            Cart();
            break;

            case 6:
            goto Fashion;
            break;

            default:
            printf("Invalid Choice !");
        }
        break;

        case 5:
        Cart();
        break;

        case 6:
        printf("\nThank You for Visiting.\n");
        printf("Have a Nice Day\n");
        break;

        default:
        printf("\nInvalid Entry !\n");
    }
}

void Cart()
{
    int Cart_choice;

    printf("\n--------Welcome To The Cart Page--------\n");
    printf("\n Total Amount of the Products added to the Cart :\n");
    printf("%d\n",Total);

    Cart1:
    printf("\nPress 1 - to confirm your order\n");
    printf("Press 0 - to Discart all the items\n");
    scanf("%d",&Cart_choice);

    if(Cart_choice==1)
    {
        printf("\n Your Order Has Been Confirmed !\n");
    }
    else if(Cart_choice==0)
    {
        int Final_choice;
        printf("\n No Items Found In The Cart\n");

        Cart2:
        printf("\n Press 1 - to go back to Home Page\n");
        printf("Press 0 - to Exit the Shopping Site\n");
        scanf("%d",&Final_choice);

        if(Final_choice==1)
        {
            Fashion();
        }
        else if(Cart_choice==0)
        {
            printf("\nThank You for Visiting.\n");
            printf("Have a Nice Day\n");
        }
        else
        {
            printf("\nInvaild Entry !\n");
            goto Cart2;
        }
    }
    else
    {
        printf("\nInvaild Entry !\n");
        goto Cart1;
    }
}
