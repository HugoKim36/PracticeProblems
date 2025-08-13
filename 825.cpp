class Solution {
public:
    int numFriendRequests(vector<int>& ages) {
        ranges::sort(ages);
        int num_requests = 0;
        for (auto it = ages.begin(); it != ages.end(); ++it) {
            int age = *it;
            auto age_end = upper_bound(ages.begin(), ages.end(), age);
            auto age_begin = lower_bound(ages.begin(), ages.end(), age);
            int people_with_age = (age_end - age_begin);

            auto group_begin = upper_bound(ages.begin(), ages.end(), (age * 0.5) + 7);
            auto group_end = upper_bound(ages.begin(), ages.end(), age);
            if (group_begin == ages.end() || group_begin >= group_end) continue;

            int group_size = abs(distance(group_end, group_begin));
            
            if (group_begin <= it && it < group_end) --group_size;
            num_requests += (group_size) * (people_with_age);
            it = prev(upper_bound(ages.begin(), ages.end(), age));
        }
        return num_requests;
    }
};
