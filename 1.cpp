#include<iostream>
#include<string>
#include<vector>
using namespace std;
//定义account
class account{
    protected:
    string name;
    string id;
    int money;

    public:
    account();
    account(string a,string b,int c);
    string return_account_name();
    string return_account_id();
    int return_account_money();
    virtual void display_information() const ;
    void deposit();
    void withdraw();
};

//account的实现
account::account(): name("None"), id("0000"), money(0){}
account::account(string a,string b,int c): name(a), id(b), money(c){}
string account::return_account_name(){return name;}
string account::return_account_id(){return id;}
int account::return_account_money(){return money;}
void account::display_information() const {
    cout << "===== 账户信息 =====" << endl;
    cout << "账户持有人：" << name << endl;
    cout << "账号：" << id << endl;
    cout << "账户余额：" << money << " 元" << endl;
}
void account::deposit() {
    int amount;
    cout<<"请输入存款金额"<<endl;
    cin>>amount;
    if (amount > 0) {
        money += amount;
        cout << "存款成功！当前余额："<< money << endl;
    } 
    else {
        cout << "存款金额必须大于0！" << endl;
    }
}
void account::withdraw() {
    int amount;
    cout<<"请输入取款金额"<<endl;
    cin>>amount;
    if (amount > 0) {
        money -= amount;
        cout << "取款成功！当前余额："<< money << endl;
    } 
    else {
        cout << "取款金额必须大于0！" << endl;
    }
}

//定义account的子类一：saving_account
class saving_account: public account{
    protected:
    int interestrate;
    double interest;

    public:
    saving_account();
    saving_account(string a,string b,int c,int d);
    int return_interestrate();
    double return_interest();
    void diplay_interest()  ;
    void display_information() const ;
};

//saving_account的实现
saving_account::saving_account():saving_account::account(), interestrate(0), interest(0){}
saving_account::saving_account(string a,string b,int c,int d): account(a, b, c), interestrate(d){interest=saving_account::return_account_money()*interestrate/100;}
int saving_account::return_interestrate(){return interestrate;}
double saving_account::return_interest(){return interest;}
void saving_account::display_information() const {
    cout << "===== 账户信息 =====" << endl;
    cout << "账户持有人：" << name << endl;
    cout << "账号：" << id << endl;
    cout << "账户余额：" << money << " 元" << endl;
    cout << "年利率：" <<  interestrate << "%" << endl;
    cout << "年利息：" <<  interest << "元" << endl;
}

//定义account的子类二：credit_account
class credit_account: public account{
    protected:
    int outstanding_balance;
    int credit_limit;

    public:
    credit_account(): account(), credit_limit(0), outstanding_balance(0) {}
    credit_account(string name, string id, int limit): account(name, id, 0), credit_limit(limit), outstanding_balance(0) {}
    void pay_bill(){
        int tem;
        cout<<"请输入还款金额"<<endl;
        cin>>tem;
        if(tem <= outstanding_balance){
            cout << "信用卡还款成功！消费金额："<< tem << " 元，当前欠款：" << outstanding_balance-tem << " 元" << endl;
            outstanding_balance -= tem;
        }
        else{
            cout << "Insufficient funds to pay the bill" << endl;
        }
    }
    void make_purchase(){
        int tem;
        cout<<"请输入借款金额"<<endl;
        cin>>tem;
        if(tem <= credit_limit-outstanding_balance){
            cout << "信用卡借款成功！借款金额："<< tem << " 元，当前欠款：" << outstanding_balance+tem << " 元" << endl;
            outstanding_balance += tem;
        }
        else{
            cout << "Purchase exceeds credit limit" << endl;
        }
    }
    void display_information() const override {
        cout << "=====信用卡账户====="<<endl;
        cout << "姓名：" << name << "账号：" << id << endl;
        cout << "信用额度：" << credit_limit << endl;
        cout << "当前欠款：" << outstanding_balance << endl;
    }
};

