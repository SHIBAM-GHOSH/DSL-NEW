#include<iostream>
using namespace std;
class hash_table{
    int size;
    int *arr;
    public:
    hash_table(int size){
        this->size=size;
        arr=new int[size];
        for(int i=0;i<size;i++){
            arr[i]=-1;
        }
    }
    void insert(){
        cout<<"Enter the number you want to insert : ";
        int num;
        cin>>num;
        int key=num%10;
        if(arr[key]==-1){
            arr[key]=num;
            return;
        }
        else{
            int i=0;
            while(i<=10){
                key=(num%10+i*i)%10;
                if(arr[key]==-1){
                    arr[key]=num;
                    cout<<"Number inserted."<<endl;
                    return;
                }
                i+=1;
            }
        }
        cout<<"Hashtable is full."<<endl;
    }
    void display(){
        cout<<"Hashtable is : ";
        for(int i=0;i<size;i++){
            cout<<arr[i]<<" ";
        }
        cout<<"\n\n";
    }
};
int main(){
    hash_table h(10);
    while(1){
        cout<<"Option : \n1.Insert\n2.Display\n3.Exit\n";
        int opt;
        cin>>opt;
        if(opt==1){
            h.insert();
        }
        else if(opt==2){
            h.display();
        }
        else{
            return 0;
        }
    }
    return 0;
}