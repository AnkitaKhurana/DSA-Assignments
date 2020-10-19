#include<iostream>
#include<string>
#include<bits/stdc++.h>
// #include"HashTabel.h"
using namespace std;

int myhashfunction(string s) {
    int hashvalue = 0;
    int base = 1;
    for (int i = 0; i < s.size(); i++) {
        hashvalue += base * s[i];
        base*=37;
    }
    return hashvalue;
}

template<typename K, typename V>
class Node{

    Node<K, V>* _next;
    pair<K, V> _data;
public:
    Node(K key, V value):_next(NULL){
        _data.first = key;
        _data.second = value;
    }

    template<typename key, typename value>
    friend class Linked_List;
};

template<typename K, typename V>
class Linked_List {
    Node<K, V>* _head;
    Node<K, V>* _tail;
public:
    Linked_List(): _head(NULL), _tail(NULL){}

    void insert_el(K key, V value = NULL) {
        // cout << "inserting inside LL " << key << endl;
        if(_head) {
            // cout << "_head = " << _head->_data.first << endl;
        }
        Node<K, V>* temp = new Node<K, V>(key, value);
        if(!_head) {
            _head = _tail = temp;
            // cout << "_head is now " << _head->_data.first << endl; 
            return;
        }
        temp->_next = _head;
        _head = temp;
        // cout << "_head is now " << _head->_data.first << endl; 
        return;
    }

    void delete_el(K ip) {
        if(!_head) {
            return;
        }
        if(_head->_data.first == ip) {
            delete _head;
            _head = _tail = NULL;
            return;
        }

        Node<K, V>* it = _head->_next;
        Node<K, V>* prev = _head;

        while(it) {
            if(it->_data.first == ip) {
                prev->_next = it->_next;
                if(it == _tail) {
                    _tail = prev;
                }
                delete it;
                return;
            }
            prev = it;
            it = it->_next;
        }
        return;
    }

    bool search(K ip) {
        if(!_head){return false;}
        Node<K, V>* temp = _head;
        // cout << "searching inside LL" << endl;
        cout << temp->_data.first << endl;
        while(temp && temp ->_data.first != ip) {
            cout << temp ->_data.first << endl;
            temp = temp->_next;
        }
        if(temp) {
            // cout << "already exists inside LL" << endl;
            return true;
        }
        return false;
    }

    V &get(K ip) {
        Node<K, V>* temp = _head;
        while(temp && temp ->_data.first != ip) {
            temp = temp->_next;
        }
        if(temp) {
            return temp->_data.second;
        }
        throw "Key doesn't exists";
    }

    template<typename key, typename value>
    friend class Hashmap;

};


template<typename key, typename value>
class HashMap {
    Linked_List<key, value> _table[4096];
    long long int _num_elements;
    long long int _TABLE_SIZE = 4096;

    int _hash_index(key K) {
        return myhashfunction(to_string(K)) % _TABLE_SIZE;
    }

    public:
    HashMap(): _num_elements(0) {
        for(int i = 0; i < _TABLE_SIZE; i++) {
            Linked_List<key, value> b;
            _table[i] = b;
        }
    }

    bool empty() const {
        return _num_elements == 0;
    }

    long long int size() const {
        return _num_elements;
    }

    int get_table_size() const {
        return _TABLE_SIZE;
    }


    bool insert(key k, value v) {
        long long int index = _hash_index(k);
        // cout << "index inside insert " << index << endl;
        // cout << "inserting inside hashmap" << endl;
        if(_table[index].search(k)) {
            // cout << "already exists inside hashmap" << endl;
            return false;
        }
        _table[index].insert_el(k, v);
        _num_elements++;
        // rehash
        return true;
    }

    value &get(key k) {

        long long int index = _hash_index(k);
        // cout << "index inside get function " << index << endl;
        if(_table[index].search(k)) {
            return _table[index].get(k);
        }
        throw "key doesn't exist";
    }

    bool find(key k) {
        // cout << "finding " << k << endl;
        long long int index = _hash_index(k);
        // cout << "index in find = " << index << endl;
        return _table[index].search(k);
    }


    void erase(const key & k) {
        long long index = _hash_index(k);
        if(_table[index].search(k)) {
            _table[index].delete_el(k);
            _num_elements--;
        }
        return;
    }

    value & operator[](const key & k) {
        // cout << "key is " << k << endl;
        long long int index = _hash_index(k);
        // cout << "index inside operator [] " << index << endl; 
        if(_table[index].search(k)) {
            return _table[index].get(k);
        }
        
        // cout << "not found" << endl;
        _table[index].insert_el(k);
        _num_elements++;
        return _table[index].get(k);
    }
};
int main() {
    HashMap<char, int> M;
    try {

        M['a'] = 0;
        cout << M.size() << endl;

        M['b'] = 1;
        cout << M.size() << endl;

        M.insert('a', 234);
        cout << M['c'] << endl;
        // cout << M.get(string("A105")) << endl;
        cout << M.get('a') << endl;
        cout << M.get('b') << endl;
        cout << M.get('c') << endl;
        cout << M.size() << endl;
        cout << M.get('d') << endl;
        // M.erase('a');
        // // cout << M.get('c') << endl;
        // // M.erase('a');
        // // cout << M.get('a') << endl;
        // cout << M.find('a') << endl;
        // cout << M.find('b') << endl;
        // M.insert('a', 45654);
        // cout << M.size() << endl;
        // cout << M['a'] << endl;
        // M['b'] = 203948;
        // cout << M['b'] << endl;
        // cout << M.size() << endl;
        // cout << M.find('a') << endl;
    } catch(const char * msg) {
        cerr << msg << endl;

    } catch(int errorcode) {
        cerr << errorcode << endl;
    }
    return 0;
}
