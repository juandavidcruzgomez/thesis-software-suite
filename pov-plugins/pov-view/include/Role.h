/**
 Copyright (c) 2014 Juan David Cruz Gómez and Telecom - Bretagne

 juan.cruzgomez@telecom-bretagne.eu 
 juandavidcruz@gmail.com

 Licensed under the EUPL, Version 1.2 or – as soon theywill be approved 
 by the European Commission - subsequent versions of the 
 EUPL (the "Licence");

 You may not use this work except in compliance with the Licence.
 You may obtain a copy of the Licence at:

    https://joinup.ec.europa.eu/software/page/eupl5
  
 Unless required by applicable law or agreed to inwriting, software 
 distributed under the Licence isdistributed on an *"AS IS"* basis,
 *WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND*, either express or implied.
 See the Licence for the specific language governing permissions and limitations 
 under the Licence.
*/
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
