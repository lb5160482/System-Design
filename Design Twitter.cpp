// push model

// lint version
class MiniTwitter {
private:
    struct Node {
        int time;    
        Tweet tweet;
        Node(int cnt, Tweet x) : time(cnt), tweet(x) {}
    };
    int cnt;
    unordered_map<int, vector<Node*>> timeLines;
    unordered_map<int, vector<Node*>> newsFeeds;
    unordered_map<int, vector<int>> followerLists;
    unordered_set<int> userList;
public:
    MiniTwitter() {
        cnt = 0;
    }

    void createNewUser(int user_id) {
        vector<Node*> tmp1;
        vector<int> tmp2;
        timeLines[user_id] = tmp1;
        newsFeeds[user_id] = tmp1;
        followerLists[user_id] = tmp2;
        userList.insert(user_id);
    }
    
    Tweet postTweet(int user_id, string tweet_text) {
        Tweet tweet = Tweet::create(user_id, tweet_text);
        Node* tmpNode = new Node(cnt, tweet);
        cnt++;
        if (!userList.count(user_id)) {
            createNewUser(user_id);
        }
        timeLines[user_id].push_back(tmpNode);
        newsFeeds[user_id].push_back(tmpNode);
        for (auto friendId : followerLists[user_id]) {
            newsFeeds[friendId].push_back(tmpNode);
        }
    
        return tweet;
    }

    
    vector<Tweet> getNewsFeed(int user_id) {
        vector<Tweet> res;
        if (!userList.count(user_id)) {
            createNewUser(user_id);
            return res;
        }
        for (int i = newsFeeds[user_id].size() - 1, count = 0; i >= 0 && count < 10; --i, ++count) {
            res.push_back(newsFeeds[user_id][i]->tweet);
        }
        
        return res;
    }
        
    
    vector<Tweet>  getTimeline(int user_id) {
        vector<Tweet> res;
        if (!userList.count(user_id)) {
            createNewUser(user_id);
            return res;
        }
        for (int i = timeLines[user_id].size() - 1, count = 0; i >= 0 && count < 10; --i, ++count) {
            res.push_back(timeLines[user_id][i]->tweet);
        }
        
        return res;        
    }

    void follow(int from_user_id, int to_user_id) {
        if (!userList.count(from_user_id)) {
            createNewUser(from_user_id);
        }        
        if (!userList.count(to_user_id)) {
            createNewUser(to_user_id);
        }        
        if (find(followerLists[to_user_id].begin(), followerLists[to_user_id].end(), from_user_id) == followerLists[to_user_id].end()) {
            followerLists[to_user_id].push_back(from_user_id);   
        }
        for (auto node : timeLines[to_user_id]) {
            newsFeeds[from_user_id].push_back(node);
        }
        sort(newsFeeds[from_user_id].begin(), newsFeeds[from_user_id].end(), MiniTwitter::cmp);
    }

    void unfollow(int from_user_id, int to_user_id) {
        if (!userList.count(from_user_id)) {
            createNewUser(from_user_id);
        }        
        if (!userList.count(to_user_id)) {
            createNewUser(to_user_id);
        }   
        auto pos = find(followerLists[to_user_id].begin(), followerLists[to_user_id].end(), from_user_id);
        if (pos != followerLists[from_user_id].end()) {
            followerLists[to_user_id].erase(pos);
        }
        vector<Node*> tmp;
        for (auto it : newsFeeds[from_user_id]) {
            if (it->tweet.user_id != to_user_id) {
                tmp.push_back(it);
            }
        }
        newsFeeds[from_user_id] = tmp;
    }
    
    static bool cmp(Node* node1, Node* node2) {
        return node1->time < node2->time;
    }
};

// leet version
class Twitter {
private:
    struct Node {
        int time;
        int tweet_id;
        int user_id;
        Node(int x, int y, int z) : time(x), tweet_id(y), user_id(z) {}
    };
    int cnt;
    unordered_map<int, vector<Node*>> newsFeeds;
    unordered_map<int, vector<Node*>> timeLines;
    unordered_map<int, vector<int>> followByLists;
    unordered_set<int> userList;
public:
    /** Initialize your data structure here. */
    Twitter() {
        cnt = 0;
    }
    
    void createUser(int userId) {
        vector<Node*> tmp1;
        vector<int> tmp2;
        newsFeeds[userId] = tmp1;
        timeLines[userId] = tmp1;
        followByLists[userId] = tmp2;
        userList.insert(userId);
    }

    /** Compose a new tweet. */
    void postTweet(int userId, int tweetId) {
        Node* node = new Node(cnt, tweetId, userId);
        cnt++;
        if (!userList.count(userId)) {
            createUser(userId);
        }
        newsFeeds[userId].push_back(node);
        timeLines[userId].push_back(node);
        for (auto friendId : followByLists[userId]) {
            newsFeeds[friendId].push_back(node);
        }
    }
    
