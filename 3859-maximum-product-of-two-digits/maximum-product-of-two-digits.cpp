class Solution {
public:
    int maxProduct(int n) {
        int maxproduct = 0;
        vector<int> arr;
        while (n > 0) {
            arr.push_back(n % 10);
            n /= 10;
        }
        for (size_t i = 0; i < arr.size(); i++) {
            for (size_t j = i + 1; j < arr.size(); j++) {
                int product = arr[i] * arr[j];
                maxproduct = max(maxproduct, product);
            }
        }
        return maxproduct;
    }
};