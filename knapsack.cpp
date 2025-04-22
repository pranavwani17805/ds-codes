#include <iostream>
using namespace std;

int knapsack(int W, int wt[], int val[], int n)
{
    int B[n + 1][W + 1];

    for (int w = 0; w <= W; w++) 
    {
        B[0][w] = 0;
    }

    for (int i = 1; i <= n; i++) 
    {
        B[i][0] = 0;
    }

    for (int i = 1; i <= n; i++)
    {
        for (int w = 0; w <= W; w++)
        {
            if (wt[i - 1] <= w)
            {
                if (val[i - 1] + B[i - 1][w - wt[i - 1]] > B[i - 1][w])
                {
                    B[i][w] = val[i - 1] + B[i - 1][w - wt[i - 1]];
                }
                else
                {
                    B[i][w] = B[i - 1][w];
                }
            }
            else
            {
                B[i][w] = B[i - 1][w];
            }
        }
    }

    return B[n][W];
}

int main()
{
    int n, W;
    cout << "Enter number of items: ";
    cin >> n;
    cout << "Enter knapsack capacity: ";
    cin >> W;

    int val[n], wt[n];

    cout << "Enter values of items: ";
    for (int i = 0; i < n; i++)
    {
        cin >> val[i];
    }
    cout << "Enter weights of items: ";
    for (int i = 0; i < n; i++)
    {
        cin >> wt[i];
    }
    cout << "Maximum value in Knapsack = " << knapsack(W, wt, val, n) << endl;

    return 0;
}