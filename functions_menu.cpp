#include <iostream>
#include "../include/functions_menu.h"
using namespace std;

void display_array(double array[20], int count) {
    cout << "[ ";
    for (int i = 0; i < count; i++) {
        cout << array[i] << " ";
    }
    cout << "]" << endl;
}
