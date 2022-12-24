#include <bits/stdc++.h>
using namespace std;
class Acc{
    int account_no;
    char name[50];
    int deposit;
    char type;
public:
    void createAcc();
    void showAcc() const;
    void modify();
    void dep(int);
    void withdraw(int);
    void report() const;
    int returnAcc() const;
    int returnDep() const;
    char returnType() const;
};

void Acc :: createAcc()
{
    cout<<"\n\nEnter the account number:\n";
    cin>>account_no;
    cout<<"\n\nEnter your full name:\n";
    cin.ignore();
    cin.getline(name,50);
    cout<<"\n\nEnter the type of account(C/S):\n";
    cin>>type;
    type = toupper(type);
    cout<<"\n\nEnter the initial amount(>= 500 for Saving and >= 1000 for current:)\n";
    cin>>deposit;
    cout<<"\n\nAccount created\n";
}
void Acc ::showAcc() const{
    cout<<"\nAccount number : "<<account_no<<"\n";
    cout<<"\nName : "<<name<<"\n";
    cout<<"\nAccount type : "<<type<<"\n";
    cout<<"\nBalance Amount : "<<deposit<<"\n";
}
void Acc ::modify(){
    cout<<"\nAccount number : "<<account_no<<"\n";
    cout<<"\n\nModify the name:\n";
    cin.ignore();
    cin.getline(name,50);
    cout<<"\n\nModify the type of account(C/S):\n";
    cin>>type;
    type = toupper(type);
    cout<<"\n\nModify the balance amount:)\n";
    cin>>deposit;
}
void Acc :: dep(int amount){
    deposit += amount;
}
void Acc :: withdraw(int amount){
    deposit -= amount;
}
void Acc :: report() const{
    cout<<account_no<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(6)<<" "<<deposit<<"\n";
}

int Acc :: returnAcc() const{
    return account_no;
}

int Acc :: returnDep()const{
    return deposit;
}

char Acc :: returnType() const{
    return type;
}

void write_account();
void display_specific(int);
void modify_account(int);
void delete_account(int);
void display_all();
void deposit_withdraw(int,int);
void welcome();

int main()
{
    char ch;
    int num;
    welcome();
    do{
        system("cls");
        cout<<"\n\n\n"<<setw(60);
        cout<<"Main Activities:"<<"\n\n";
        cout<<setw(57);
        cout<<"01.NEW ACCOUNT"<<"\n";
        cout<<setw(59);
        cout<<"02.DEPOSIT MONEY"<<"\n";
        cout<<setw(60);
        cout<<"03.WITHDRAW MONEY"<<"\n";
        cout<<setw(61);
        cout<<"04.BALANCE INQUIRY"<<"\n";
        cout<<setw(65);
        cout<<"05.ACCOUNT HOLDER LIST"<<"\n";
        cout<<setw(63);
        cout<<"06.MODIFY AN ACCOUNT"<<"\n";
        cout<<setw(62);
        cout<<"07.CLOSE AN ACCOUNT"<<"\n";
        cout<<setw(50);
        cout<<"08.EXIT"<<"\n";
        cout<<setw(70);
        cout<<"Select your option from the above:"<<"\n";
        cin>>ch;
        system("cls");
        switch(ch){
        case '1':
            write_account();
            break;
        case '2':
            cout<<"\n\nEnter the account number : ";
            cin>>num;
            deposit_withdraw(num,1);
            break;
        case '3':
            cout<<"\n\nEnter the account number : ";
            cin>>num;
            deposit_withdraw(num,2);
            break;
        case '4':
            cout<<"\n\nEnter the account number : ";
            cin>>num;
            display_specific(num);
            break;
        case '5':
            display_all();
            break;
        case '6':
            cout<<"\n\nEnter the account number : ";
            cin>>num;
            modify_account(num);
            break;
        case '7':
            cout<<"\n\nEnter the account number : ";
            cin>>num;
            delete_account(num);
            break;
        case '8':
            cout<<"\n\nThanks for using bank management system...";
            break;
        default:cout<<"\a";
        }

         cin.ignore();
         cin.get();

    }while(ch!='8');
    return 0;
}

void write_account(){
    Acc ac;
    ofstream outFile;
    outFile.open("bank.dat",ios::binary|ios::app);
    ac.createAcc();
    outFile.write(reinterpret_cast<char *>(&ac) , sizeof(Acc));
    outFile.close();
}