int main(){
    int w=1;
    vector<account*> acc;                               //这里account后要带指针*，因为acc中有子类，使得vector可以储存子类的地址（但是显示基类内容）
    account* finder(vector<account*>&acc,string a);     //pointer（基类指针）

    while(w){
        cout<<"=====欢迎使用巴豆的银行帐户系统====="<<endl;
        cout<<"1.创建账户"<<endl;
        cout<<"2.账户管理"<<endl;
        cout<<"0.退出系统"<<endl;
        cin>>w;
        switch(w){
            case 1:{
                int tem=1;
                while(tem){
                    cout<<"=====请选择创建的账户====="<<endl;
                    cout<<"1.创建储蓄卡账户"<<endl;
                    cout<<"2.创建信用卡账户"<<endl;
                    cout<<"0.返回上一页"<<endl;
                    cin>>tem;

                    switch(tem){
                        case 1:{
                            string a,b; int c,d;
                            cout<<"请输入储蓄卡账户姓名"<<endl;
                            cin>>a;
                            cout<<"请输入储蓄卡账户卡号"<<endl;
                            cin>>b;
                            cout<<"请输入储蓄卡账户余额"<<endl;
                            cin>>c;
                            cout<<"请输入储蓄卡账户利率"<<endl;
                            cin>>d;
                            acc.push_back(new saving_account(a,b,c,d));
                            cin.get();
                            cout<<"创建账户成功，按回车键继续"<<endl;
                            cin.get();
                            break;
                        }
                        case 2:{
                            string a,b; int c;
                            cout<<"请输入信用卡账户姓名"<<endl;
                            cin>>a;
                            cout<<"请输入信用卡账户卡号"<<endl;
                            cin>>b;
                            cout<<"请输入信用卡账户额度"<<endl;
                            cin>>c;
                            acc.push_back(new credit_account(a,b,c));
                            cin.get();
                            cout<<"创建账户成功，按回车键继续"<<endl;
                            cin.get();
                            break;
                        }
                        case 0:{
                            cin.get();
                            cout<<"按回车键继续"<<endl;
                            cin.get();
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
                break;
            }
            case 2:{
                int tem=1;
                while(tem){
                    cout<<"=====请选择操作的账户类型====="<<endl;
                    cout<<"1.储蓄卡账户操作"<<endl;
                    cout<<"2.信用卡账户操作"<<endl;
                    cout<<"0.返回上一页"<<endl;
                    cin>>tem;

                    switch(tem){
                        case 1:{
                            string a;
                            cout<<"请输入账户姓名"<<endl;
                            cin>>a;
                            
                            account* pointer=finder(acc,a);
                            if(pointer==nullptr){
                                cout<<"查询失败"<<endl;
                                cin.get();
                                cout<<"按回车键继续"<<endl;
                                cin.get();
                            }
                            else{
                                saving_account* s_ptr =static_cast<saving_account*>(pointer);   //将基类指针转化为子类指针
                                cin.get();
                                cout<<"查询成功,按回车键进入储蓄卡操作界面"<<endl;
                                cin.get();
                                int tem2=1;
                                while(tem2){
                                    cout<<"=====储蓄卡操作界面====="<<endl;
                                    cout<<"1.查询储蓄卡账户信息"<<endl;
                                    cout<<"2.储蓄卡取款"<<endl;
                                    cout<<"3.储蓄卡存款"<<endl;
                                    cout<<"0.返回初始界面"<<endl;
                                    cin>>tem2;

                                    switch(tem2){
                                        case 1:{
                                            s_ptr->display_information();
                                            cin.get();
                                            cout<<"按回车键继续"<<endl;
                                            cin.get();
                                            break;
                                        };
                                        case 2:{
                                            s_ptr->withdraw();
                                            cin.get();
                                            cout<<"按回车键继续"<<endl;
                                            cin.get();
                                            break;
                                        };
                                        case 3:{
                                            s_ptr->deposit();
                                            cin.get();
                                            cout<<"按回车键继续"<<endl;
                                            cin.get();
                                            break;
                                        };
                                        case 0:{
                                            cin.get();
                                            cout<<"按回车键继续"<<endl;
                                            cin.get();
                                            break;
                                        }
                                    }
                                    system("clear");
                                }
                            }
                            break;
                        }
                        case 2:{
                            string a;
                            cout<<"请输入账户姓名"<<endl;
                            cin>>a;
                            
                            account* pointer=finder(acc,a);
                            if(pointer==nullptr){
                                cout<<"查询失败"<<endl;
                                cin.get();
                                cout<<"按回车键继续"<<endl;
                                cin.get();
                            }
                            else{
                                credit_account* c_ptr = static_cast<credit_account*>(pointer);
                                cin.get();
                                cout<<"查询成功,按回车键进入信用卡操作界面"<<endl;
                                cin.get();
                                int tem2=1;
                                while(tem2){
                                    cout<<"=====信用卡操作界面====="<<endl;
                                    cout<<"1.查询信用卡账户信息"<<endl;
                                    cout<<"2.信用卡取款"<<endl;
                                    cout<<"3.信用卡存款"<<endl;
                                    cout<<"0.返回初始界面"<<endl;
                                    cin>>tem2;

                                    switch(tem2){
                                        case 1:{
                                            c_ptr->display_information();
                                            cin.get();
                                            cout<<"按回车键继续"<<endl;
                                            cin.get();
                                            break;
                                        };
                                        case 2:{
                                            c_ptr->make_purchase();
                                            cin.get();
                                            cout<<"按回车键继续"<<endl;
                                            cin.get();
                                            break;
                                        };
                                        case 3:{
                                            c_ptr->pay_bill();
                                            cin.get();
                                            cout<<"按回车键继续"<<endl;
                                            cin.get();
                                            break;
                                        };
                                        case 0:{
                                            cin.get();
                                            cout<<"按回车键继续"<<endl;
                                            cin.get();
                                            break;
                                        }
                                    }
                                    system("clear");
                                }
                            }
                            break;
                        }
                        case 0:{
                            cin.get();
                            cout<<"按回车键继续"<<endl;
                            cin.get();
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
            }
            case 0:{
                cout<<"感谢使用本系统，祝你天天开心！"<<endl;
                cin.get();
                cout<<"按回车键继续"<<endl;
                cin.get();
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

    for(auto v: acc){
        delete v;                  //释放vector
    }
    acc.clear();
    return 0;
}

account* finder(vector<account*> &acc,string a){
    for(auto &v: acc){
        if(v->return_account_name()==a){
            return v;
        }
    }
    return nullptr;
}