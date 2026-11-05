class Solution {
public:
    int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d) {
        int i = 0;
        int count = 0;
        while (i < arr1.size()) {
            int j = 0;
            bool valid = true;
            while (j < arr2.size()) {
                if (abs(arr1[i] - arr2[j]) <= d) {
                    valid = false;
                    break; 
                }
                j++;
            }
            if (valid) {
                count++;
            }
            i++;
        }
        return count;
    }
};