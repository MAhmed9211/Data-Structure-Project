#include <iostream>
#include<fstream>
#include<string>
using namespace std;

class TrieNode
{
public:
    char a = 'a';
    bool end;
    TrieNode* children[26];

    TrieNode()
    {
        a = ' ';
        for (int i = 0; i < 26; i++)
        {
            children[i] = NULL;
        }
        end = false;
    }
    // end is true if the node represents
    // end of a word
};

class Tries
{
    TrieNode* root = new TrieNode;
public:
    void insert(string key)
    {
        TrieNode* temp = root;
        for (int i = 0; i < key.length(); i++)
        {
            int index = key[i] - 'a';
            if (temp->children[index] == NULL)
            {
                TrieNode* n = new TrieNode;
                n->a = key[i];
                temp->children[index] = new TrieNode;
            }
            temp = temp->children[index];
        }
        temp->end = true;
    }
    bool cheak(string key)
    {
        bool flag;
        int index;
        TrieNode* temp = root;

        for (int i = 0; i < key.length(); i++)
        {
            index = key[i] - 'a';
            if (!temp->children[index])
            {
                cout << "Invalid input.\n";
                return false;
            }
            temp = temp->children[index];
        }
        flag = temp->end;
        return flag;
    }
    TrieNode* sugg_node(string key)
    {
        TrieNode* temp = root;

        for (int i = 0; i < key.length(); i++)
        {
            int index = key[i] - 'a';
            temp = temp->children[index];
        }
        return temp;
    }
    bool cheak_exeption(string line)
    {
        int s = line.size();
        bool flag = false;
        for (int i = 0; i < s; i++)
        {
            if (line[i] < 'a' || line[i]>'z')
            {
                flag = true;
            }
        }
        return flag;
    }
    void load()
    {
        bool get = false;
        string line;
        char a = 'a';
        ifstream myfile("outfile.txt", ios::in);
        if (myfile.is_open())
        {
            while (!myfile.eof())
            {
                getline(myfile, line);
                get = cheak_exeption(line);
                if (get == false)
                {
                    insert(line);
                }
                get = false;
            }
            myfile.close();
        }
        else
        {
            cout << "Plz see, I am getting some problem from the file.\n";
        }
    }
    void display(struct TrieNode* head, char str[], int index, int go, int& count)
    {
        if (head == NULL)
        {
            return;
        }
        else if (count >= go)
        {
            return;
        }
        if (head->end)
        {
            str[index] = '\0';
            count++;
            cout << "(" << count << ")" << str << endl;
        }
        for (int i = 0; i < 26; i++)
        {
            if (head->children[i])
            {
                str[index] = i + 'a';
                index++;
                display(head->children[i], str, index, go, count);
            }
        }
    }
    void suggestion(string abc, int num)
    {
        int count = 0;

        char ss[500];
        int string_length = abc.length();
        for (int i = 0; i < string_length; i++)
        {
            ss[i] = abc[i];
        }
        bool flag = cheak(abc);
        if (flag)
        {
            TrieNode* holder = sugg_node(abc);
            display(holder, ss, string_length, num, count);
            if (count < num)
            {
                cout << "Sorry i can just gave you the above suggestions.\n";
            }
        }
        else
        {
            cout << "You entered wrong input.\n";
        }
    }
};


// Driver
int main()
{
    Tries obj;
    int num;
    string name;
    char choice;

    obj.load();

    while (true)
    {
        system("cls");
        cout << "(1) Get Suggestion.\n";
        cout << "(2) Exit.\n";
        cin >> choice;
        if (choice == '1')
        {
            cout << "Enter the String to get suggestion.\n";
            cin >> name;
            cout << "How amny Suggestion do you want.\n";
            cin >> num;
            if (num < -1)
            {
                cout << "Invalid Input.\n";
            }
            else
            {
                obj.suggestion(name, num);
            }
        }
        else if (choice == '2')
        {
            cout << "You have successfully terminated the program.\n";
            break;
        }
        else if (choice < '1' || choice>'2')
        {
            cout << "Invalid Input.\n";
        }
        system("pause");
    }
    return 0;
}
