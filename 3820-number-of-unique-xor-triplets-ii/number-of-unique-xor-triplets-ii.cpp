class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        bitset<2048> pair_xor, triplet_xor;
        for (int x : nums)
            for (int y : nums)
                pair_xor[x ^ y] = 1;
        for (int p = 0; p < 2048; ++p)
            if (pair_xor[p])
                for (int x : nums)
                    triplet_xor[p ^ x] = 1;
        return triplet_xor.count();
    }
};