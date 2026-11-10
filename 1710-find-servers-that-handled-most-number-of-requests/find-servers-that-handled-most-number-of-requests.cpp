class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> busy;
        set<int> available;
        for (int i = 0; i < k; ++i) {
            available.insert(i);
        }
        
        vector<int> requestCount(k, 0);
        int n = arrival.size();
        
        for (int i = 0; i < n; ++i) {
            long long currTime = arrival[i];
            long long endTime = currTime + load[i];
            
            while (!busy.empty() && busy.top().first <= currTime) {
                available.insert(busy.top().second);
                busy.pop();
            }
            
            if (available.empty()) {
                continue;
            }
            
            int preferred = i % k;
            auto it = available.lower_bound(preferred);
            if (it == available.end()) {
                it = available.begin();
            }
            
            int server = *it;
            available.erase(it);
            busy.push({endTime, server});
            requestCount[server]++;
        }
        
        int maxRequests = 0;
        for (int count : requestCount) {
            maxRequests = max(maxRequests, count);
        }
        
        vector<int> result;
        for (int i = 0; i < k; ++i) {
            if (requestCount[i] == maxRequests) {
                result.push_back(i);
            }
        }
        
        return result;
    }
};