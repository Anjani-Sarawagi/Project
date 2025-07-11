#include<iostream>
#include<fstream>
#include<windows.h>
#include<sstream>
#include<string>
using namespace std;

// ofstream = to write data in the file
// ifstream = to read the data in file

class Account{
private:
string AccountNo, Password;
int Balance;
public:
Account(): AccountNo(""), Password(""), Balance(0) {};

void setAccountNo(string id)          { AccountNo = id; }
void setPassword(string password)     { Password = password; }
void setBalance(int balance)          { Balance = balance; }

string getAccountNo()      { return AccountNo; }
string getPassword()       { return Password; }
int getBalance()           { return Balance; }
};

void openAccount(Account user){
    system("cls");
    string id, pw;
    cout<<"\tEnter Account No : ";
    cin>>id;
    user.setAccountNo(id);
    
    cout<<"\tEnter a strong password : ";
    cin>>pw;
    user.setPassword(pw);

    user.setBalance(0);

    ofstream outfile("C:\\file handaling/Bank.txt", ios::app); // storing the data in the txt file
    if(!outfile){   //if file does not get opened
        cout<<"\tError : File can't open!"<<endl;
    }
    else{
        outfile<<"\t"<<user.getAccountNo()<<" : "<<user.getPassword()<<" : "<<user.getBalance()<<endl<<endl;
        cout<<"\tAccount created successfuly!"<<endl;
    }
    outfile.close();
    Sleep(2000);
}

void addCash(){
    system("cls");
    string id;
    cout<<"\tEnter Account No : ";
    cin>>id;

    ifstream infile("C:\\file handaling/Bank.txt");        // to read the data from the file
    ofstream outfile("C:\\file handaling/Bank Temp.txt");  // ifstream = to read the data in file

    if(!infile || !outfile){
        cout<<"\tError : File can't open"<<endl;
    }

    string line;
    bool found = false;

    while(getline(infile, line)){ // get line is a function which get the data from the file
                                  // taking data from the infile and saving it in line (string)
    
    stringstream ss;              // header file sstream
    ss<<line;                     // ss taking data from line
    string userID, userPW;
    int userBalance;
    char delimiter;               // to set the boundary

    ss>>userID>>delimiter>>userPW>>delimiter>>userBalance;     // taking data from the ss
    if(id==userID){
        found = true;
        int cash;
        cout<<"\tEnter Cash : ";
        cin>>cash;

        int newBalance = userBalance + cash;
        userBalance = newBalance;

        outfile<<"\t"<<userID<<" : "<<userPW<<" : "<<userBalance<<endl;
        cout<<"\tNew balance is : "<<newBalance<<endl;
    }
    else{
        outfile<<line<<endl;
    }
    }

    if(!found){
        cout<<"\tEnter valid Account No!"<<endl;
    }
    outfile.close();
    infile.close();
    remove("C:\\file handaling/Bank.txt");
    rename("C:\\file handaling/Bank Temp.txt", "C:\\file handaling/Bank.txt");
    Sleep(3000);
}

void withdraw(){
    string id, pw;
    cout<<"\tEnter Account No : ";
    cin>>id;
    cout<<"\tEnter Password : ";
    cin>>pw;

    ifstream infile("C:\\file handaling/Bank.txt");
    ofstream outfile("C:\\file handaling/Bank Temp.txt");

    if(!infile || !outfile){
        cout<<"\tError : File can't open!"<<endl;
    }

    string line;
    bool found = false;

    while(getline(infile, line)){
    stringstream ss;
    ss<<line;
    string userId, userPw;
    int UserBalance;
    char delimiter;
    ss>>userId>>delimiter>>userPw>>delimiter>>UserBalance;

    if(id==userId && pw==userPw){
        found = true;
        int cash;
        cout<<"\tEnter cash : ";
        cin>>cash;
        if(cash <= UserBalance){
            int newBalance = UserBalance-cash;
            UserBalance = newBalance;
            outfile<<"\t"<<userId<<" : "<<userPw<<" : "<<UserBalance<<endl;
            cout<<"\tTransaction was successful !"<<endl;
            cout<<"\tRemainig Balance : "<<UserBalance<<endl;
        }
        else{
            cout<<"\tLow Balance !!"<<endl;
            outfile<<"\t"<<userId<<" : "<<userPw<<" : "<<UserBalance<<endl;

        }
    }
    else{
        outfile<<line<<endl;
    }
    }


    if(!found){
        cout<<"\tInvalid Account No or Password."<<endl;
    }

    outfile.close();
    infile.close();
    remove("C:\\file handaling/Bank.txt");
    rename("C:\\file handaling/Bank Temp.txt", "C:\\file handaling/Bank.txt");
    Sleep(5000);
}

int main(){
    Account user;

    bool exit = false;

    while(!exit){
    system("cls");

    int choice;
    cout<<"\tWelcome to Bank Account Management System"<<endl;
    cout<<"\t*****************************************"<<endl;
    cout<<"\t1.Open New Account."<<endl;
    cout<<"\t2.Add Cash."<<endl;
    cout<<"\t3.Withdraw Cash."<<endl;
    cout<<"\t4.Exit."<<endl;
    cin>>choice;
    Sleep(1000);

    if(choice==1){
        openAccount(user);
    }
    else if(choice==2){
        addCash();
    }
    else if(choice==3){
        withdraw();
    }
    else if(choice==4){
        system("cls");
        exit = true;
        cout<<"\tGood Luck !!"<<endl;
        Sleep(2000);
    }
    else{
        cout<<"Invailed choice !!";
    }
    Sleep(2000);
    }
    
    return 0;
}