void display_specific(int n){
    Acc ac;
    bool flag = false;
    ifstream inFile;
    inFile.open("bank.dat",ios::binary);
    if(!inFile){
        cout<<"File coulnt be openend!!Press any key...";
        return;
    }
    while(inFile.read(reinterpret_cast<char *>(&ac) , sizeof(Acc))){
        if(ac.returnAcc() == n){
            ac.showAcc();
            flag = true;
        }
    }
    inFile.close();
    if(!flag){
        cout<<"Account does not exist..."<<"\n";
    }
}
void modify_account(int n){
    Acc acc;
    fstream File;
    bool found = false;
    File.open("bank.dat",ios::binary|ios::in|ios::out);
    if(!File){
        cout<<"File could not be openend!!Press any key...."<<"\n";
        return;
    }
    while(!File.eof() && found == false){
        File.read(reinterpret_cast<char *>(&acc) , sizeof(Acc));
        if(acc.returnAcc()== n ){
            acc.showAcc();
            cout<<"\n\nEnter the new details for the account: ";
            int pos = (-1) *static_cast<int>(sizeof(Acc));
            File.seekp(pos,ios::cur);
            File.write(reinterpret_cast<char *>(&acc) , sizeof(Acc));
            cout<<"\n\nRecord updated";
            found = true;
        }
    }
    File.close();
    if(!found){
        cout<<"Account does not exist..."<<"\n";
    }
}

void delete_account(int n){
    Acc acc;
    ifstream inFile;
    ofstream outFile;
    inFile.open("bank.dat",ios::binary);
    if(!inFile){
        cout<<"File could not be openend!!Press any key...."<<"\n";
        return;
    }
    outFile.open("Temp.dat",ios::binary);
    inFile.seekg(0,ios::beg);
    while(inFile.read(reinterpret_cast<char *>(&acc) , sizeof(Acc))){
        if(acc.returnAcc() != n){
            outFile.write(reinterpret_cast<char *>(&acc) , sizeof(Acc));
        }
    }
    inFile.close();
    outFile.close();
    remove("bank.dat");
    rename("Temp.dat","bank.dat");
    cout<<"\n\nRecord updated"<<"\n";

}
void display_all(){
    Acc acc;
    ifstream inFile;
    inFile.open("bank.dat",ios::binary);
    if(!inFile){
        cout<<"File could not be openend!!Press any key...."<<"\n";
        return;
    }
    cin.ignore();
    cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
    cout<<"====================================================\n";
    cout<<"A/c no.      NAME           Type  Balance\n";
	cout<<"====================================================\n";
	while(inFile.read(reinterpret_cast<char *>(&acc) , sizeof(Acc))){
        acc.report();
	}
	inFile.close();
}

void deposit_withdraw(int m,int n){
    int amount;
    bool found = false;
    Acc acc;
    fstream File;
    File.open("bank.dat",ios::binary|ios::in|ios::out);
    if(!File){
        cout<<"File could not be openend!!Press any key...."<<"\n";
        return;
    }
     while(!File.eof() && found == false){
        File.read(reinterpret_cast<char *>(&acc) , sizeof(Acc));
        if(acc.returnAcc()== m ){
            acc.showAcc();
            if(n == 1){
                cout<<"\n\n\tDEPOSIT MONEY\n";
                cin>>amount;
                acc.dep(amount);
            }
            if(n == 2){
                cout<<"\n\n\tWITHDRAW MONEY\n";
                cout<<"\n\n\ENTER THE AMOUNT TO BE DEPOSITED";
                cin>>amount;
                int balance = acc.returnDep()-amount;
                if((balance<500 && acc.returnType() == 'S') ||(balance<1000 && acc.returnType() == 'C') ){
                    cout<<"Insufficient balance\n";
                }
                else{
                    acc.withdraw(amount);
                }

            }
            int pos = (-1) *static_cast<int>(sizeof(Acc));
            File.seekp(pos,ios::cur);
            File.write(reinterpret_cast<char *>(&acc) , sizeof(Acc));
            cout<<"\n\nRecord updated";
            found = true;
        }
     }
        File.close();
    if(!found){
        cout<<"Account does not exist..."<<"\n";
    }
}


void welcome(){
    cout<<"\n\n\n\n\n";
    cout<<setw(68)<<"Bank Management System"<<"\n";
    cout<<"\n\n\n";
    cout<<setw(43)<<" "<<"Done by :20WH1A1256 K.Sahithi"<<"\n";
    cout<<setw(33)<<" "<<"College:BVRIT HYDERABAD College of Engineering for Women"<<"\n";
    cin.get();
}
