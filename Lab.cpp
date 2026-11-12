#include <iostream>
using namespace std;

int main()
{
    int n;

    cout << "Size of the Array is: ";
    cin >> n;

    int a[100];

    cout << "Enter the Array: ";

    for(int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    for(int i = 1; i < n; i++)
    {
        int key = a[i];
        int j = i - 1;

        while(j >= 0 && a[j] > key)
        {
            a[j + 1] = a[j];
            j--;
        }

        a[j + 1] = key;
    }

    cout << "Sorted Array: ";

    for(int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }

    return 0;
}