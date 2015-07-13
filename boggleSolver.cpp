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

class Boggle
{

private:
    vector<string> boggleMatrix;
    Trie trie;
    int m, n;

    void findWordsUtil(vector<vector<bool> >& visited, string& str, int row, int col,
        vector<string>& result)
    {
        if(row < 0 || row >= m || col < 0 || col >= n)
        {
            return;
        }

        if(visited[row][col])
        {
            return;
        }

        visited[row][col] = true;
        str = str + boggleMatrix[row][col];
        if(trie.search(str))
        {
            result.push_back(str);
        }

        for(int i=row-1; i<=row+1; i++)
        {
            for(int j=col-1; j<=col+1; j++)
            {
                findWordsUtil(visited, str, i, j, result);
            }
        }

        visited[row][col] = false;
        str.erase(str.length()-1);
    }

public:
    Boggle(vector<string> matrix, vector<string> dictionary)
    {
        boggleMatrix = matrix;
        m = boggleMatrix.size();
        n = boggleMatrix[0].size();
        for(int i=0; i<dictionary.size(); i++)
        {
            trie.insert(dictionary[i]);
        }
    }

    vector<string> findWords()
    {
        vector<vector<bool> > visited;
        for(int i=0; i<m; i++)
        {
            vector<bool> temp;
            for(int j=0; j<n; j++)
            {
                temp.push_back(false);
            }
            visited.push_back(temp);
        }
        string str = "";
        vector<string> result;
        for(int i=0; i<m; i++)
        {
            for(int j=0; j<n; j++)
            {
                findWordsUtil(visited, str, i, j, result);
            }
        }

        return result;
    }
};

int main(int argc, char const *argv[]) {
    int c;
    vector<string> dictionary;
    cin>>c;
    while(c--)
    {
        string temp;
        cin>>temp;
        dictionary.push_back(temp);
    }
    int m;
    cin>>m;
    vector<string> boggleMatrix;
    while(m--)
    {
        string temp;
        cin>>temp;
        boggleMatrix.push_back(temp);
    }

    Boggle boggle (boggleMatrix, dictionary);

    vector<string> words = boggle.findWords();
    cout<<endl;
    for(int i=0; i<words.size(); i++)
    {
        cout<<words[i]<<endl;
    }
    return 0;
}
