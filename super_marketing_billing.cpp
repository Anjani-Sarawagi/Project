#include<iostream>
#include<fstream>
#include<sstream>
#include<windows.h>
#include<string>
using namespace std;

class Bill{
private :

string item;
int rate;
int quantity;

public :

void setItem(string item)        {this->item = item;}
void setRate(int rate)           {this->rate = rate;}
void setQuantity(int quantity)   {this->quantity = quantity;}

string getItem()    {return item;}
int getRate()       {return rate;}
int getQuantity()   {return quantity;}
};


void addItem(Bill b){ 

    bool close = false;
    while(! close){
        int choice;
        cout<<"\t1.Add Item."<<endl;
        cout<<"\t2.Close Session."<<endl;
        cout<<"\tEnter Choice"<<endl;
        cin>>choice;

        if(choice==1){
            system("cls");
            string item;
            int rate, quantity;

            cout<<"\tEnter Item : ";
            cin>>item;
            cout<<"\tEnter Rate : ";
            cin>>rate;
            cout<<"\tEnter Quantity : ";
            cin>>quantity;

            b.setItem(item);
            b.setRate(rate);
            b.setQuantity(quantity);
           
            ofstream out("C:\\file handaling/Bill.txt", ios::app);
            if(!out){
                cout<<"\tError : File can't open!!"<<endl;
            }
            else{
                out<<"\t"<<b.getItem()<<" : "<<b.getRate()<<" : "<<b.getQuantity()<<endl<<endl;
            }
            out.close();
            cout<<"\tItem added successfuly"<<endl;
            Sleep(3000);
        }
        else if(choice==2){
            system("cls");
            close = true;
            cout<<"\tBack To Main Menu"<<endl;
            Sleep(3000);
        }
        else{
            cout<<"Invailed Choice !!"<<endl;
        }

    }
}

void printBill(){
    system("cls");
   
    int count = 0;
    bool close = false;

    while(!close){

    system("cls");
    int choice;
    cout<<"\t1.Add Bill."<<endl;
    cout<<"\t2.Close Session."<<endl;
    cout<<"\tEnter Choice : ";
    cin>>choice;

    if(choice==1){
        string item;
        int quantity;
        cout<<"Enter Item : ";
        cin>>item;
        cout<<"Enter Quantity : ";
        cin>>quantity;

        ifstream in("C:\\file handaling/Bill.txt");
        ofstream out("C:\\file handaling/Bill Temp.txt");

        string line;
        bool found = false;

        while(getline(in, line)){
            stringstream ss;
            ss<<line;
            string itemName;
            int itemRate;
            int itemQuantity;
            char delimiter;
            ss>>itemName>>delimiter>>itemRate>>delimiter>>itemQuantity;

            if(item == itemName){
                found = true;
                if(quantity <= itemQuantity){
                    int amount = itemRate*quantity;
                    cout<<"\t Item  |  Rate  |  Quantity  |  Amount"<<endl;
                    cout<<"\t"<<item<<" | "<<itemRate<<" | "<<quantity<<" | "<<amount<<endl;
                    
                    int newQuantity = itemQuantity-quantity;
                    itemQuantity = newQuantity;
                    count += amount;

                    out<<"\t"<<itemName<<" : "<<itemRate<<" : "<<itemQuantity<<endl<<endl;
                }
                else{
                    cout<<"\tSorry, "<<item<<" ended !!"<<endl;
                }
            }
            else{
                out<<line;
            }
        }

        if(!found){
            cout<<"\tItem not available !!"<<endl;
        }

        out.close();
        in.close();
        remove("C:\\file handaling/Bill.txt");
        rename("C:\\file handaling/Bill Temp.txt", "C:\\file handaling/Bill.txt");
    }

    else if(choice == 2){
        close = true;
        cout<<"\tCounting Total Bill"<<endl;
    }
    Sleep(3000);
    }
    system("cls");
    cout<<endl<<endl<<"\t Total Bill -------------------------- : "<<count<<endl<<endl;
    cout<<"Thanks for shoping"<<endl;
    Sleep(5000);
}

int main(){

    Bill b;
    bool exit = false;
    while(! exit){
    system("cls");
    int choice;

    cout<<"\tWelcome To Super Market Billing System"<<endl;
    cout<<"\t**************************************"<<endl;
    cout<<"\t\t1.Add Item."<<endl;
    cout<<"\t\t2.Print Bill."<<endl;
    cout<<"\t\t3.Exit."<<endl;
    cout<<"\t\tEnter Choice : ";
    cin>>choice;

    if(choice==1){
        system("cls");
        addItem(b);
        Sleep(3000);
    }
    else if(choice==2){
        printBill();
    }
    else if(choice==3){
        system("cls");
        exit = true;
        cout<<"Good Luck !!"<<endl;
        Sleep(3000);
    }
    else{
        cout<<"Invailed input!!"<<endl;
        break;
    }
}
    
return 0;
}