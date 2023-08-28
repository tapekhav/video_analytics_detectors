#ifndef VIDEO_ANALYTICS_DETECTORS_PROTECTED_MAP_H
#define VIDEO_ANALYTICS_DETECTORS_PROTECTED_MAP_H

#include <map>

template<typename Value>
class ProtectedValue {
public:
    explicit ProtectedValue(const Value& value) : data(value) {}

    const Value& get() const
    {
        return data;
    }

private:
    Value data;
};

template<typename Key, typename Value>
class ProtectedMap : public std::map<Key, ProtectedValue<Value>> {
public:
    using std::map<Key, ProtectedValue<Value>>::emplace;

    ProtectedMap(std::initializer_list<std::pair<const Key, Value>> initList)
    {
        for (const auto& pair : initList)
        {
            this->emplace(pair.first, pair.second);
        }
    }

    const Value& operator[](const Key& key) const
    {
        auto it = this->find(key);
        if (it != this->end())
        {
            return it->second.get();
        }

        static ProtectedValue<Value> default_value(Value{});
        return default_value.get();
    }

    template<typename... Args>
    std::pair<typename std::map<Key, ProtectedValue<Value>>::iterator, bool> insert(Args&&... args) = delete;

    typename std::map<Key, ProtectedValue<Value>>::iterator erase(typename std::map<Key,
                                                                  ProtectedValue<Value>>::iterator) = delete;
    void clear() = delete;
};

#endif //VIDEO_ANALYTICS_DETECTORS_PROTECTED_MAP_H
