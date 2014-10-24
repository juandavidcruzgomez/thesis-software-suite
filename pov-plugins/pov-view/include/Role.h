#ifndef ROLE_H
#define ROLE_H

#include <iostream>

using namespace std;

struct Role {
    float p_index;
    float z_index;
    explicit Role(){
      p_index = 0;
      z_index = 0;
    }
    int role() const {
        int result = 0;
        //Non-hub roles
        if (z_index < 2.5 and p_index < 0.0001) {
            result = 1;
        }
        else if (z_index < 2.5 and p_index >= 0.0001 and p_index < 0.625) {
            result = 2;
        }
        else if (z_index < 2.5 and p_index >= 0.625 and p_index < 0.8) {
            result = 3;
        }
        else if (z_index < 2.5 and p_index >= 0.8) {
            result = 4;
        }
        //Hub roles
        if (z_index >= 2.5 and p_index < 0.3) {
            result = 5;
        }
        else if (z_index >= 2.5 and p_index >= 0.3 and p_index < 0.75) {
            result = 6;
        }
        else if (z_index >= 2.5 and p_index >= 0.75) {
            result = 7;
        }
        return result;
    }
    bool operator>( const Role& other ) const{
      return role() > other.role();
    }
    
    void print_role(){
      cout << "z-Index: " << z_index << ", P-index: " << p_index << ", role: " << role() << endl;
    }
};

#endif