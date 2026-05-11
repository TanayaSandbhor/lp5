#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

int main()
{
    int n;

    cout << "Enter size: ";
    cin >> n;

    // Check for valid size
    if(n <= 0)
    {
        cout << "Invalid size!" << endl;
        return 0;
    }

    vector<int> a(n);

    cout << "Enter array elements: ";
    for(int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    int sum = 0;
    int min_val = a[0];
    int max_val = a[0];

    // Parallel Sum
    #pragma omp parallel for reduction(+:sum)
    for(int i = 0; i < n; i++)
    {
        sum += a[i];
    }

    // Parallel Minimum
    #pragma omp parallel for reduction(min:min_val)
    for(int i = 0; i < n; i++)
    {
        if(a[i] < min_val)
        {
            min_val = a[i];
        }
    }

    // Parallel Maximum
    #pragma omp parallel for reduction(max:max_val)
    for(int i = 0; i < n; i++)
    {
        if(a[i] > max_val)
        {
            max_val = a[i];
        }
    }

    float avg = (float)sum / n;

    cout << "\nResults:" << endl;
    cout << "Sum = " << sum << endl;
    cout << "Minimum = " << min_val << endl;
    cout << "Maximum = " << max_val << endl;
    cout << "Average = " << avg << endl;

    return 0;
}
