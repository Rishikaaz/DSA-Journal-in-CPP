class Solution {
public:
    int reverseDegree(string s) {
        int n = s.length();
        int degree = 0;
        for (int i = 1; i <= n; i++) {
            int reverseidx = 26 - (s[i - 1] - 'a');
            int product = reverseidx * i;
            degree += product;
        }
        return degree;
    }
};