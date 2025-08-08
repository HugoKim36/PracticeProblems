template <typename T>
class hash_set {
private:
    enum class Status : int8_t {
        EMPTY = 0,
        OCCUPIED = 1,
        DELETED = 2
    };
    struct Bucket {
        Status status = Status::EMPTY;
        T key;
    };
public:
    hash_set() : data(std::vector<Bucket>(16)) { }
    
    bool insert(const T& key) {
        auto [pos, exists] = probe(key);
        if (exists) return false;
        data[pos].key = key;
        data[pos].status = Status::OCCUPIED;
        ++num_elts;
        if (load_factor() > 0.5) {
            rehash_and_grow();
        }
        return true;
    }

    bool erase(const T& key) {
        if (num_elts == 0) return false;
        auto [pos, exists] = probe(key);
        if (!exists) return false;
        data[pos].status = Status::DELETED;
        --num_elts;
        return true;
    }

    bool contains(const T& key) const {
        auto [pos, exists] = probe(key);
        return exists;
    }
private:
    // finds key or returns the position of the first empty bucket
    std::pair<size_t, bool> probe(const T& key) const {
        std::hash<T> hasher;
        size_t pos = hasher(key) % data.size();
        std::pair<size_t, bool> to_return = {pos, false};
        for (int i = 0; i < data.size(); ++i) {
            if (data[pos].status == Status::OCCUPIED && data[pos].key == key) {
                return {pos, true};
            }
            if (data[pos].status == Status::EMPTY) {
                return {pos, false};
            }
            if (data[pos].status == Status::DELETED && to_return.first == pos) {
                to_return = {pos, false};
            }
            pos = ((pos + 1) % data.size());
        }
        return to_return;
    }

    double load_factor() const {
        return (num_elts * 1.0) / data.size();
    }

    void rehash_and_grow() {
        std::vector<T> keys;
        for (auto& b : data) {
            if (b.status == Status::OCCUPIED) {
                keys.push_back(b.key);
            }
            b = Bucket{};
        }
        num_elts = 0;
        data.resize(data.size() * 2);
        for (const auto& k : keys) {
            insert(k);
        }
    }

    std::vector<Bucket> data;
    size_t num_elts;
};

class MyHashSet {
public:
    MyHashSet() { }
    
    void add(int key) {
        data.insert(key);
    }
    
    void remove(int key) {
        data.erase(key);
    }
    
    bool contains(int key) {
        return data.contains(key);
    }
private:
    hash_set<int> data;
};

/**
 * Your MyHashSet object will be instantiated and called as such:
 * MyHashSet* obj = new MyHashSet();
 * obj->add(key);
 * obj->remove(key);
 * bool param_3 = obj->contains(key);
 */
