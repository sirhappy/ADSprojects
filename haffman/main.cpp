
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <bitset>

using namespace std;


class Huffman {

    class Node {
        friend Huffman;

    public:
        Node(int frequency)
        {
            this->frequency = frequency;
            left = nullptr;
            right = nullptr;
        }

        void addCode(int num, int length)
        {
            if (!left && !right)
            {
                code |= num;
                this->length = length;
            }
        }

        string codeToString()
        {
            string str = code.to_string();
            return str.substr(str.length() - length, length);
        }

        ~Node()
        {
            if (left)
                delete left;
            if (right)
                delete right;
        }

    private:
        int frequency;
        int length;
        bitset<8 * sizeof(long long)> code;
        Node* left;
        Node* right;
    };

public:
    void build()
    {
        while (nodes.size() > 1)
        {
            Node* mergedNode = new Node((nodes[nodes.size() - 1]->frequency +
                                         nodes[nodes.size() - 2]->frequency));
            mergedNode->left = nodes[nodes.size() - 2];
            mergedNode->right = nodes[nodes.size() - 1];

            nodes.pop_back();

            int i = nodes.size() - 2;
            while (i >= 0 && mergedNode->frequency > nodes[i]->frequency)
            {
                nodes[i + 1] = nodes[i];
                --i;
            }
            nodes[i + 1] = mergedNode;
        }

        root = nodes[0];
        makeCode(root, 0, 0);
    }

    void addChance(int chance)
    {
        nodes.push_back(new Node(chance));
        origin.push_back(nodes[nodes.size() - 1]);
    }

    string get(int i)
    {
        return origin[i]->codeToString();
    }

    ~Huffman()
    {
        if (root)
            delete root;
    }

private:
    void makeCode(const Node* node, int num, int length)
    {
        ++length;
        if (node->left)
        {
            node->left->addCode((num << 1) + 1, length);
            makeCode(node->left, (num << 1) + 1, length);
        }
        if (node->right)
        {
            node->right->addCode(num << 1, length);
            makeCode(node->right, num << 1, length);
        }
    }

private:
    vector<Node*> nodes;
    vector<Node*> origin;
    Node* root;
};

int main()
{
    int n;
    Huffman* huff = new Huffman();
    fstream fin;
    fin.open("input.txt", ios::in);
    if (fin.is_open())
    {
        fin >> n;
        for (int i = 0; i < n; i++)
        {
            int x;
            fin >> x;
            huff->addChance(x);
        }

        fin.close();

        huff->build();
        fstream fout;
        fout.open("output.txt", ios::out);
        for (int i = 0; i < n; i++)
        {
            fout << huff->get(i) << (i == n - 1 ? "" : " ");
        }
        fout.close();
        delete huff;
    }

    return 0;

}

