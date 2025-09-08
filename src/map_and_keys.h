#ifndef MAP_AND_KEYS_H
#define MAP_AND_KEYS_H

#include <iostream>
#include <map>
#include <vector>
using namespace std;

template <typename typeKey, typename typeValue>
class map_and_keys {
public:
    map<typeKey, typeValue> _map;
    vector<typeKey> _keys;

    map_and_keys() = default;

    typeValue operator [] (typeKey tk) {
        return _map[tk];
    }
    bool Add(typeKey key, typeValue value) {
        if (std::find(_keys.begin(), _keys.end(), key) != _keys.end()) {return false;}
        _map[key]=value;
        _keys.push_back(key);
        return true;
    }
    bool Remove(typeKey removeKey) {
        if (_keys.size() == 0) { return false; }

        auto it = std::find(_keys.begin(), _keys.end(), removeKey);
        _map.erase(removeKey);
        _keys.erase(it);

        return it!=_keys.end();
    }
    bool Set(typeKey keyType, typeValue value) {
        auto it = _map.find(keyType);
        _map[it] = value;
        return it!=_map.end();
    };
    bool IsNull() { return _keys.size() == 0; }
    int size() { return _map.size(); }
    bool haveIs(typeKey key) {
        return _map.find(key) != _map.end();
    }
};
#endif //MAP_AND_KEYS_H