/**
 The MIT License (MIT)

 Copyright (c) 2012 Juan David Cruz Gómez and Telecom - Bretagne 
 juan.cruzgomez@telecom-bretagne.eu

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
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
