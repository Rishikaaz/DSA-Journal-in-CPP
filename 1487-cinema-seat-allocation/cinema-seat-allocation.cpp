class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        unordered_map<int, int> reservedMap;
        for (const auto& seat : reservedSeats) {
            int row = seat[0];
            int col = seat[1];
            if (col >= 2 && col <= 9) {
                reservedMap[row] |= (1 << (col - 1));
            }
        }
        
        long long totalGroups = (long long)(n - reservedMap.size()) * 2;
        int leftMask = etablishMask(2, 5);
        int rightMask = etablishMask(6, 9);
        int middleMask = etablishMask(4, 7);
        for (auto& pair : reservedMap) {
            int mask = pair.second;
            bool leftAvailable = (mask & leftMask) == 0;
            bool rightAvailable = (mask & rightMask) == 0;
            
            if (leftAvailable && rightAvailable) {
                totalGroups += 2;
            } else if (leftAvailable || rightAvailable) {
                totalGroups += 1;
            } else if ((mask & middleMask) == 0) {
                totalGroups += 1;
            }
        }
        return totalGroups;
    }

private:
    int etablishMask(int start, int end) {
        int m = 0;
        for (int i = start; i <= end; ++i) {
            m |= (1 << (i - 1));
        }
        return m;
    }
};