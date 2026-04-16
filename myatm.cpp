#include<iostream>
#include<string>
#include<vector>
using namespace std;
//定义account类
class account{
    private:
    int id;
    string name;
    int money;

    public:
    account(): id(0), name("None"), money(0) {}; 
    account(int a,string b,int c);
    int return_id() const;            //小贴士：在只读函数后添加const提升代码健壮性
    string return_name() const;
    int return_money() const;
    int deposit(int a);
    int withdraw(int a);
};

//account类的实现
account::account(int a,string b,int c)
    : id(a), name(b), money(c) {};
int account::return_id() const{
    return id;
}
string account::return_name() const{
    return name;
}
int account::return_money() const{
    return money;
}
int account::deposit(int a){
    money+=a;
}
int account::withdraw(int a){
    money-=a;
}

//定义ATM类
class ATM{
    private:
    vector<account> vec_account;         //定义一个叫做vec_account的account数组

    public:
    void creat_account();
    void get_account();
    void deposit();
    void withdraw();
    void display_all_account() const;

    private:
    account *find_account(string a){     //这是一个叫做find_account的函数，目的是为了返回一个地址！
        for(auto &v: vec_account){       //for each循环，v前面用&引用是为了减少复制粘贴，防止数据出现差错
            if(v.return_name()==a){
                return &v;               //返回地址
            }
        }
        return nullptr;
    }
};

//ATM类的实现
void ATM::creat_account(){
    int a;string b;int c;
    cout<<"请输入新账户ID,姓名及余额"<<endl;
    cin>>a>>b>>c;
    vec_account.push_back(account(a,b,c));
    cout<<"创建成功"<<endl;
}
void ATM::get_account(){
    string a;
    account *pointer;
    cout<<"请输入查询账户姓名"<<endl;
    cin>>a;
    pointer=find_account(a);             //用pointer接受返回的地址
    if(pointer==nullptr){
        cout<<"查询失败，未找到您的账户"<<endl;
    }
    else{
        cout<<"查询成功"<<endl;
        cout<<"您的账户ID为:"<<pointer->return_id()<<endl;
        cout<<"您的账户姓名为:"<<pointer->return_name()<<endl;
        cout<<"您的账户余额为:"<<pointer->return_money()<<endl;
    }
}
void ATM::deposit(){
    string a;
    account *pointer;
    cout<<"请输入查询账户姓名"<<endl;
    cin>>a;
    pointer=find_account(a);
    if(pointer==nullptr){
        cout<<"查询失败，未找到您的账户"<<endl;
    }
    else{
        cout<<"查询成功"<<endl;
        cout<<"您的账户余额为:"<<pointer->return_money()<<endl;
        
        int b;
        cout<<"请输入存入金额:"<<endl;
        cin>>b;
        pointer->deposit(b);
        cout<<"存款成功，您的账户余额为:"<<pointer->return_money()<<endl;
    }
}
void ATM::withdraw(){
    string a;
    account *pointer;
    cout<<"请输入查询账户姓名"<<endl;
    cin>>a;
    pointer=find_account(a);
    if(pointer==nullptr){
        cout<<"查询失败，未找到您的账户"<<endl;
    }
    else{
        cout<<"查询成功"<<endl;
        cout<<"您的账户余额为:"<<pointer->return_money()<<endl;
        
        int b;
        cout<<"请输入取出金额:"<<endl;
        cin>>b;
        pointer->withdraw(b);
        cout<<"取款成功，您的账户余额为:"<<pointer->return_money()<<endl;
    }
}
void ATM::display_all_account() const{
    for(auto &v: vec_account){
        cout<<"账户ID:"<<v.return_id()<<" 账户姓名:"<<v.return_name()<<" 账户余额:"<<v.return_money()<<endl;
    }
}

//系统总实现
int main(){
    int w=1;
    ATM atm;

    while(w){
        cout<<"欢迎使用豆子的ATM系统"<<endl;
        cout<<"输入1:创建账户"<<endl;
        cout<<"输入2:查询账户"<<endl;
        cout<<"输入3:账户存款"<<endl;
        cout<<"输入4:账户取款"<<endl;
        cout<<"输入5:显示所有账户"<<endl;
        cout<<"输入0:退出账户"<<endl;
        cin>>w;
        switch(w){
            case 1:{
                atm.creat_account();
                cin.get();
                cout<<"按回车键继续"<<endl;
                cin.get();
                break;
            }
            case 2:{
                atm.get_account();
                cin.get();
                cout<<"按回车键继续"<<endl;
                cin.get();
                break;
            }
            case 3:{
                atm.deposit();
                cin.get();
                cout<<"按回车键继续"<<endl;
                cin.get();
                break;
            }
            case 4:{
                atm.withdraw();
                cin.get();
                cout<<"按回车键继续"<<endl;
                cin.get();
                break;
            }
            case 5:{
                atm.display_all_account();
                cin.get();
                cout<<"按回车键继续"<<endl;
                cin.get();
                break;
            }
            case 0:{
                cout<<"感谢使用本系统，祝你天天开心"<<endl;
                break;
            }
            default:{
                cout<<"输入错误，请重新输入"<<endl;
                cin.get();
                cout<<"按回车键继续"<<endl;
                cin.get();
                break;
            }
        }
        system("clear");
    }
    
    return 0;
}