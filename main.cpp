#include <iostream>
#include <fstream>
#include "hashTable.h"


int main() {
    
    std::ifstream f("hashuri.in");
    std::ofstream g("hashuri.out");
    
    hashTable<int, int> hasht(666013);
    
    int n, i, tip, x;
    
    f >> n;
    
    for (i = 1; i <= n; i++) {
        f >> tip >> x;
        
        if (tip == 1 && hasht.get(x) == 0) {
            hasht.add(x, 0, 1);
            continue;
        }
        if (tip == 2) {
            hasht.remove(x);
            continue;
        }
        if (tip == 3) {
            g << hasht.get(x) << "\n";
        }
    }
    
    f.close();
    g.close();
    return 0;
}
