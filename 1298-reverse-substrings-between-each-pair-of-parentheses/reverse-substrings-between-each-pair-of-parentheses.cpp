class Solution {
public:
    string reverseParentheses(string s) {
        stack<string> st;
        string result = "";
        for (char c : s) {
            if (c == '(') {
                st.push(result);
                result = "";
            } else if (c == ')') {
                reverse(result.begin(), result.end());
                if (!st.empty()) {
                    result = st.top() + result;
                    st.pop();
                }
            } else {
                result += c;
            }
        }
        return result;
    }
};