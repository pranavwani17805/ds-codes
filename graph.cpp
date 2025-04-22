#include<iostream>
#include<string>
using namespace std;

class Node
{
    string name;
    int id;
    Node *next;

    friend class Graph;
    friend class Queue;
    friend class Stack;
};

class Queue
{
    int q[20];
    int front, rear;
    friend class BFS;
    public:
    Queue()
    {
        front = rear = -1;
    }
    void insert(int);
    int del();
    int empty();
};

void Queue :: insert(int temp)
{
    rear++;
    q[rear] = temp;
}

int Queue :: del()
{
    front++;
    return q[front];
}

int Queue :: empty()
{
    if(front == rear)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

class Stack 
{
    int s[20];
    int top;
    public:
    Stack() 
    {
        top = -1;
    }
    void push(int);
    int pop();
    int empty();
};

void Stack::push(int temp) 
{
    top++;
    s[top] = temp;
}

int Stack::pop() 
{
    int t = s[top];
    top--;
    return t;
}

int Stack::empty() 
{
    return top == -1;
}

class Graph
{
    int n;
    Node *head[20];
    public:
    void create();
    void display();
    Node *search(int v_id);
    int visited[20];
    void DFS();
    void DFS_rec(int v);
    void DFS_non_rec();
    void BFS();
};

void Graph :: create()
{
    char ch;
    Node *curr;

    cout<<"Enter the number of users: ";
    cin>>n;
    for(int i = 0; i < n; i++)
    {
        head[i] = new Node();
        cout << "Enter name for user with ID " << i << ": ";
        cin >> head[i]->name;
        head[i] -> id = i;
        head[i] -> next = NULL;
    }
    for(int i = 0; i < n; i++)
    {
        Node *temp;
        temp = head[i];
        do
        {
            int fid;
            cout << "Enter ID of a friend for user " << head[i]->name << " (ID " << i << "): ";
            cin >> fid;
            if(fid == i)
            {
            cout<<"Self-Loop not allowed!!!!"<<endl;
            }
            else
            {
            curr = new Node();
            curr->id = fid;
            curr->name = head[fid]->name;
            curr -> next = NULL;
            temp -> next = curr;
            temp = curr;
            }
            cout<<"Do you want to add another friend for user "<< head[i] -> name <<"(y/n): ";
            cin>>ch;
        }while(ch == 'y' || ch == 'Y');
    }
}

void Graph :: display()
{
    for(int i = 0; i < n; i++)
    {
        cout << head[i] -> name << "(ID " << i << "): ";
        Node *temp = head[i] -> next;
        while (temp != NULL)
        {
            cout << temp->name << " (ID " << temp->id << ") -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }
}

void Graph :: DFS_rec(int v)
{
    cout << head[v]->name << " ";
    visited[v] = 1;

    for (Node *temp = head[v]->next; temp != NULL; temp = temp->next) 
    {
        if (!visited[temp->id]) 
        {
            DFS_rec(temp->id);
        }
    }
}

void Graph :: DFS()
{
    for (int i = 0; i < n; i++) 
    {
        visited[i] = 0;
    }

    int startId;
    cout << "Enter starting user ID for DFS (recursive): ";
    cin >> startId;

    cout << "DFS (Recursive): ";
    DFS_rec(startId);
    cout << endl;
}

void Graph :: DFS_non_rec() {
    for (int i = 0; i < n; i++) 
    {
        visited[i] = 0;
    }

    int startId;
    cout << "Enter starting user ID for DFS (non-recursive): ";
    cin >> startId;

    Stack s;
    s.push(startId);
    visited[startId]=1;
    cout << "DFS (Non-Recursive): ";

    while (!s.empty()) 
    {
        int v = s.pop();
        if (!visited[v]) 
        {
            cout << head[v]->name << " ";
            visited[v] = 1;
        }

        for (Node *temp = head[v]->next; temp != nullptr; temp = temp->next) 
        {
            if (!visited[temp->id]) 
            {
                s.push(temp->id);
            }
        }
    }
    cout << endl;
}

void Graph :: BFS()
{
    for (int i = 0; i < n; i++) 
    {
        visited[i] = 0;
    }

    int startId;
    cout << "Enter starting user ID for BFS: ";
    cin >> startId;

    Queue q;
    q.insert(startId);
    visited[startId] = 1;

    cout << "BFS: ";
    while (!q.empty()) 
    {
        int v = q.del();
        cout << head[v]->name << " ";

        Node *temp = head[v]->next;
        while (temp != NULL) 
        {
            if (!visited[temp->id]) 
            {
                q.insert(temp->id);
                visited[temp->id] = 1;
            }
            temp = temp->next;
        }
    }
    cout << endl;
}

int main()
{
    Graph g;
    int choice;
   
    do 
    {
        cout << "\nMenu:\n";
        cout << "1. Create a graph using adjacency list (Friend name, ID)\n";
        cout << "2. Display the graph\n";
        cout << "3. Perform recursive DFS traversal (using ID)\n";
        cout << "4. Perform non-recursive DFS traversal (using ID)\n";
        cout << "5. Perform BFS traversal (using ID)\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) 
        {
            case 1:
                g.create();
                break;
            case 2:
                g.display();
                break;
            case 3:
                g.DFS();
                break;
            case 4:
                g.DFS_non_rec();
                break;
            case 5:
                g.BFS();
                break;
            case 6:
                cout << "Exiting the program....." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again!" << endl;
        }
    }while (choice != 6);
    return 0;
}