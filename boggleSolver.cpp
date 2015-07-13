#include<iostream>
#include<vector>
#include<string>

int ALPHABET_SIZE = 26;

using namespace std;

class TrieNode
{
private:
    int value;
    vector<TrieNode*> children;

public:
    TrieNode()
    {
        value = 0;
        for(int i=0; i<ALPHABET_SIZE; i++)
        {
            children.push_back(NULL);
        }
    }

    int getValue()
    {
        return value;
    }

    void setValue(int x)
    {
        value = x;
    }

    vector<TrieNode*> getChildren()
    {
        return children;
    }

    bool isChild(int index)
    {
        return children[index] != NULL;
    }

    void createChild(int index)
    {
        children[index] = new TrieNode();
    }

    TrieNode* getChild(int index)
    {
        return children[index];
    }
};

class Trie
{
private:
    int count;
    TrieNode* root;

    int getIndex(char c)
    {
        c = tolower(c);
        return c-'a';
    }

public:
    Trie()
    {
        root = new TrieNode();
        count = 0;
    }

    void insert(string s)
    {
        count++;
        TrieNode* current = root;
        for(int i=0; i<s.size(); i++)
        {
            int index = getIndex(s[i]);
            if(!current->isChild(index))
            {
                current->createChild(index);
            }

            current = current->getChild(index);
        }

        current->setValue(count);
    }

    int search(string s)
    {
        TrieNode* current = root;
        for(int i=0; i<s.size(); i++)
        {
            int index = getIndex(s[i]);
            if(!current->getChild(index))
            {
                return 0;
            }
            current = current->getChild(index);
        }

        return current->getValue();
    }
};

int main(int argc, char const *argv[]) {
    int n;
    Trie trie;
    cin>>n;
    while(n--)
    {
        string temp;
        cin>>temp;
        trie.insert(temp);
        cout<<trie.search(temp)<<endl;
    }
    return 0;
}
