// The code is a program that simulates a billing system for a store called "VIT CANTEEN".
//  It uses structures to store data about orders and items.

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

struct items
// stores information about an item,
// including the item name, price and quantity
{
    char item[20];
    float price;
    int qty;
};

struct orders// information about an order, including the customer's name,
// the date of the order, the number of items in the order
//  and an array of 'struct items' for the items in the order.

{
    char customer[50];
    char date[50];
    int numOfItems;
    struct items itm[50];
};

//Function to Generate Bills
//phase 1
void generateBillHeader(char name[50],char date[30])// This function takes the name of the customer and the date of the order as inputs
// and generates the header of the bill, which includes the store name,
// date of the order, and a table with column headers for items, quantity and total.

{

    printf("\n\n");
    printf("\t      VIT CANTEEN     ");
    printf("\n\t -----------------");
    printf("\n Date : %s",date);
    printf("\n");
    printf("------------------------------------------------\n");
    printf("Items \t\t");
    printf("Quantity \t\t");
    printf("Total \t\t");
    printf("\n------------------------------------------------");
    printf("\n\n");

}
void generateBillBody(char Item[30],int qty,float price)// This function takes the name of an item, its quantity, and price as inputs
// and generates a row in the table for that item, showing the name, quantity, and total cost of the item.


{

    printf("%s\t\t",Item);
    printf("%d\t\t",qty);
    printf("%2.f\t\t",qty * price);
    printf("\n");

}



void generateBillFooter(float total)// This function takes the total cost of the order as an input
// and generates the footer of the bill, which includes the subtotal, discount, net total, taxes, and grand total.

{

    printf("\n");
    float dis = 0.1*total;
    float netTotal = total-dis;
    float cgst = 0.09*netTotal, grandTotal = netTotal + 2*cgst;
    printf("----------------------------------------------");
    printf("\nSubTotal\t\t\t %.2f",total);
    printf("\n Discount @10%s\t\t\t %.2f","%",dis);
    printf("\n\t\t\t\t----------------");
    printf("\n Net Total\t\t\t %.2f",netTotal);
    printf("\n CGST @9 %s\t\t\t %.2f","%",cgst);
    printf("\n SGST @9 %s\t\t\t %.2f","%",cgst);
    printf("\n--------------------------------------------");
    printf("\n Grand Total\t\t\t %.2f",grandTotal);

}

int main()//The main() function starts by declaring a number of variables, 
//including a struct of type orders named ord, and a file pointer fp. 

{

    float total;
    int opt,n;
    struct orders ord;
    struct orders order;
    char saveBill = 'y', contFlag='y';
    char name[50];

    FILE * fp;
    // It then enters a while loop that presents the user with a menu of options
    //  "Generate Invoice", "Show all Invoice", and "Exit"
    // DashBoard

    while(contFlag=='y'){
        system("cls");
        float total=0;
        int invoiceFound=0;
    printf("\t ========== VIT CANTEEN  ===========");
    printf("\n\n\tPlease enter your prefered operation: ");
    printf("\n\t1.Generate Invoice");
    printf("\n\t2.Show all Invoice");
    printf("\n\t3.Exit");

    printf("\n\n\t Your Choice : ");
    scanf("\n %d",&opt);
    fgetc(stdin);
    //phase 2
    switch(opt){
        case 1:

        system("cls");
        printf("\n\tPlease Enter the name of the customer:\t");
        fgets(order.customer,50,stdin);
        order.customer[strlen(order.customer)-1]= 0;
        strcpy(order.date,__DATE__);
        printf("\n\tPlease enter the number of items:\t");
        scanf("%d",&n);
        order.numOfItems = n;

        for(int i=0;i<n;i++){
        fgetc(stdin);
        printf("\n\n");
        printf("\tPlease enter the item %d:\t",i+1);
        fgets(order.itm[i].item,20,stdin);
        order.itm[i].item[strlen(order.itm[i].item)-1]=0;
        printf("\tPlease enter the quantity:\t");
        scanf("%d",&order.itm[i].qty);
        printf("\tPlease enter the unit price:\t");
        scanf("%f",&order.itm[i].price);
        total += order.itm[i].qty * order.itm[i].price;
        }

        generateBillHeader(order.customer,order.date);
        for(int i=0;i<order.numOfItems;i++){
        generateBillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
        }

        generateBillFooter(total);

        printf("\nDo you want to save the invoice [y/n]:\t");
        scanf("%s",&saveBill);

        if (saveBill == 'y')
        {
            fp = fopen("ABC.txt","a+");
            fwrite(&order,sizeof(struct orders),1,fp);
            if (fwrite != 0) {
                printf("\nSuccessfully Saved");
            }
            else
            printf("\nError Saving ");
            fclose(fp);
            break;
         //phase 3
       case 2:
         // the user chooses to save the bill, the program opens a file named "p.txt" in "append" mode 
            //and writes the order struct to it using fwrite() function.

        system("cls");
        fp = fopen("ABC.txt","r");
        printf("\n Your Previous Invoices\n");
        while(fread(&order,sizeof(struct orders),1,fp)){
            float tot = 0;
            generateBillHeader(order.customer,order.date);
            for(int i=0;i<order.numOfItems;i++){
                generateBillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
                tot += order.itm[i].qty * order.itm[i].price;
            }
            generateBillFooter(tot);
        }
        fclose(fp);
        break;
    }


        case 3:
        //Finally, the program checks if the fwrite() call was successful
        // and prints a message to indicate whether the bill was saved successfully.

        printf("\n\t Thank You :)\n\n");
        printf("\n\n");

        exit(0);

        break;

        default:
        printf("\tSorry invalid option");
        break;

    }
    printf("\n\n\t Do you want to perform another operation? [y/n]: \t");
    scanf("%s",&contFlag);
    }
    printf("\n\t Thank You :)\n\n");
    printf("\n\n");


   return 0;
}