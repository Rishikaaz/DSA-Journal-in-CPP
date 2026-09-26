class Solution {
public:
    string evaluate(string s, vector<vector<string>>& knowledge) {
        unordered_map<string, string> map;
        for (const auto& pair : knowledge) {
            map[pair[0]] = pair[1];
        }
        
        string result = "";
        int n = s.length();
        int i = 0;
        
        while (i < n) {
            if (s[i] == '(') {
                i++;
                string key = "";
                while (i < n && s[i] != ')') {
                    key += s[i];
                    i++;
                }
                i++;
                
                if (map.find(key) != map.end()) {
                    result += map[key];
                } else {
                    result += "?";
                }
            } else {
                result += s[i];
                i++;
            }
        }
        
        return result;
    }
};