class Solution {
    int convertToDays(string date) {
        vector<int> days = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        int month = stoi(date.substr(0, 2));
        int day = stoi(date.substr(3, 2));
        int total_days = day;
        for (int i = 0; i < month - 1; ++i) {
            total_days += days[i];
        }
        return total_days;
    }
public:
    int countDaysTogether(string arriveAlice, string leaveAlice, string arriveBob, string leaveBob) {
        int aliceStart = convertToDays(arriveAlice);
        int aliceEnd = convertToDays(leaveAlice);
        int bobStart = convertToDays(arriveBob);
        int bobEnd = convertToDays(leaveBob);
        
        int overlapStart = max(aliceStart, bobStart);
        int overlapEnd = min(aliceEnd, bobEnd);
        
        if (overlapStart <= overlapEnd) {
            return overlapEnd - overlapStart + 1;
        }
        return 0;
    }
};