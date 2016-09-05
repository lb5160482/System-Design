class Typeahead {
private:
	unordered_map<string, vector<string>> table;
public:
    // @param dict: A dictionary of words dict
    Typeahead(unordered_set<string> &dict) {
        for (auto item : dict) {
        	for (int i = 0; i < item.size(); ++i) {
        		for (int j = 1; i + j - 1 < item.size(); ++j) {
        			string subStr = item.substr(i, j);
        			if (table.count(subStr)) {
        				auto pos = find(table[subStr].begin(), table[subStr].end(), item);
        				if (pos == table[subStr].end()) {
        					table[subStr].push_back(item);
        				}
        			}
        			else {
        				table[subStr].push_back(item);
        			}
        		}
        	}
        }
    }
    
    // @param str: a string
    // @return a set of words
    vector<string> search(string &str) {
        if (table.count(str)) {
        	return table[str];
        }
        else {
        	return vector<string>();
        }
    }
};