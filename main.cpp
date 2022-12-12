#include<cstddef>
#include<iostream>
#include<list>
#include<memory>

using std::shared_ptr;
using std::weak_ptr;
using std::make_shared;

struct Node
{
    Node(int val) : val(val) {}
    Node(int val, const shared_ptr<Node>& prev) : val(val), prev(prev) {}
    weak_ptr<Node> prev;
    int val;
    std::list<shared_ptr<Node>> next;

    shared_ptr<Node> create_node(int val, const shared_ptr<Node>& father) // to do
    {
        this->next.emplace_back(make_shared<Node>(val, father));
        return this->next.back();
    }

    ~Node() { std::cout << "val: " << val << " freed\n"; }
};

int main()
{
    shared_ptr<Node> head = make_shared<Node>(10);
    shared_ptr<Node> branch1 = head->create_node(20, head);
    shared_ptr<Node> branch2 = head->create_node(21, head);
    shared_ptr<Node> leafe1 = branch1->create_node(30, branch1);
    shared_ptr<Node> leafe2 = branch2->create_node(31, branch2);
    shared_ptr<Node> leafe3 = branch1->create_node(32, branch1);
    shared_ptr<Node> leafe4 = branch2->create_node(33, branch2);

    std::cout << head->val << '\n';
    std::cout << branch1->val << '\n';
    std::cout << branch2->val << '\n';
    std::cout << leafe1->val << '\n';
    std::cout << leafe2->val << '\n';
    std::cout << leafe3->val << '\n';
    std::cout << leafe4->val << '\n';

    // expected: 10, 20, 21, 30, 31, 32, 33
    // free in same order ONE DEALLOCATION PER

    return 0;
}
