#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class avlNode
{
    string word;
    string meaning;
    avlNode *left;
    avlNode *right;
    public:
    friend class avlTree;
    avlNode()
    {
        left = NULL;
        right = NULL;
    }
    avlNode(string w, string m)
    {
        word = w;
        meaning = m;
        left = NULL;
        right = NULL;
    }
};

class avlTree
{
    avlNode *root;
public:
    avlTree()
    {
        root = NULL;
    }
    int height(avlNode *);
    int diff(avlNode *);
    avlNode *rr_rotation(avlNode *);
    avlNode *ll_rotation(avlNode *);
    avlNode *lr_rotation(avlNode *);
    avlNode *rl_rotation(avlNode *);
    avlNode *balance(avlNode *);
    void insert();
    avlNode *insert(avlNode *, avlNode *);
    void display(avlNode *, int);
    void inorder(avlNode *);
    void preorder(avlNode *);
    void postorder(avlNode *);

    avlNode* getRoot()
    {
        return root;
    }
};

avlNode* avlTree :: ll_rotation(avlNode *parent)
{
    avlNode *temp;
    temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    return temp;
}

avlNode* avlTree :: rr_rotation(avlNode *parent)
{
    avlNode *temp;
    temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    return temp;
}

avlNode* avlTree :: lr_rotation(avlNode *parent)
{
    avlNode *temp;
    temp = parent->left;
    parent->left = rr_rotation(temp);
    return ll_rotation(parent);
}

avlNode* avlTree :: rl_rotation(avlNode *parent)
{
    avlNode *temp;
    temp = parent->right;
    parent->right = ll_rotation(temp);
    return rr_rotation(parent);
}

int avlTree :: height(avlNode *temp)
{
    int h = 0;
    if (temp != NULL)
    {
        int lheight = height(temp->left);
        int rheight = height(temp->right);
        int maxheight = max(lheight, rheight);
        h = maxheight + 1;
    }
    return h;
}

int avlTree :: diff(avlNode *temp)
{
    int lheight = height(temp->left);
    int rheight = height(temp->right);
    int bfactor = lheight - rheight;
    return bfactor;
}

avlNode* avlTree :: balance(avlNode *temp)
{
    int bfactor = diff(temp);
    if (bfactor > 1)
    {
        if (diff(temp->left) > 0)
        {
            temp = ll_rotation(temp);
        }
        else
        {
            temp = lr_rotation(temp);
        }
    }
    else if (bfactor < -1)
    {
        if (diff(temp->right) > 0)
        {
            temp = rl_rotation(temp);
        }
        else
        {
            temp = rr_rotation(temp);
        }
    }
    return temp;
}

void avlTree :: insert()
{
    char ch;
    do
    {
        string word, meaning;
        cout << "Enter word: ";
        cin >> word;
        cout << "Enter Meaning: ";
        cin >> meaning;
        avlNode *temp = new avlNode(word, meaning);
        root = insert(root, temp);
        cout << "Enter your choice: ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
}

avlNode* avlTree :: insert(avlNode *root, avlNode *temp)
{
    if (root == NULL)
    {
        root = temp;
    }
    else if (temp->word < root->word)
    {
        root->left = insert(root->left, temp);
        root = balance(root);
    }
    else if (temp->word >= root->word)
    {
        root->right = insert(root->right, temp);
        root = balance(root);
    }
    return root;
}

void avlTree :: display(avlNode *ptr, int level)
{
    if (ptr != NULL)
    {
        display(ptr->right, level + 1);
        cout << "\n";
        if (ptr == root)
        {
            cout << "Root -> ";
        }
        for (int i = 0; i < level; i++)
        {
            cout << "   ";
        }
        cout << ptr->word << ": " << ptr->meaning << endl;
        display(ptr->left, level + 1);
    }
}

void avlTree :: inorder(avlNode *temp)
{
    if(temp != NULL)
    {
        inorder(temp->left);
        cout<<temp->word<<"\t";
        inorder(temp->right);
    }
}

void avlTree :: preorder(avlNode *temp)
{
    if(temp != NULL)
    {
        cout<<temp->word<<"\t";
        preorder(temp->left);
        preorder(temp->right);
    }
}

void avlTree :: postorder(avlNode *temp)
{
    if(temp != NULL)
    {
        postorder(temp->left);
        postorder(temp->right);
        cout<<temp->word<<"\t";
    }
}

int main()
{
    avlTree t;
    int choice;

    do 
    {
        cout << "\nAVL Tree Dictionary Operations:\n";
        cout << "1. Insert a word\n";
        cout << "2. Display the AVL Tree\n";
        cout << "3. Inorder Traversal\n";
        cout << "4. Preorder Traversal\n";
        cout << "5. Postorder Traversal\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                t.insert();
                break;
            case 2:
                cout << "\nDictionary contents (AVL Tree):\n";
                t.display(t.getRoot(), 0);
                break;
            case 3:
                cout<<"\nInorder Traversal\n";
                t.inorder(t.getRoot());
                break;
            case 4:
                cout<<"\nPreorder Traversal\n";
                t.preorder(t.getRoot());
                break;
            case 5:
                cout<<"\nPostorder Traversal\n";
                t.postorder(t.getRoot());
                break;
            case 6:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Please enter a valid option.\n";
        }
    } while (choice != 6);

    return 0;
}