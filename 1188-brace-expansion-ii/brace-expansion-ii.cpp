class Solution {
public:
    set<string> parse(string s) {
        vector<string> parts;
        int depth = 0;
        int start = 0;
        for (int i = 0; i < s.length(); ++i) {
            if (s[i] == '{') depth++;
            else if (s[i] == '}') depth--;
            else if (s[i] == ',' && depth == 0) {
                parts.push_back(s.substr(start, i - start));
                start = i + 1;
            }
        }
        parts.push_back(s.substr(start));

        if (parts.size() > 1) {
            set<string> result;
            for (const auto& p : parts) {
                set<string> sub = parse(p);
                result.insert(sub.begin(), sub.end());
            }
            return result;
        }

        vector<set<string>> factors;
        int i = 0;
        while (i < s.length()) {
            if (s[i] == '{') {
                int j = i, d = 0;
                while (j < s.length()) {
                    if (s[j] == '{') d++;
                    else if (s[j] == '}') d--;
                    if (d == 0) break;
                    j++;
                }
                string inner = s.substr(i + 1, j - i - 1);
                factors.push_back(parse(inner));
                i = j + 1;
            } else {
                int j = i;
                while (j < s.length() && s[j] != '{') {
                    j++;
                }
                string word = s.substr(i, j - i);
                factors.push_back({word});
                i = j;
            }
        }

        set<string> current = {""};
        for (const auto& factor : factors) {
            set<string> next;
            for (const auto& prefix : current) {
                for (const auto& word : factor) {
                    next.insert(prefix + word);
                }
            }
            current = next;
        }
        return current;
    }

    vector<string> braceExpansionII(string expression) {
        set<string> resSet = parse(expression);
        return vector<string>(resSet.begin(), resSet.end());
    }
};