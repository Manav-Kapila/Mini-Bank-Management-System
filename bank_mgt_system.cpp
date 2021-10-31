/**********************************************************************************************
            PROGRAM FOR MINI BANK MANAGEMENT SYSTEM
**********************************************************************************************/

/**********************************************************************************************

1. Create an account first then use the program 
2. If an account is not created and directly operations are accessed 
then it will will throw an error because without any account creation, the data file is not 
created and hence there is no data for the code to act upon
**********************************************************************************************/


#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
#include<stdlib.h>
using namespace std;

// Class account containing fxns for banking operations
class Bank
{
    int AccNumber, lastTxnAccount;
    char name[50],address[100],lastTxnName[20],lastTxnType[10];
    int deposit,lastTxnAmount,lastTxnBalance;
    char type;
public:
    void create_account();  //Fxn to get data from user
    void show_account() const;  //Fxn to show data on screen
    void show_account_holder_name() const;  //Fxn to show data on screen
    void show_account_balance() const;  //Fxn to show data on screen
    void show_account_holder_address() const;  //Fxn to show data on screen
    void dep(int);  //Fxn to accept amount and add to balance amount
    void draw(int); //Fxn to accept amount and subtract from balance amount
    void report() const;    //Fxn to show data in tabular format
    int retAccNumber() const;    //Fxn to return account number
    int retdeposit() const; //Fxn to return balance amount
    char rettype() const;   //Fxn to return type of account
};         //class ends here


// Fxn to take user input to create account 
void Bank::create_account()
{
    cout<<"\nEnter The account No. :";
    cin>>AccNumber;
    cout<<"\n\nEnter the Name of the account holder : ";
    cin.ignore();
    cin.getline(name,50);
    cout<<"\n\nEnter the Address of the account holder : ";
    cin.ignore();
    cin.getline(address,100);
    cout<<"\nEnter the type of account i.e. Savings or Current (C= Current and S= Savings) : ";
    cin>>type;
    type=toupper(type);
    cout<<"\n Enter The Initial Balance : ";
    cin>>deposit;
    cout<<"\n\n\nAccount Created..";
}

// Fxn to display status of created account 
void Bank::show_account() const
{
    cout<<"\n Account No. : "<<AccNumber;
    cout<<"\n Account Holder's Name : ";
    cout<<name;
    cout<<"\n Account Holder's Address : ";
    cout<<address;
    cout<<"\n Account Type  : "<<type;
    cout<<"\n Account Balance : "<<deposit;
}

void Bank::show_account_holder_name() const
{
    cout<<"\n Account No. : "<<AccNumber;
    cout<<"\n Account Holder's Name : ";
    cout<<name;
}

void Bank::show_account_balance() const
{
    cout<<"\n Account No. : "<<AccNumber;
    cout<<"\n Account Balance : "<<deposit;
}

void Bank::show_account_holder_address() const
{
    cout<<"\n Account No. : "<<AccNumber;
    cout<<"\n Account Holder's Address : ";
    cout<<address;
}

void Bank::dep(int x)
{
    deposit+=x;
}

void Bank::draw(int x)
{
    deposit-=x;
}

void Bank::report() const
{
    cout<<AccNumber<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(6)<<deposit<<endl;
}


int Bank::retAccNumber() const
{
    return AccNumber;
}

int Bank::retdeposit() const
{
    return deposit;
}

char Bank::rettype() const
{
    return type;
}

//      Fxn to write in file

void write_account()
{
    Bank obj;
    ofstream outFile;
    outFile.open("bank_accounts_data.dat",ios::binary|ios::app);
    obj.create_account();
    outFile.write(reinterpret_cast<char *> (&obj), sizeof(Bank));
    outFile.close();
}

//      Fxn to read specific record from file

