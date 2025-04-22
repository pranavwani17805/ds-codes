
#include <iostream>
#include <stdlib.h>
#include <string>
#define MAX 10
using namespace std;

class User 
{
    long int mobile;
    string name;
    double billamount;

    public:
    User()
    {
        mobile = 0;
        name = "";
        billamount = 0.0;
    }
    friend class Operations;
};

class Operations 
{
    User M[10];
    int n;
    public:
    Operations(int n1)
    {
        n = n1;
    }
    void accept();
    void display();
    int linear_search(long int key);
    int binary_rec(long int key, int low, int high);
    int binary(long int key, int low, int high);
    int partition(int low, int high);
    void quickSort(int low, int high);
    void adjust(int n, int i);
    void heapsort();
};

void Operations::accept()
{
    cout << "Enter the details of the users: "<<endl;
    for(int i = 0; i < n; i++)
    {
        cout << "Enter Mobile Number: ";
        cin >> M[i].mobile;
        cout << "Enter Name: ";
        cin >> M[i].name;
        cout << "Enter Bill Amount: ";
        cin >> M[i].billamount;
    }
}

void Operations::display()
{
    cout << "Mobile Number\tName\t\tBill Amount\n";
    for(int i = 0; i < n; i++)
    {
        cout << M[i].mobile << "\t" << M[i].name << "\t\t" << M[i].billamount << endl;
    }
}

int Operations::linear_search(long int key)
{
    for (int i = 0; i < n; i++) 
    {
        if (key == M[i].mobile) 
        {
            cout << "User found:\n";
            cout << "Mobile Number\tName\t\tBill Amount\n";
            cout << M[i].mobile << "\t" << M[i].name << "\t\t" << M[i].billamount << endl;
            return i;
        }
    }
    return -1;
}

int Operations::binary_rec(long int key, int low, int high)
{
    if (low <= high)
    {
        int mid = (low + high) / 2;
        if (key == M[mid].mobile)
        {
            cout << "User found:\n";
            cout << "Mobile Number\tName\t\tBill Amount\n";
            cout << M[mid].mobile << "\t" << M[mid].name << "\t\t" << M[mid].billamount << endl;
            return mid;
        }
        else if (key < M[mid].mobile)
        {
            return binary_rec(key, low, mid - 1);
        }
        else
        {
            return binary_rec(key, mid + 1, high);
        }
    }
    return -1;
}

int Operations::binary(long int key, int low, int high)
{
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (key == M[mid].mobile)
        {
            cout << "User found:\n";
            cout << "Mobile Number\tName\t\tBill Amount\n";
            cout << M[mid].mobile << "\t" << M[mid].name << "\t\t" << M[mid].billamount << endl;
            return mid;
        }
        else if (key < M[mid].mobile)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    return -1;
}


int Operations::partition(int low, int high) 
{
    int i = low - 1;
    long int piv = M[high].mobile;
    User temp;
    for(int j = low; j <= high - 1; j++)
    {
        if(M[j].mobile >= piv)
        {
            i++;
            temp = M[i];
            M[i] = M[j];
            M[j] = temp;
        }
    }
    temp = M[i + 1];
    M[i + 1] = M[high];
    M[high] = temp;
    return i + 1;
}

void Operations::quickSort(int low, int high)
{
    if(low < high)
    {
        int j = partition(low, high);
        quickSort(low, j - 1);
        quickSort(j + 1, high);
    }
}

void Operations::adjust(int n1, int i)
{
    int j;
    User temp;
    while((2 * i + 1) <= n1)
    {
        j = 2 * i + 1;
        if(((j + 1) <= n1) && (M[j + 1].billamount > M[j].billamount))
        {
            j++;
        }
        if(M[i].billamount >= M[j].billamount)
        {
            break;
        }
        else
        {
            temp = M[i];
            M[i] = M[j];
            M[j] = temp;
            i = j;
        }
    }
}

void Operations::heapsort() 
{
    int i, n1 = n;
    User temp;
    for(i = (n1 / 2) - 1; i >= 0; i--)
    {
        adjust(n1 - 1, i);
    }
    while(n1 > 0)
    {
        temp = M[0];
        M[0] = M[n1 - 1];
        M[n1 - 1] = temp;
        n1--;
        adjust(n1 - 1, 0);
    }
}

int main() 
{
    int n, ch;
    long int key;

    cout << "Enter the number of users: ";
    cin >> n;

    Operations ops(n);
    ops.accept();

    do 
    {
        cout << "\nMenu:\n";
        cout << "1. Linear Search\n";
        cout << "2. Recursive Binary Search\n";
        cout << "3. Non-Recursive Binary Search\n";
        cout << "4. Quick Sort (Descending Order by Mobile Number)\n";
        cout << "5. Heap Sort (Ascending Order by Bill Amount)\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> ch;

        switch (ch) 
        {
            case 1: 
            {
                cout << "Enter the mobile number to search: ";
                cin >> key;
                int index = ops.linear_search(key);
                if (index == -1) 
                {
                    cout << "User not found!\n";
                }
                break;
            }
            case 2: 
            {
                cout << "Enter the mobile number to search: ";
                cin >> key;
                int index = ops.binary_rec(key, 0, n - 1);
                if (index == -1) 
                {
                    cout << "User not found!\n";
                }
                break;
            }
            case 3: 
            {
                cout << "Enter the mobile number to search: ";
                cin >> key;
                int index = ops.binary(key, 0, n - 1);
                if (index == -1) 
                {
                    cout << "User not found!\n";
                }
                break;
            }
            case 4: 
            {
                cout << "Sorting users in descending order of mobile numbers using Quick Sort...\n";
                ops.quickSort(0, n - 1);
                ops.display();
                break;
            }
            case 5: 
            {
                cout << "Sorting users in ascending order of bill amounts using Heap Sort...\n";
                ops.heapsort();
                ops.display();
                break;
            }
            case 6:
                cout << "Exiting the program...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (ch != 6);
    return 0;
}