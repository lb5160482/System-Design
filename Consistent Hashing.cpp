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

// for n = 1, return

// [
//   [0,359,1]
// ]

// represent 0~359 belongs to machine 1.

// for n = 2, return

// [
//   [0,179,1],
//   [180,359,2]
// ]

// for n = 3, return

// [
//   [0,89,1]
//   [90,179,3],
//   [180,359,2]
// ]

// for n = 4, return

// [
//   [0,89,1],
//   [90,179,3],
//   [180,269,2],
//   [270,359,4]
// ]

// for n = 5, return

// [
//   [0,44,1],
//   [45,89,5],
//   [90,179,3],
//   [180,269,2],
//   [270,359,4]
// ]
