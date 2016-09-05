/**
 * Definition of TrieNode:
 * class TrieNode {
 * public:
 *     TrieNode() {}
 *     map<char, TrieNode*> children;
 * };
 */
class Solution {
public:
    /**
     * This method will be invoked first, you should design your own algorithm 
     * to serialize a trie which denote by a root node to a string which
     * can be easily deserialized by your own "deserialize" method later.
     */
    string serialize(TrieNode* root) {
        TrieNode* p = root;
        queue<TrieNode*> q;
        q.push(root);
        string res = "";
        while (!q.empty()) {
            p = q.front();
            q.pop();
            for (auto it : p->children) {
                res = res + it.first + ' ';
                q.push(it.second);
            }
            res += '#';
        }

        return res;
    }

    /**
     * This method will be invoked second, the argument data is what exactly
     * you serialized at method "serialize", that means the data is not given by
     * system, it's given by your own serialize method. So the format of data is
     * designed by yourself, and deserialize it here as you serialize it in 
     * "serialize" method.
     */
    TrieNode* deserialize(string data) {
        TrieNode* root = new TrieNode();
        TrieNode* p = root;
        size_t pos = data.find('#');
        queue<TrieNode*> q;
        q.push(p);
        while (pos != string::npos) {
            string children = data.substr(0, pos);
            data = data.substr(pos + 1);
            p = q.front();
            q.pop();
            size_t childPos = children.find(' ');
            while (childPos != string::npos) {
                char node = children.substr(0, childPos)[0];
                children = children.substr(childPos + 1);
                p->children[node] = new TrieNode();
                q.push(p->children[node]);
                childPos = children.find(' ');
            }
            pos = data.find('#');
        }

        return root;
    }
};