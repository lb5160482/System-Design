// As a follow up for Tiny URL, we are going to support custom tiny url, so that user can create their own tiny url.
// Notice
// Custom url may have more than 6 characters in path.
// Example:
// createCustom("http://www.lintcode.com/p1", "000001")
// createCustom("http://www.lintcode.com/p2", "000002")
// createCustom("http://www.lintcode.com/p3", "000003")
// createCustom("http://www.lintcode.com/p4", "000004")
// longToShort("http://www.lintcode.com/problem/")
// shortToLong("http://tiny.url/000002")
// shortToLong("http://tiny.url/000004")
// createCustom("http://www.facebook.com", "facebook")
// createCustom("http://www.facebook.com", "facebook")
// createCustom("http://www.google.com", "google")
// createCustom("http://www.lintcode.com", "lc")
// shortToLong("http://tiny.url/lc")
// shortToLong("http://tiny.url/google")
// createCustom("http://www.google.com", "google")
// shortToLong("http://tiny.url/facebook")
// longToShort("http://www.lintcode.com")
// longToShort("http://www.google.com")
// longToShort("http://www.facebook.com")
class TinyUrl2 {
private:
    map<int, string> id2url;//url table: id -> long url
    map<string, int> url2id; // url table: long irl -> id
    map<string, string> custom_c2url; // custom table: custom url -> long url
    map<string, string> custom_url2c; // custom table: long url -> custom
    // short url to id calculation
    int urlToId(string shortUrl) {
        int id = 0;
        string chars = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        for (int i = 0; i < shortUrl.size(); ++i) {
            int num = 0;
            char c = shortUrl[i];
            if (isdigit(c)) {
                num = c - '0';
            }
            else if (c >= 'a' && c <= 'z') {
                num = 10 + c - 'a';
            }
            else if (c >= 'A' && c <= 'Z') {
                num = 36 + c - 'A';
            }
            else {
                return -1;
            }
            id = 62 * id + num;
        }

        return id;
    }
    // id to short url calculation
    string idToUrl(int id) {
        string shortUrl = "";
        string chars = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        while (id > 0) {
            shortUrl = chars[id % 62] + shortUrl;
            id /= 62;
        }
        while (shortUrl.size() < 6) {
            shortUrl = '0' + shortUrl;
        }
        return shortUrl;        
    }

public:
    /**
     * @param long_url a long url
     * @param a short key
     * @return a short url starts with http://tiny.url/
     */
    string createCustom(string& long_url, string& short_key) {
        // if size == 6, check if regular url table has this one first
        if (short_key.size() == 6) {
            int id = urlToId(short_key);
            // id > 6 means it's a valid regular short url
            if (id > 0) {
                if (id2url.count(id) || url2id.count(long_url)) {
                    return "error";
                }
            }
        }
        // if custom table has this one, but with the same short_key and long_url, return the one
        if (custom_c2url.count(short_key) && custom_url2c.count(long_url)) {
            return "http://tiny.url/" + short_key;
        }        
        // check if custom table has the one, if it does but does not have same information, return false
        if (custom_c2url.count(short_key) || custom_url2c.count(long_url)) {
            return "error";
        }
        // add to custom table
        custom_c2url[short_key] = long_url;
        custom_url2c[long_url] = short_key;
        return "http://tiny.url/" + short_key;
    }

    /**
     * @param long_url a long url
     * @return a short url starts with http://tiny.url/
     */
    string longToShort(string& long_url) {
        // check if custom table has this long url, then check regular table, if both not, add to regular table
        if (custom_url2c.count(long_url)) {
            return "http://tiny.url/" + custom_url2c[long_url];
        }
        else if (url2id.count(long_url)) {
            int id = url2id[long_url];
            return "http://tiny.url/" + idToUrl(id);
        }
        else {
            // use long long to avoid overflow, since the url may be really long
            long long tmpId = 0;
            for (int i = 0; i < long_url.size(); ++i) {
                tmpId = (256 * tmpId + long_url[i]) % INT_MAX;
            }
            // if taken, check next(plus one)
            while (id2url.count(tmpId)) {
                tmpId++;
                tmpId %= INT_MAX;
            }
            int id = tmpId;
            // add to regular table
            id2url[id] = long_url;
            url2id[long_url] = id;
            return "http://tiny.url/" + idToUrl(id);
        }
    }

    /**
     * @param short_url a short url starts with http://tiny.url/
     * @return a long url
     */
    string shortToLong(string& short_url) {
        // get short url key and id
        string short_key = short_url.substr(16);
        int id = urlToId(short_key);
        // check custom using short_key; regular by id; or return false
        if (custom_c2url.count(short_key)) {
            return custom_c2url[short_key];
        }
        if (id2url.count(id)) {
            return id2url[id];
        }
        else {
            return "error";
        }
    }
};