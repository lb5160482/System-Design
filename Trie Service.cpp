// Given a list of

// <"abc", 2>
// <"ac", 4>
// <"ab", 9>

// Return <a[9,4,2]<b[9,2]<c[2]<>>c[4]<>>>, and denote the following tree structure:

//          Root
//          / 
//        a(9,4,2)
//       /    \
//     b(9,2) c(4)
//    /
//  c(2)
/**
 * Definition of TrieNode:
 * class TrieNode {
 * public:
 *     TrieNode() {}
 *     map<char, TrieNode*> children;
 *     vector<int> top10;
 * };
 */
class TrieService {
private:
    TrieNode* root;

public:
    TrieService() {
        root = new TrieNode();
    }

    TrieNode* getRoot() {
        // Return root of trie root, and 
        // lintcode will print the tree struct.
        return root;
    }

    void insert(string& word, int frequency) {
        TrieNode* p = root;
        for (int i = 0; i < word.size(); ++i) {
            if (p->children.count(word[i])) {
                p = p->children[word[i]];
            }
            else {
                TrieNode* newNode = new TrieNode();
                p->children[word[i]] = newNode;
                p = newNode;
            }
            if (p->top10.size() < 10) {
                p->top10.push_back(frequency);
            }
            else {
                if (frequency > p->top10.back()) {
                    p->top10.pop_back();
                    p->top10.push_back(frequency);
                }
            }
            sort(p->top10.begin(), p->top10.end(), TrieService::cmp);
        }
    }

    static bool cmp(int a, int b) {
        return a > b;
    }
};

