class Solution {
public:
    /**
     * @param n a positive integer
     * @return n x 3 matrix
     */
    vector<vector<int>> consistentHashing(int n) {
        vector<vector<int>> res;
        int cnt = 1;
        vector<int> init = {0, 359, 1};
        res.push_back(init);
        while (cnt < n) {
        	cnt++;
        	int maxInd = 0;
        	int maxInterval = INT_MIN;
        	for (int i = 0; i < res.size(); ++i) {
        		if (res[i][1] - res[i][0] > maxInterval) {
        			maxInterval = res[i][1] - res[i][0];
        			maxInd = i;
        		}
        	}
        	int start = res[maxInd][0];
        	int end = res[maxInd][1];
        	int mid = start + (end - start) / 2;
        	res[maxInd][1] = mid;
        	vector<int> newInterval = {mid + 1, end, cnt};
        	res.push_back(newInterval);
        }

        return res;
    }
};