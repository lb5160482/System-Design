class TrieNode {
public:
    char c;
    int cnt;
    vector<TrieNode*> nextNodes;
    TrieNode(char x) : c(x), cnt(0) {}
    TrieNode() : c('#'), cnt(0) {}
};

class Trie {
public:
    Trie() {
        root = new TrieNode();
    }

    // Inserts a word into the trie.
    void insert(string word) {
        TrieNode* node = root;
        for (int i = 0; i < word.size(); ++i) {
            bool hasChar = false;
            for (auto nextNode : node->nextNodes) {
                if (nextNode->c == word[i]) {
                    node = nextNode;
                    hasChar = true;
                    break;
                }
            }
            if (!hasChar) {
                TrieNode* nextNode = new TrieNode(word[i]);
                node->nextNodes.push_back(nextNode);
                node = nextNode;
            }
        }
        node->cnt++;
    }

    // Returns if the word is in the trie.
    bool search(string word) {
        TrieNode* node = root;
        for (int i = 0; i < word.size(); ++i) {
            bool hasChar = false;
            for (auto nextNode : node->nextNodes) {
                if (nextNode->c == word[i]) {
                    node = nextNode;
                    hasChar = true;
                    break;
                }
            }
            if (!hasChar) {
                return false;
            }
        }
        
        return node->cnt > 0 ? true : false;        
    }

    // Returns if there is any word in the trie
    // that starts with the given prefix.
    bool startsWith(string prefix) {
        TrieNode* node = root;
        for (int i = 0; i < prefix.size(); ++i) {
            bool hasChar = false;
            for (auto nextNode : node->nextNodes) {
                if (nextNode->c == prefix[i]) {
                    node = nextNode;
                    hasChar = true;
                    break;
                }
            }
            if (!hasChar) {
                return false;
            }
        }
        
        return true;               
    }

private:
    TrieNode* root;
};