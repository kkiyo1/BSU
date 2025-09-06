#include <iostream>
#include <fstream>
#include <string>

struct Node {
    long long num;
    Node* left;
    Node* right;
    Node(long long n, Node* l, Node* r) : num(n), left(l), right(r) {};
    ~Node() {
        delete right;
        delete left;
    }
};

class BinaryTree {
private:
    Node* root;
public:
    long long summ = 0;
    BinaryTree() : root(nullptr){}
    ~BinaryTree() { delete root; }
    void push(long long x) {
        if (nullptr == root) {
            root = new Node(x, nullptr, nullptr);
            summ += x;
            return;
        }
        Node* curr = root;
        while (true) {
            if (x < curr->num) {
                if (nullptr != curr->left) curr = curr->left;
                else {
                    curr->left = new Node(x, nullptr, nullptr);
                    summ += x;
                    break;
                }
            }
            else if (x > curr->num) {
                if (nullptr != curr->right) curr = curr->right;
                else {
                    curr->right = new Node(x, nullptr, nullptr);
                    summ += x;
                    break;
                };
            }
            else break;
        }
    }
};

int main() {
    BinaryTree tree;
    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("output.txt");
    if (!inputFile.is_open()) {
        outputFile << 0;
        return 0;
    }
    std::string line;
    while (std::getline(inputFile, line)) {
        if (line.empty()) continue;
        tree.push(std::stoll(line));
    }
    outputFile << tree.summ;
    return 0;
}