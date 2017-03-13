//
//  hashTable.cpp
//  Hash Table
//
//  Created by Toma Radu-Petrescu on 13/03/2017.
//  Copyright © 2017 Toma Radu-Petrescu. All rights reserved.
//

#include "hashTable.h"
#include <iostream>

template <class A, class B>
hashTable<A, B>::hashTable(int sz) {
    size = sz;
    used_size = 0;
    table = new nod*[size]();
}

template <class A, class B>
hashTable<A, B>::~hashTable() {
    int i;
    nod *c, *aux;
    
    for (i = 0; i < size; i++) {
        if (table[i] != NULL) {
            c = table[i];
            while (c != NULL) {
                aux = c->next;
                delete c;
                c = aux;
            }
        }
    }
    delete[] table;
}

template <class A, class B>
void hashTable<A, B>::setSize(int size2) {
    size = size2;
}

template <class A, class B>
const int hashTable<A, B>::getSize() {
    return size;
}

template <class A, class B>
void hashTable<A, B>::add(A key, B value, bool ok) {
    nod* c;
    int hash;
    
    hash = key() % size;
    
    c = table[hash];
    
    if (used_size < size / 2) {
        if (c == 0) {
            c = new nod;
            c->value = value;
            c->key = key;
            c->next = 0;
            table[hash] = c;
        } else {
            c = new nod;
            c->value = value;
            c->key = key;
            c->next = table[hash];
            table[hash] = c;
        }
        used_size++;
        if (ok == 0)
        std::cout << "Added element." << std::endl;
    } else {
        resize();
        // std::cout<<"Table resized!"<<std::endl;
        // std::cout<<"New size: "<<size<<std::endl;
        add(key, value, 0);
        if (ok == 0)
        std::cout << "Added element." << std::endl;
    }
}

template <>
void hashTable<int, int>::add(int key, int value, bool ok) {
    nod* c;
    int hash;
    
    hash = key % size;
    
    c = table[hash];
    
    if (used_size < size / 2) {
        if (c == 0) {
            c = new nod;
            c->value = value;
            c->key = key;
            c->next = 0;
            table[hash] = c;
        } else {
            c = new nod;
            c->value = value;
            c->key = key;
            c->next = table[hash];
            table[hash] = c;
        }
        used_size++;
        if (ok == 0)
        std::cout << "Added element." << std::endl;
    } else {
        resize();
        // std::cout<<"Table resized!"<<std::endl;
        // std::cout<<"New size: "<<size<<std::endl;
        add(key, value, 0);
        if (ok == 0)
        std::cout << "Added element." << std::endl;
    }
}

template <class A, class B>
void hashTable<A, B>::remove(A key) {
    nod *c, *u = NULL, *aux;
    int hash;
    
    hash = key() % size;
    c = table[hash];
    if (c == 0) {
        // std::cout<<"Nimic de sters.";
    } else {
        if (c->key == key) {
            aux = c;
            table[hash] = c->next;
            delete aux;
            //      std::cout<<"S-a sters.";
            return;
        }
        while (c->next != 0) {
            if (c->next->key == key) {
                aux = c->next;
                c->next = c->next->next;
                delete aux;
                //        std::cout<<"Sters!";
                return;
            }
            if (c->next->next == 0)
            u = c;
            c = c->next;
        }
        
        if (c->key == key) {
            delete c;
            u->next = 0;
            //      std::cout<<"Sters!";
            return;
        }
        //      std::cout<<"Nimic de sters.";
    }
}

template <>
void hashTable<int, int>::remove(int key) {
    nod *c, *u = NULL, *aux;
    int hash;
    
    hash = key % size;
    c = table[hash];
    if (c == 0) {
        // std::cout<<"Nimic de sters.";
    } else {
        if (c->key == key) {
            aux = c;
            table[hash] = c->next;
            delete aux;
            //      std::cout<<"S-a sters.";
            return;
        }
        while (c->next != 0) {
            if (c->next->key == key) {
                aux = c->next;
                c->next = c->next->next;
                delete aux;
                //        std::cout<<"Sters!";
                return;
            }
            if (c->next->next == 0)
            u = c;
            c = c->next;
        }
        
        if (c->key == key) {
            delete c;
            u->next = 0;
            //      std::cout<<"Sters!";
            return;
        }
        //      std::cout<<"Nimic de sters.";
    }
}

template <class A, class B>
bool hashTable<A, B>::get(A key) {
    int hash;
    nod* value;
    
    hash = key() % size;
    
    value = table[hash];
    
    while (value != 0) {
        if (value->key == key) {
            // std::cout<<"S-a gasit: ";
            return true;
        }
        value = value->next;
    }
    
    // std::cout<<"NU s-a gasit!\n";
    return false;
}

template <>
bool hashTable<int, int>::get(int key) {
    int hash;
    nod* value;
    
    hash = key % size;
    
    value = table[hash];
    
    while (value != 0) {
        if (value->key == key) {
            // std::cout<<"S-a gasit: ";
            return true;
        }
        value = value->next;
    }
    
    // std::cout<<"NU s-a gasit!\n";
    return false;
}

template <class A, class B>
void hashTable<A, B>::resize() {
    nod *c, *aux;
    int i;
    
    hashTable<A, B> newhash(2 * size);
    
    for (i = 0; i < size; i++) {
        c = table[i];
        while (c != NULL) {
            newhash.add(c->key, c->value, 1);
            c = c->next;
        }
    }
    
    for (i = 0; i < size; i++) {
        if (table[i] != NULL) {
            c = table[i];
            while (c != NULL) {
                aux = c->next;
                delete c;
                c = aux;
            }
        }
    }
    delete[] table;
    
    size = newhash.size;
    used_size = 0;
    table = new nod*[size]();
    
    for (i = 0; i < size; i++) {
        c = newhash.table[i];
        
        while (c != NULL) {
            add(c->key, c->value, 1);
            c = c->next;
        }
    }
}

