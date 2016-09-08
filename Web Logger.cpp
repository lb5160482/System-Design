class WebLogger {
private:
    queue<int> q;
public:
    WebLogger() {
        // initialize your data structure here.
    }

    /**
     * @param timestamp an integer
     * @return void
     */
    void hit(int timestamp) {
        q.push(timestamp);
    }

    /**
     * @param timestamp an integer
     * @return an integer
     */
    int get_hit_count_in_last_5_minutes(int timestamp) {
        if (q.empty()) {
            return 0;
        }
        int first = q.front();
        while (timestamp - first >= 300) {
            q.pop();
            if (q.empty()) {
                break;
            }
            first = q.front();
        }

        return q.size();
    }
};