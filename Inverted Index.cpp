/**
 * Definition of Document:
 * class Document {
 * public:
 *     int id;
 *     string content;
 * }
 */
class Solution {
public:
    /**
     * @param docs a list of documents
     * @return an inverted index
     */
    map<string, vector<int>> invertedIndex(vector<Document>& docs) {
        map<string, vector<int>> res;
        for (auto doc : docs) {
        	string tmp = doc.content;
        	auto pos = tmp.find(' ');
        	while (pos != string::npos) {
        		string word = tmp.substr(0, pos);
        		tmp = tmp.substr(pos + 1);
        		pos = tmp.find(' ');
        		if (word.size() == 0) {
        			continue;
        		}
        		if (!res.count(word)) {
        			res[word].push_back(doc.id);
        		}
        		else {
        			if (res[word].back() != doc.id) {
        				res[word].push_back(doc.id);
        			}
        		}
        	}
        	if (!res.count(tmp)) {
    			res[tmp].push_back(doc.id);
    		}
    		else {
    			if (res[tmp].back() != doc.id) {
    				res[tmp].push_back(doc.id);
    			}
    		}
        }

        return res;
    }
};

// input:
// [
//   {
//     "id": 1,
//     "content": "This is the content of document 1 it is very short"
//   },
//   {
//     "id": 2,
//     "content": "This is the content of document 2 it is very long bilabial bilabial heheh hahaha ..."
//   },
// ]

// output:
// {
//    "This": [1, 2],
//    "is": [1, 2],
//    ...
// }