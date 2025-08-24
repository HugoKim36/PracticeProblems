class Solution {
public:
    struct Server {
        int id = 0;
        int time_free = 0;
        bool operator<(const Server& other) const {
            return (time_free > other.time_free);
        }
    };
    class ServerList {
    public:
        ServerList(int k_in) : num_free(k_in), is_free(vector<char>(k_in, true)) {
            for (int i = 0; i < k_in; ++i) {
                free_servers.insert(i);
            }
        }

        bool all_busy() const { return (num_free == 0); }
        void mark_busy (int id) {
            is_free[id] = false;
            free_servers.erase(id);
            --num_free;
        }
        void mark_free (int id) {
            is_free[id] = true;
            free_servers.insert(id);
            ++num_free;
        }
        int find_next_free(int id) const {
            if (all_busy()) return -1;
            if (is_free[id]) return id;
            auto it = free_servers.upper_bound(id);
            if (it != free_servers.end()) {
                return *it;
            }
            return *free_servers.lower_bound(0);
        }
        bool busy(int id) const { return !is_free[id]; }
    private:
        int num_free = 0;
        vector<char> is_free;
        set<int> free_servers;
    };
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        vector<int> busiest;
        vector<int> handled(k);
        priority_queue<Server> busy_servers;
        int t = 0;
        ServerList servers(k);
        int max_reqs = 0;
        for (int i = 0; i < load.size(); ++i) {
            t = max(t, arrival[i]);
            while (!busy_servers.empty() && t >= busy_servers.top().time_free) {
                servers.mark_free(busy_servers.top().id);
                busy_servers.pop();
            }
            if (servers.all_busy()) continue;
            int target = servers.find_next_free(i % k);
            servers.mark_busy(target);
            max_reqs = max(max_reqs, ++handled[target]);
            busy_servers.push({target, t + load[i]});
        }
        for (int i = 0; i < k; ++i) {
            if (handled[i] == max_reqs) busiest.push_back(i);
        }
        return busiest;
    }
};
