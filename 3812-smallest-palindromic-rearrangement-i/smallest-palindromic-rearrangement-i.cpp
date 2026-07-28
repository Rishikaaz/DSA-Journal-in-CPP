class Solution {
public:
    string smallestPalindrome(string s) {
        int n = s.length();
        int half_len = n / 2;
        string first_half = s.substr(0, half_len);
        sort(first_half.begin(), first_half.end());
        string second_half = first_half;
        reverse(second_half.begin(), second_half.end());
        if (n % 2 != 0) {
            return first_half + s[half_len] + second_half;
        }
        return first_half + second_half;
    }
};