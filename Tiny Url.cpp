// Given a long url, make it shorter. To make it simpler, let's ignore the domain name.

// You should implement two methods:

//     longToShort(url). Convert a long url to a short url.
//     shortToLong(url). Convert a short url to a long url starts with http://tiny.url/.

// You can design any shorten algorithm, the judge only cares about two things:

//     The short key's length should equal to 6 (without domain and slash). And the acceptable characters are [a-zA-Z0-9]. For example: abcD9E
//     No two long urls mapping to the same short url and no two short urls mapping to the same long url.


class TinyUrl {
private:
    vector<string> table;
public:
    /**
     * @param url a long url
     * @return a short url starts with http://tiny.url/
     */
    string longToShort(string& url) {
        table.push_back(url);
        int id = table.size() - 1;
        string shortUrl = "";
        string chars = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        while (id > 0) {
            shortUrl = chars[id % 62] + shortUrl;
            id /= 62;
        }
        while (shortUrl.size() < 6) {
            shortUrl = '0' + shortUrl;
        }
        shortUrl = "http://tiny.url/" + shortUrl;
        return shortUrl;
    }

    /**
     * @param url a short url starts with http://tiny.url/
     * @return a long url
     */
    string shortToLong(string& url) {
        string shortUrl = url.substr(16);
        int id = 0;
        for (int i = 0; i < shortUrl.size(); ++i) {
            char c = shortUrl[i];
            int num = 0;
            if (isdigit(c)) {
                num = c - '0';
            }
            else if (c >= 'a' && c <= 'z') {
                num = c - 'a' + 10;
            }
            else {
                num = c - 'A' + 36;
            }
            id = 62 * id + num;
        }
        return table[id];
    }
};