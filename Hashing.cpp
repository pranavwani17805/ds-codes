#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class record 
{
    int rollno, marks;
    char name[20];
    friend class student;
};

class hashing 
{
    int rollno, pos;
    public:
    hashing() 
    {
        rollno = -1;
        pos = -1;
    }
    friend class student;
};

class student 
{
    record rec;
    hashing h[10];
    int s, count;

    public:
    student();
    void create_wor();
    void create_wr();
    void modify();
    void retrieve();
    void delete_rec();
    void display();
    void rebuild_hash_table();
};

student::student() 
{
    s = sizeof(record);
    count = 0;
    for (int i = 0; i < 10; i++) 
    {
        h[i].rollno = -1;
        h[i].pos = -1;
    }
    rebuild_hash_table();
}

void student::rebuild_hash_table() 
{
    ifstream f("student.txt", ios::binary);
    if (!f) return;
    int pos = 0;
    while (f.read((char*)&rec, sizeof(record))) 
    {
        int loc = rec.rollno % 10;
        while (h[loc].rollno != -1)
            loc = (loc + 1) % 10;
        h[loc].rollno = rec.rollno;
        h[loc].pos = pos;
        pos++;
    }
    count = pos;
    f.close();
}

void student::create_wr() 
{
    char ans;
    fstream f("student.txt", ios::binary | ios::in | ios::out | ios::app);
    do 
    {
        cout << "Enter the details:\n";
        cout << "Roll no: "; cin >> rec.rollno;
        cout << "Name: "; cin >> rec.name;
        cout << "Marks: "; cin >> rec.marks;

        int loc = rec.rollno % 10;
        if (h[loc].rollno == -1) 
        {
            h[loc].rollno = rec.rollno;
            h[loc].pos = count;
        } 
        else 
        {
            int i = 1;
            while (h[(loc + i) % 10].rollno != -1 && i < 10)
                i++;
            if (i == 10) 
            {
                cout << "Hash table full. Cannot insert.\n";
                return;
            }
            loc = (loc + i) % 10;
            h[loc].rollno = rec.rollno;
            h[loc].pos = count;
        }

        f.write((char*)&rec, s);
        count++;
        cout << "Do you want to add next student record? (y/n): ";
        cin >> ans;
    } while (ans == 'y' || ans == 'Y');
    f.close();
}

void student::create_wor() 
{
    char ans;
    fstream f("student.txt", ios::binary | ios::in | ios::out | ios::app);
    do 
    {
        cout << "Enter the details:\n";
        cout << "Roll no: "; cin >> rec.rollno;
        cout << "Name: "; cin >> rec.name;
        cout << "Marks: "; cin >> rec.marks;

        int loc = rec.rollno % 10;
        int i = 0;
        while (h[(loc + i) % 10].rollno != -1 && i < 10)
            i++;

        if (i == 10) 
        {
            cout << "Hash table full. Cannot insert.\n";
            return;
        }

        loc = (loc + i) % 10;
        h[loc].rollno = rec.rollno;
        h[loc].pos = count;

        f.write((char*)&rec, s);
        count++;

        cout << "Do you want to add next student record? (y/n): ";
        cin >> ans;
    } while (ans == 'y' || ans == 'Y');
    f.close();
}

void student::delete_rec() 
{
    char ans;
    do 
    {
        int roll;
        cout << "Enter the roll no to be deleted: ";
        cin >> roll;

        fstream f("student.txt", ios::binary | ios::in);
        fstream t("temp.txt", ios::binary | ios::out);
        int pos = 0;
        count = 0;

        for (int i = 0; i < 10; i++) 
        {
            h[i].rollno = -1;
            h[i].pos = -1;
        }

        while (f.read((char*)&rec, sizeof(record))) 
        {
            if (rec.rollno != roll) 
            {
                t.write((char*)&rec, sizeof(record));
                int loc = rec.rollno % 10;
                while (h[loc].rollno != -1)
                    loc = (loc + 1) % 10;
                h[loc].rollno = rec.rollno;
                h[loc].pos = pos++;
            }
        }

        count = pos;
        f.close();
        t.close();
        remove("student.txt");
        rename("temp.txt", "student.txt");

        cout << "Do you want to delete another record? (y/n): ";
        cin >> ans;
    } while (ans == 'y' || ans == 'Y');
}

void student::modify() 
{
    int roll;
    cout << "Enter roll number to modify: ";
    cin >> roll;

    fstream f("student.txt", ios::binary | ios::in | ios::out);
    bool found = false;

    for (int i = 0; i < 10; i++) 
    {
        if (h[i].rollno == roll) 
        {
            f.seekg(h[i].pos * sizeof(record), ios::beg);
            f.read((char*)&rec, sizeof(record));

            cout << "Current Record:\n";
            cout << "Roll No: " << rec.rollno << "\nName: " << rec.name << "\nMarks: " << rec.marks << endl;

            cout << "Enter new name: ";
            cin >> rec.name;
            cout << "Enter new marks: ";
            cin >> rec.marks;

            f.seekp(h[i].pos * sizeof(record), ios::beg);
            f.write((char*)&rec, sizeof(record));
            found = true;
            break;
        }
    }
    if (!found) cout << "Record not found.\n";
    f.close();
}

void student::display() 
{
    cout << "\n--- Hash Table ---\n";
    cout << "Key\tRoll No\tName\tMarks\n";
    for (int i = 0; i < 10; i++) 
    {
        if (h[i].rollno != -1) 
        {
            fstream f("student.txt", ios::binary | ios::in);
            f.seekg(h[i].pos * sizeof(record), ios::beg);
            f.read((char*)&rec, sizeof(record));
            cout << i << "\t" << rec.rollno << "\t" << rec.name << "\t" << rec.marks << endl;
            f.close();
        } 
        else 
        {
            cout << i << "\t--\t--\t--\n";
        }
    }
}

void student::retrieve() 
{
    int roll;
    cout << "Enter roll number to search: ";
    cin >> roll;

    fstream f("student.txt", ios::binary | ios::in);
    bool found = false;

    for (int i = 0; i < 10; i++) 
    {
        if (h[i].rollno == roll) 
        {
            f.seekg(h[i].pos * sizeof(record), ios::beg);
            f.read((char*)&rec, sizeof(record));
            cout << "Record Found:\n";
            cout << "Roll No: " << rec.rollno << "\nName: " << rec.name << "\nMarks: " << rec.marks << endl;
            found = true;
            break;
        }
    }
    if (!found) cout << "Record not found.\n";
    f.close();
}

int main() 
{
    student s;
    int choice;
    do 
    {
        cout << "\n--- Student Record System ---\n";
        cout << "1. Create with Replacement\n";
        cout << "2. Create without Replacement\n";
        cout << "3. Delete a Record\n";
        cout << "4. Modify a Record\n";
        cout << "5. Insert a Record without replacement\n";
        cout << "6. Insert a Record with replacement\n";
        cout << "7. Display Records\n";
        cout << "8. Search a Record\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) 
        {
            case 1: 
                s.create_wr(); 
                break;
            case 2: 
                s.create_wor(); 
                break;
            case 3: 
                s.delete_rec(); 
                break;
            case 4: 
                s.modify(); 
                break;
            case 5: 
                s.create_wor(); 
                break;
            case 6: 
                s.create_wr(); 
                break;
            case 7:
                s.display(); 
                break;
            case 8:
                s.retrieve();
                break;
            case 9: 
                cout << "Exiting...\n"; 
                break;
            default: 
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 9);

    return 0;
}