    /** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */
    vector<int> getNewsFeed(int userId) {
        vector<int> res;
        if (!userList.count(userId)) {
            createUser(userId);
            return res;
        }
        for (int i = newsFeeds[userId].size() - 1, count = 0; i >= 0 && count < 10; --i, ++count) {
            res.push_back(newsFeeds[userId][i]->tweet_id);
        }

        return res;
    }
    
    /** Follower follows a followee. If the operation is invalid, it should be a no-op. */
    void follow(int followerId, int followeeId) {
        if (!userList.count(followerId)) {
            createUser(followerId);
        }
        if (!userList.count(followeeId)) {
            createUser(followeeId);
        }
        if (followerId == followeeId) {
            return;
        }
        auto pos = find(followByLists[followeeId].begin(), followByLists[followeeId].end(), followerId);
        if (pos != followByLists[followeeId].end()) {
            return;
        }
        followByLists[followeeId].push_back(followerId);
        for (auto node : timeLines[followeeId]) {
            newsFeeds[followerId].push_back(node);
        }
        sort(newsFeeds[followerId].begin(), newsFeeds[followerId].end(), cmp);
    }
    
    /** Follower unfollows a followee. If the operation is invalid, it should be a no-op. */
    void unfollow(int followerId, int followeeId) {
        if (!userList.count(followerId)) {
            createUser(followerId);
        }
        if (!userList.count(followeeId)) {
            createUser(followeeId);
        }        
        if (followerId == followeeId) {
            return;
        }        
        auto pos = find(followByLists[followeeId].begin(), followByLists[followeeId].end(), followerId);
        if (pos == followByLists[followeeId].end()) {
            return;
        }
        followByLists[followeeId].erase(pos);
        vector<Node*> tmp;
        for (auto node : newsFeeds[followerId]) {
            if (node->user_id != followeeId) {
                tmp.push_back(node);
            }
        }
        newsFeeds[followerId] = tmp;
    }

    static bool cmp(Node* node1, Node* node2) {
        return node1->time < node2->time;
    }
};


// pull model
class Twitter {
private:
    struct Node {
        int time;
        int tweet_id;
        int user_id;
        Node(int x, int y, int z) : time(x), tweet_id(y), user_id(z) {}
    };
    int cnt;
    unordered_map<int, vector<Node*>> timeLines;
    unordered_map<int, vector<int>> followLists;
    unordered_set<int> userList;
public:
    /** Initialize your data structure here. */
    Twitter() {
        cnt = 0;
    }
    
    void createUser(int userId) {
        vector<Node*> tmp1;
        vector<int> tmp2;
        timeLines[userId] = tmp1;
        followLists[userId] = tmp2;
        userList.insert(userId);
    }

    /** Compose a new tweet. */
    void postTweet(int userId, int tweetId) {
        Node* node = new Node(cnt, tweetId, userId);
        cnt++;
        if (!userList.count(userId)) {
            createUser(userId);
        }
        timeLines[userId].push_back(node);
    }
    
    /** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */
    vector<int> getNewsFeed(int userId) {
        vector<int> res;
        vector<Node*> tmp;
        if (!userList.count(userId)) {
            createUser(userId);
            return res;
        }
        for (auto followee : followLists[userId]) {
            for (int i = timeLines[followee].size() - 1, cnt = 0; i >= 0 && cnt < 10; --i, ++cnt) {
                tmp.push_back(timeLines[followee][i]);
            }
        }
        for (int i = timeLines[userId].size() - 1, cnt = 0; i >= 0 && cnt < 10; --i, ++cnt) {
            tmp.push_back(timeLines[userId][i]);
        }
        sort(tmp.begin(), tmp.end(), Twitter::cmp);
        for (int i = 0; i < 10 && i < tmp.size(); ++i) {
            res.push_back(tmp[i]->tweet_id);
        }
        return res;
    }
    
    /** Follower follows a followee. If the operation is invalid, it should be a no-op. */
    void follow(int followerId, int followeeId) {
        if (!userList.count(followerId)) {
            createUser(followerId);
        }
        if (!userList.count(followeeId)) {
            createUser(followeeId);
        }
        if (followerId == followeeId) {
            return;
        }
        auto pos = find(followLists[followerId].begin(), followLists[followerId].end(), followeeId);
        if (pos != followLists[followerId].end()) {
            return;
        }
        followLists[followerId].push_back(followeeId);
    }
    
    /** Follower unfollows a followee. If the operation is invalid, it should be a no-op. */
    void unfollow(int followerId, int followeeId) {
        if (!userList.count(followerId)) {
            createUser(followerId);
        }
        if (!userList.count(followeeId)) {
            createUser(followeeId);
        }        
        if (followerId == followeeId) {
            return;
        }        
        auto pos = find(followLists[followerId].begin(), followLists[followerId].end(), followeeId);
        if (pos == followLists[followerId].end()) {
            return;
        }
        followLists[followerId].erase(pos);
    }

    static bool cmp(Node* node1, Node* node2) {
        return node1->time > node2->time;
    }
};