#include <iostream>
#include <climits>
using namespace std;

class Graph 
{
    int n;   
    int weight;
    int costMatrix[20][20];
    int nearest[20];
    int t[20][2];
    int mincost;

    public:
    Graph(int size);
    void create();
    void displayCostMatrix();
    int prims(int start_id);
    void displayNearest();
};

Graph :: Graph(int size) 
{
    n = size;
    mincost = 0;

    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            costMatrix[i][j] = INT_MAX;
        }
    }
}

void Graph :: create() 
{
    char ch;
    cout << "Enter the number of vertices: ";
    cin >> n;

    for (int i = 0; i < n; i++) 
    {
        do 
        {
            int fid;
            cout << "Enter data of an edge for vertex " << i << ": ";
            cin >> fid;
            if (fid == i) 
            {
                cout << "Self-Loop not allowed!!!!" << endl;
            } 
            else 
            {
                cout<<"Enter the cost of the edge: ";
                cin>>weight;
                costMatrix[i][fid] = weight;
                costMatrix[fid][i] = weight;
            }
            cout << "Do you want to add another edge for vertex " << i << " (y/n): ";
            cin >> ch;
        } while (ch == 'y' || ch == 'Y');
    }
}

void Graph :: displayCostMatrix() 
{
    cout << "Cost Matrix:" << endl;
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            if (costMatrix[i][j] == INT_MAX) 
            {
                cout << "inf\t";
            } 
            else 
            {
                cout << costMatrix[i][j] << " \t";
            }
        }
        cout << endl;
    }
}

int Graph :: prims(int start_id)
{
    nearest[start_id] = -1;
    for (int i = 0; i < n; i++) 
    {
        if (i != start_id)
        {
            nearest[i] = start_id;
        }
    }

    int r = 0;
    for (int i = 1; i < n; i++)
    {
        int min = INT_MAX;
        int j = -1;

        for (int k = 0; k < n; k++)
        {
            if (nearest[k] != -1 && costMatrix[k][nearest[k]] < min)
            {
                j = k;
                min = costMatrix[k][nearest[k]];
            }
        }

        if (j != -1)
        {
            t[r][0] = nearest[j];
            t[r][1] = j;
            mincost += min;
            nearest[j] = -1;

            for (int k = 0; k < n; k++)
            {
                if (nearest[k] != -1 && costMatrix[k][nearest[k]] > costMatrix[k][j])
                {
                    nearest[k] = j;
                }
            }
            r++;
        }
    }
    return mincost;
}

void Graph :: displayNearest()
{
    cout << "\nMinimum Spanning Tree Edges:\n";
    for (int i = 0; i < n - 1; i++) 
    {
        cout << "Edge " << t[i][0] << " - " << t[i][1] 
            << " : Weight " << costMatrix[t[i][0]][t[i][1]] << endl;
    }
    cout << "Total MST Cost: " << mincost << endl;
}

int main() 
{
    int size;
    cout << "Enter the number of vertices: ";
    cin >> size;

    Graph g(size);
    g.create();
    g.displayCostMatrix();

    int start_id;
    cout << "Enter the start ID for Prim's algorithm: ";
    cin >> start_id;
    g.prims(start_id);
    g.displayNearest();

    return 0;
}