void display_sp(int n)
{
    Bank obj;
    bool flag=false;
    ifstream inFile;
    inFile.open("bank_accounts_data.dat",ios::binary);
    if(!inFile)
    {
        cout<<"File could not be open !! Try creating an account first.";
        return;
    }
    cout<<"\n BALANCE DETAILS \n";

        while(inFile.read(reinterpret_cast<char *> (&obj), sizeof(Bank)))
    {
        if(obj.retAccNumber()==n)
        {
            obj.show_account();
            flag=true;
        }
    }
    inFile.close();
    if(flag==false)
        cout<<"\n\nAccount number does not exist";
}

//      Fxn for displaying account holder's name

void display_sp_name(int n)
{
    Bank obj;
    bool flag=false;
    ifstream inFile;
    inFile.open("bank_accounts_data.dat",ios::binary);
    if(!inFile)
    {
        cout<<"File could not be open !! Try creating an account first.";
        return;
    }
    cout<<"\n BALANCE DETAILS \n";

        while(inFile.read(reinterpret_cast<char *> (&obj), sizeof(Bank)))
    {
        if(obj.retAccNumber()==n)
        {
            obj.show_account_holder_name();
            flag=true;
        }
    }
    inFile.close();
    if(flag==false)
        cout<<"\n\nAccount number does not exist";
}

//      Fxn for displaying account holder's balance

void display_sp_balance(int n)
{
    Bank obj;
    bool flag=false;
    ifstream inFile;
    inFile.open("bank_accounts_data.dat",ios::binary);
    if(!inFile)
    {
        cout<<"File could not be open !! Try creating an account first.";
        return;
    }
    cout<<"\n BALANCE DETAILS \n";

        while(inFile.read(reinterpret_cast<char *> (&obj), sizeof(Bank)))
    {
        if(obj.retAccNumber()==n)
        {
            obj.show_account_balance();
            flag=true;
        }
    }
    inFile.close();
    if(flag==false)
        cout<<"\n\nAccount number does not exist";
}

//      Fxn for displaying account holder's address

void display_sp_address(int n)
{
    Bank obj;
    bool flag=false;
    ifstream inFile;
    inFile.open("bank_accounts_data.dat",ios::binary);
    if(!inFile)
    {
        cout<<"File could not be open !! Try creating an account first.";
        return;
    }
    cout<<"\n BALANCE DETAILS \n";

        while(inFile.read(reinterpret_cast<char *> (&obj), sizeof(Bank)))
    {
        if(obj.retAccNumber()==n)
        {
            obj.show_account_holder_address();
            flag=true;
        }
    }
    inFile.close();
    if(flag==false)
        cout<<"\n\nAccount number does not exist";
}


//      Fxn for deleting account

void delete_account(int n)
{
    Bank obj;
    ifstream inFile;
    ofstream outFile;
    inFile.open("bank_accounts_data.dat",ios::binary);
    if(!inFile)
    {
        cout<<"File could not be open !! Try creating an account first.";
        return;
    }
    outFile.open("Temp.dat",ios::binary);
    inFile.seekg(0,ios::beg);
    while(inFile.read(reinterpret_cast<char *> (&obj), sizeof(Bank)))
    {
        if(obj.retAccNumber()!=n)
        {
            outFile.write(reinterpret_cast<char *> (&obj), sizeof(Bank));
        }
    }
    inFile.close();
    outFile.close();
    remove("bank_accounts_data.dat");
    rename("Temp.dat","bank_accounts_data.dat");
    cout<<"\n\n\t Record Deleted ..";
}

//***************************************************************
//      Fxn to display all accounts deposit list
//****************************************************************

void display_all()
{
    Bank obj;
    ifstream inFile;
    inFile.open("bank_accounts_data.dat",ios::binary);
    if(!inFile)
    {
        cout<<"File could not be open !! Try creating an account first.";
        return;
    }
    cout<<"\n\n ACCOUNT HOLDER's LIST \n\n";
    cout<<"\n====================================================\n";
    cout<<"A/c no.      NAME        Type    Balance \n";
    cout<<"\n====================================================\n";
    while(inFile.read(reinterpret_cast<char *> (&obj), sizeof(Bank)))
    {
        obj.report();
    }
    inFile.close();
}

//      Fxn to deposit and withdraw amounts

