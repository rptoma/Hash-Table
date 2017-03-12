#include <iostream>
#include <fstream>

std::ifstream f("hashuri.in");
std::ofstream g("hashuri.out");

template <class A, class B> class hashTable{
private:
    int size;
    int used_size;
    
    struct nod{
        A key;
        B value;
        nod *next;
    };
    
    nod **table;
    
public:
    
    hashTable(int sz);
    ~hashTable();
    
    void setSize(int size);
    const int getSize();
    void resize();
    
    void add(A key, B value, bool ok);
    void remove(A key);
    
    bool get(A key);
    
    bool operator[](A key){
        return get(key);
    }
    
};

template <class A, class B> hashTable<A,B>::hashTable(int sz){
    size=sz;
    used_size=0;
    table=new nod*[size]();
}

template <class A, class B> hashTable<A,B>::~hashTable(){
    int i;
    nod *c,*aux;
    
    for(i=0;i<size;i++){
        if(table[i]!=NULL){
            c=table[i];
            while(c!=NULL){
                aux=c->next;
                delete c;
                c=aux;
            }
        }
    }
    delete[] table;
}


template <class A, class B> void hashTable<A,B>::setSize(int size2){
    size=size2;
}

template <class A, class B> const int hashTable<A,B>::getSize(){
    return size;
}

template <class A, class B> void hashTable<A,B>::add(A key, B value, bool ok){
    nod *c;
    int hash;
    
    hash=key()%size;
    
    c=table[hash];
    
    if(used_size<size/2){
        if(c==0){
            c=new nod;
            c->value=value;
            c->key=key;
            c->next=0;
            table[hash]=c;
        }
        else{
            c=new nod;
            c->value=value;
            c->key=key;
            c->next=table[hash];
            table[hash]=c;
        }
        used_size++;
        if(ok==0) std::cout<<"Added element."<<std::endl;
    }
    else{
        resize();
        //std::cout<<"Table resized!"<<std::endl;
        //std::cout<<"New size: "<<size<<std::endl;
        add(key, value, 0);
        if(ok==0) std::cout<<"Added element."<<std::endl;
    }
}

template<> void hashTable<int,int>::add(int key, int value, bool ok){
    nod *c;
    int hash;
    
    hash=key%size;
    
    c=table[hash];
    
    if(used_size<size/2){
        if(c==0){
            c=new nod;
            c->value=value;
            c->key=key;
            c->next=0;
            table[hash]=c;
        }
        else{
            c=new nod;
            c->value=value;
            c->key=key;
            c->next=table[hash];
            table[hash]=c;
        }
        used_size++;
        if(ok==0) std::cout<<"Added element."<<std::endl;
    }
    else{
        resize();
        //std::cout<<"Table resized!"<<std::endl;
        //std::cout<<"New size: "<<size<<std::endl;
        add(key, value, 0);
        if(ok==0) std::cout<<"Added element."<<std::endl;
    }

}

template <class A, class B> void hashTable<A,B>::remove(A key){
    nod *c, *u = NULL, *aux;
    int hash;
    
    hash=key()%size;
    c=table[hash];
    if(c==0){
        // std::cout<<"Nimic de sters.";
    }
    else{
        if(c->key==key){
            aux=c;
            table[hash]=c->next;
            delete aux;
            //      std::cout<<"S-a sters.";
            return;
        }
        while(c->next!=0){
            if(c->next->key==key){
                aux=c->next;
                c->next=c->next->next;
                delete aux;
                //        std::cout<<"Sters!";
                return;
            }
            if(c->next->next==0) u=c;
            c=c->next;
        }
        
        if(c->key==key){
            delete c;
            u->next=0;
            //      std::cout<<"Sters!";
            return;
        }
        //      std::cout<<"Nimic de sters.";
    }
}

template<> void hashTable<int,int>::remove(int key){
    nod *c, *u = NULL, *aux;
    int hash;
    
    hash=key%size;
    c=table[hash];
    if(c==0){
        // std::cout<<"Nimic de sters.";
    }
    else{
        if(c->key==key){
            aux=c;
            table[hash]=c->next;
            delete aux;
            //      std::cout<<"S-a sters.";
            return;
        }
        while(c->next!=0){
            if(c->next->key==key){
                aux=c->next;
                c->next=c->next->next;
                delete aux;
                //        std::cout<<"Sters!";
                return;
            }
            if(c->next->next==0) u=c;
            c=c->next;
        }
        
        if(c->key==key){
            delete c;
            u->next=0;
            //      std::cout<<"Sters!";
            return;
        }
        //      std::cout<<"Nimic de sters.";
    }
}


template <class A, class B> bool hashTable<A,B>::get(A key){
    int hash;
    nod *value;
    
    hash=key()%size;
    
    value=table[hash];
    
    while(value!=0){
        if(value->key==key){
            //std::cout<<"S-a gasit: ";
            return true;
        }
        value=value->next;
    }
    
    //std::cout<<"NU s-a gasit!\n";
    return false;
}

template<> bool hashTable<int,int>::get(int key){
    int hash;
    nod *value;
    
    hash=key%size;
    
    value=table[hash];
    
    while(value!=0){
        if(value->key==key){
            //std::cout<<"S-a gasit: ";
            return true;
        }
        value=value->next;
    }
    
    //std::cout<<"NU s-a gasit!\n";
    return false;
}


template <class A, class B> void hashTable<A,B>::resize(){
    nod *c,*aux;
    int i;
    
    hashTable<A,B> newhash(2*size);
    
    for(i=0;i<size;i++){
        c=table[i];
        while(c!=NULL){
            newhash.add(c->key, c->value,1);
            c=c->next;
        }
    }
    
    for(i=0;i<size;i++){
        if(table[i]!=NULL){
            c=table[i];
            while(c!=NULL){
                aux=c->next;
                delete c;
                c=aux;
            }
        }
    }
    delete[] table;
    
    
    size=newhash.size;
    used_size=0;
    table=new nod*[size]();
    
    for(i=0;i<size;i++){
        
        c=newhash.table[i];
        
        while(c!=NULL){
            add(c->key,c->value,1);
            c=c->next;
        }
    }
}


int main() {

    hashTable<int, int> hasht(666013);
    
    int n,i,tip, x;
    
    f>>n;

    for (i = 1; i <= n; i++)
    {
        f>>tip>>x;
        
        if(tip==1 && hasht.get(x)==0){
            hasht.add(x, 0, 1);
            continue;
        }
        if(tip==2){
            hasht.remove(x);
            continue;
        }
        if(tip==3){
            g<<hasht.get(x)<<"\n";
        }
    }
    
    f.close();
    g.close();
    return 0;
}
