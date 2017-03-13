#ifndef hashTable_h
#define hashTable_h

template <class A, class B>
class hashTable {
    private:
    int size;
    int used_size;
    
    struct nod {
        A key;
        B value;
        nod* next;
    };
    
    nod** table;
    
    public:
    hashTable(int sz);
    ~hashTable();
    
    void setSize(int size);
    const int getSize();
    void resize();
    
    void add(A key, B value, bool ok);
    void remove(A key);
    
    bool get(A key);
    
    bool operator[](A key) { return get(key); }
};


#endif /* hashTable_h */
