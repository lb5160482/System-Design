/**
 * Definition of Column:
 * class Column {
 * public:
 *     int key;
 *     String value;
 *     Column(int key, string value) {
 *         this->key = key;
 *         this->value = value;
 *    }
 * }
 */
class MiniCassandra {
private:
    unordered_map<string, map<int, string>> table;
public:
    MiniCassandra() {
        // initialize your data structure here.
    }
    
    /**
     * @param raw_key a string
     * @param column_start an integer
     * @param column_end an integer
     * @return void
     */
    void insert(string raw_key, int column_key, string column_value) {
        table[raw_key][column_key] = column_value;
    }

    /**
     * @param raw_key a string
     * @param column_start an integer
     * @param column_end an integer
     * @return a list of Columns
     */
    vector<Column> query(string raw_key, int column_start, int column_end) {
        vector<Column> res;
        for (auto it : table[raw_key]) {
            if (it.first >= column_start && it.first <= column_end) {
                res.push_back(Column(it.first, it.second));
            }
            if (it.first > column_end) {
                break;
            }
        }

        return res;
    }
};