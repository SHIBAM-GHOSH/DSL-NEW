#include<iostream>
#include<math.h>
using namespace std;
class node{
    public:
    string word;
    string meaning;
    node *next;
    node(string word,string meaning){
        this->word=word;
        this->meaning=meaning;
        this->next=nullptr;
    }
};
int hash_func(string s){
    int ans=0;
    for(int i=0;i<s.length();i++){
        int ascii=s[i];
        ans+=ascii*pow(10,i);
    }
    return ans%10;
}
class dictionary{
    node ** dict=new node*[10];
    public:
    dictionary(){
        for(int i=0;i<10;i++){
            dict[i]=nullptr;
        }
    }
    void put(string wrd,string mean,int index){
        node *n=new node(wrd,mean);
        if(dict[index]==nullptr){
            dict[index]=n;
            return;
        }
        else{
            n->next=dict[index];
            dict[index]=n;
        }
    }
    void insert(){
        string wrd,mean;
        cout<<"Enter the word you want to insert : ";
        cin>>wrd;
        cout<<"Enter the meaning of the "<<wrd<<" word : ";
        cin>>mean;
        int index=hash_func(wrd);
        put(wrd,mean,index);
        cout<<"Word index successfully."<<endl;
    }
    void search(){
        string wrd;
        cout<<"Enter the word whose meaning you want to search : ";
        cin>>wrd;
        int index=hash_func(wrd);
        node *temp=dict[index];
        while(temp!=nullptr){
            if(temp->word==wrd){
                cout<<"The meaning of "<<wrd<<" is : "<<temp->meaning<<endl;
                return ;
            }
            temp=temp->next;
        }
        cout<<"Word not found in the dictionary."<<endl;
    }
    void display(){
        cout<<"Dictionary is : "<<endl;
        cout<<"Word->Meaning"<<endl;
        for(int i=0;i<10;i++){
            node *temp=dict[i];
            cout<<"Words with hash value "<<i<<"\n"<<endl;
            while(temp!=nullptr){
                cout<<temp->word<<"->"<<temp->meaning<<endl;
                temp=temp->next;
            }
            cout<<endl;
        }
    }
};
int main(){
    dictionary d;
    int choice;
    while(true){
        cout<<"Enter your choice :\n1.Insert word\n2.Search Meaning\n3.Display Dictionary"<<endl;
        cout<<"4.Exit\n";
        cin>>choice;
        if(choice==1){
            d.insert();
        }
        else if(choice==2){
            d.search();
        }
        else if(choice==3){
            d.display();
        }
        else{
            return 0;
        }
    }
    return 0;
}