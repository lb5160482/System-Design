class Node{
public:
    int key;
    int val;
    int expireTime;
    Node(){}
    Node(int k, int v, int e) : key(k), val(v), expireTime(e) {}
};

class Memcache {
private:
    unordered_map<int, vector<Node*>> expireList;// store time when nodes expire
    unordered_map<int, Node*> nodeList;
public:
    Memcache() {}

    int get(int curtTime, int key) {
        int res = 0;
        if (!nodeList.count(key)) {
            res = INT_MAX;
        }
        else {
            res = nodeList[key]->val;
        }

        update(curtTime);
        
        return res;
    }

    void set(int curtTime, int key, int value, int ttl) {
        // update expiration time
        int expTime = 0;
        if (ttl != 0) {
            expTime = curtTime + ttl - 1;
        }
        if (nodeList.count(key)) {
            Node* curt = nodeList[key];
            curt->val = value;
            // remove node's position in expire list
            if (expTime != curt->expireTime) {
                auto pos = find(expireList[curt->expireTime].begin(), expireList[curt->expireTime].end(), curt);
                expireList[curt->expireTime].erase(pos);
                curt->expireTime = expTime;
                expireList[expTime].push_back(curt);
            }
        }
        else {
            Node* tmp = new Node(key, value, expTime);
            nodeList[key] = tmp;
            expireList[expTime].push_back(tmp);
        }

        update(curtTime);
    }

    void del(int curtTime, int key) {
        if (nodeList.count(key)) {
            Node* tmp = nodeList[key];
            auto pos = find(expireList[tmp->expireTime].begin(), expireList[tmp->expireTime].end(), tmp);
            expireList[tmp->expireTime].erase(pos);
            nodeList.erase(key);
            delete tmp;
        }

        update(curtTime);
    }
    
    int incr(int curtTime, int key, int delta) {
        int res = 0;
        if (!nodeList.count(key)) {
            res = INT_MAX;
        }
        else {
            nodeList[key]->val += delta;
            res = nodeList[key]->val;
        }
        update(curtTime);

        return res;
    }
    
    int decr(int curtTime, int key, int delta) {
        int res = 0;
        if (!nodeList.count(key)) {
            res = INT_MAX;
        }
        else {
            nodeList[key]->val -= delta;
            res = nodeList[key]->val;
        }
        update(curtTime);

        return res;        
    }

    // delete nodes which expire at curtTime
    void update(int curtTime) {
        for (auto node : expireList[curtTime]) {
            nodeList.erase(node->key);
            delete node;
        }
        expireList.erase(curtTime);        
    }
};