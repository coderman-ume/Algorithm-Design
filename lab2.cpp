#include <iostream>
using namespace std;

int main()
{
    int n;

    cout << "Array input: ";
    cin >> n;

    int a[100];

    cout << "Enter the array: ";

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    for (int i = 0; i < n - 1; i++)
    {
        int min = i;

        for (int j = i + 1; j < n; j++)
        {
            if (a[j] < a[min])
            {
                min = j;
            }
        }

        int temp = a[i];
        a[i] = a[min];
        a[min] = temp;
    }

    cout << "Sorted array: ";

    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }

    return 0;
}