#include <iostream>
using namespace std;

int main()
{
    int size = 5;
    int numbers[5];


    for (int i = 0; i < size; i++)
    {
        cin >> numbers[i];
    }


    for (int pass = 0; pass < size - 1; pass++)
    {
        for (int index = 0; index < size - pass - 1; index++)
        {
            if (numbers[index] > numbers[index + 1])
            {
                int swapValue = numbers[index];
                numbers[index] = numbers[index + 1];
                numbers[index + 1] = swapValue;
            }
        }
    }


    for (int i = 0; i < size; i++)
    {
        cout << numbers[i] << " ";
    }

    return 0;
}