void deposit_withdraw(int n, int option)
{
    int amt;
    bool found=false;
    Bank obj;
    fstream File;
    File.open("bank_accounts_data.dat", ios::binary|ios::in|ios::out);
    if(!File)
    {
        cout<<"File could not be open !! Try creating an account first.";
        return;
    }
    while(!File.eof() && found==false)
    {
        File.read(reinterpret_cast<char *> (&obj), sizeof(Bank));
        if(obj.retAccNumber()==n)
        {
            obj.show_account();
            if(option==1)
            {
                cout<<"\n\n\tTO DEPOSITE AMOUNT ";
                cout<<"\n\n Enter The amount to be deposited";
                cin>>amt;
                obj.dep(amt);
            }
            if(option==2)
            {
                cout<<"\n\n\t TO WITHDRAW AMOUNT ";
                cout<<"\n\n Enter The amount to withdraw";
                cin>>amt;
                int bal=obj.retdeposit();
    // Logic to check whether the amount to withdrawn is greater than available balance in the account
                if(bal<amt)
                    cout<<"Insufficience balance";
                else
                    obj.draw(amt);
            }
            int pos=(-1)*static_cast<int>(sizeof(obj));
            File.seekp(pos,ios::cur);
            File.write(reinterpret_cast<char *> (&obj), sizeof(Bank));
            cout<<"\n\n\t Record Updated";
            found=true;
           }
         }
    File.close();
    if(found==false)
        cout<<"\n\n Record Not Found ";
}


//***************************************************************
//      Main driver code
//****************************************************************


int main()
{
    char ch;
    int accNo;
    cout<<"\n\n ---------------------------------------------------------------------------";
    cout<<"\n\n*********************  Mini Bank Management System     *********************";
    cout<<"\n\n ---------------------------------------------------------------------------";
    do
    {
    // choose:
        system("cls");
        cout<<"\n MAIN MENU";
         cout<<"\n Enter Your Choice : ";
        cout<<"\n 1. Create a new account";
        cout<<"\n 2. Deposit money in an existing account";
        cout<<"\n 3. Withdraw money from an existing account";
        cout<<"\n 4. Check balance of an existing account";
        cout<<"\n 5. Display list of all account holders";
        cout<<"\n 6. Delete an existing account";
        cout<<"\n 7. Check whether account exists or not";
        cout<<"\n 8. Show account holder's NAME ONLY ";
        cout<<"\n 9. Show account holder's BALANCE ONLY ";
        cout<<"\n A. Show account holder's ADDRESS ONLY ";      
        cout<<"\n 0. EXIT\n";
       
        cin>>ch;
        if(ch =='a'){
            ch=toupper(ch);
        }
        system("cls");
        switch(ch)
        {
        case '1':
            write_account();
            break;
        case '2':
            cout<<"\n Enter account No. : "; 
            cin>>accNo;
            deposit_withdraw(accNo, 1);
            break;
        case '3':
            cout<<"\n\n\tEnter account No. : "; 
            cin>>accNo;
            deposit_withdraw(accNo, 2);
            break;
        case '4':
            cout<<"\n Enter account No. : "; 
            cin>>accNo;
            display_sp(accNo);
            break;
        case '5':
            display_all();
            break;
        case '6':
            cout<<"\n Enter account No. : "; 
            cin>>accNo;
            delete_account(accNo);
            break;
         case '7':
            cout<<"\n Enter account No. : "; 
            cin>>accNo;
            display_sp(accNo);
            break;
        case '8':
            cout<<"\n Enter account No. : "; 
            cin>>accNo;
            display_sp_name(accNo);
            break;
        case '9':
            cout<<"\n Enter account No. : "; 
            cin>>accNo;
            display_sp_balance(accNo);
            break;
        case 'A':
            cout<<"\n Enter account No. : "; 
            cin>>accNo;
            display_sp_address(accNo);
            break;
         case '0':
            cout<<"\n EXITING........";
            break;
         default :cout<<" Invalid Choice!.....Press Any Key to continue ";
        //    goto choose;
        }
        cin.ignore();
        cin.get();
    }while(ch!='0');
    return 0;
}