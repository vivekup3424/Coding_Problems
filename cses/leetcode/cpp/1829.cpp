class Node
{
public:
    int data;
    Node *next;
    Node *reverseNode(Node *root)
    {
        if (root == nullptr)
        {
            return root;
        }
        Node *prev = nullptr;
        Node *temp = root;
        while (temp != nullptr)
        {
            Node *data = temp->next;
            temp->next = prev;
            prev = temp;
            temp = data;
        }
    }
    bool isCycle(Node *root, set<int> &visited)
    {
        if (root == nullptr)
        {
            return true;
        }
        if (visited.count(root->data))
        {
            return false;
        }
        visited.insert(root->data);
        else return isCycle(root->next, visited);
    }
    bool cycleDetect(Node *root)
    {
        set<int> visited;
        bool result = isCycle(root, visited);
        return result;
    }
};

// how would I reverse this node
