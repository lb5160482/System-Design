// consistnt hashing-----virtual nodes
class Solution {
private:
    vector<int> list;
    int numPerMahine;
    unordered_map<int, vector<int>> machineList;
public:
    // @param n a positive integer
    // @param k a positive integer
    // @return a Solution object
    static Solution create(int n, int k) {
        Solution solution = Solution(n, k);
        
        return solution;
    }

    Solution(int number, int machineSize) : list(vector<int>(number, 0)), numPerMahine(machineSize) {
        srand(time(NULL));
    }

    // @param machine_id an integer
    // @return a list of shard ids
    vector<int> addMachine(int machine_id) {
        for (int i = 0; i < numPerMahine; ++i) {
            int num = rand() % list.size();
            while (list[num] != 0) {
                num = rand() % list.size();
            }
            list[num] = machine_id;
            machineList[machine_id].push_back(num);
        }
        sort(machineList[machine_id].begin(),  machineList[machine_id].end());
        return machineList[machine_id];
    }

    // @param hashcode an integer
    // @return a machine id
    int getMachineIdByHashCode(int hashcode) {
        hashcode %= list.size();
        while (list[hashcode] == 0) {
            hashcode++;
            if (hashcode == list.size()) {
                hashcode = 0;
            }
        }

        return list[hashcode];
    }
};
