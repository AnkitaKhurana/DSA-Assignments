#include<bits/stdc++.h>

using namespace std;

template<typename L>
struct Lesser {
    bool operator()(const L ip1, const L ip2) {
        return ip1 < ip2;
    }
};

template<typename N, typename V>
class Node {
    N _data;
    V _value;
    int _height;
    int _count;
    Node* _left;
    Node* _right;
    int _elements_right;
    int _elements_left;
    public:
    Node(N ipkey, V ipval): _data(ipkey), _value(ipval), _left(NULL), _right(NULL), _count(1), _height(1), _elements_right(0), _elements_left(0){}
    // Node(): _left(NULL), _right(NULL){}

    template<typename T, typename val, typename C>
    friend class AVL_Tree;
};

template <typename T, typename V, typename Comp = Lesser<T> >
class AVL_Tree {
    Node<T, V>* _root;
    Comp _comparator;

    int _height(Node<T, V>* root) const{
        if(!root) {
            return 0;
        }
        return root -> _height;
    }

    int _elements_right(Node<T, V>* root) const{
        if(!root) {
            return 0;
        }
        return root -> _elements_right;
    }

    int _elements_left(Node<T, V>* root) const{
        if(!root) {
            return 0;
        }
        return root -> _elements_left;
    }

    Node<T, V>* _insert(Node<T, V>* root, T ip, V val) {
        if(!root) {
            // cout << "inserted " << ip << endl;
            return new Node<T, V>(ip, val);
        }
        if(root -> _data == ip) {
            root -> _value = val;
            return root;
        }
        int comparison_result = _comparator(root -> _data, ip);
        if(comparison_result == true) {
            // cout << ip << " is greater than " << root ->_data << endl;
            root -> _right = _insert(root -> _right, ip, val);
        }
        else {
            // cout << ip << " is greater than " << root ->_data << endl;
            root -> _left = _insert(root -> _left, ip, val);
        }
        root -> _height = max(_height(root->_left), _height(root -> _right)) + 1;

        root -> _elements_right = root -> _right ? _elements_right(root->_right) + _elements_left(root ->_right) + root->_right->_count : 0;
        root -> _elements_left = root -> _left ? _elements_left(root -> _left) + _elements_right(root -> _left) + root->_left->_count : 0; 
        // cout << root ->_data << " height is " << root -> _height << endl;
        root = _check_balance(root, ip);
        // cout << "balanced check inside insert" << endl;
        // cout << "now root is " << root -> _data << endl;
        // cout << "right child of " << root -> _data << " is " << get_elements_right(root->_data) << endl;
        return root;

    }

    Node<T, V>* _check_balance(Node<T, V>* (&root), T ip) {

        if(abs(_height(root ->_left) - _height(root -> _right)) >= 2) {
            // cout << root ->_data << " is disbalanced " << endl;
            root = _insert_balance(root, ip);
        }
        return root;
    }

    int _get_balance(Node<T, V>* root) {
        if(!root) {
            return 0;
        }
        return _height(root ->_left) - _height(root -> _right);
    }
    Node<T, V>* _insert_balance(Node<T, V>* (&root), T ip) {
        // L-R Imbalance
        if(root -> _left && !_comparator(root -> _data, ip) && _comparator(root -> _left -> _data, ip)) {
            // cout << "R-L Imbalance" << endl;
            root ->_left =  _left_rotate(root -> _left);
            // cout << "root after left rotation is " << root ->_data << endl;
            root = _right_rotate(root);
            return root;
        }

        // R-L Imbalance
        if(root ->_right && _comparator(root -> _data, ip) && !_comparator(root -> _right -> _data, ip)) {
            root ->_right = _right_rotate(root-> _right);
            root = _left_rotate(root);
            return root;
        }

        // L-L Imbalance
        if(root -> _left && !_comparator(root-> _data, ip) && !_comparator(root->_left->_data, ip)) {
            root = _right_rotate(root);
            return root;
        }

         // R-R Imbalance
        if(root -> _right && _comparator(root-> _data, ip) && _comparator(root->_right->_data, ip)) {
            root = _left_rotate(root);
            return root;
        }
    }

    Node<T, V>* _left_rotate(Node<T, V>* root) {
        Node<T, V>* temp = root -> _right -> _left;
        Node<T, V>* new_root = root -> _right;
        new_root -> _left = root;
        root -> _right = temp;

        root -> _height = max(_height(root->_left), _height(root -> _right)) + 1;
        new_root -> _height = max(_height(new_root->_left), _height(new_root -> _right)) + 1;

        root -> _elements_right = root -> _right ? _elements_right(root -> _right) + root->_right->_count + _elements_left(root->_right) : 0;
        root -> _elements_left = root -> _left ? _elements_left(root -> _left) + root->_left->_count + _elements_right(root ->_left) : 0;
        new_root -> _elements_right = new_root -> _right ? _elements_right(new_root -> _right) + new_root->_right->_count + _elements_left(new_root->_right) : 0;
        new_root -> _elements_left = new_root -> _left ? _elements_right(new_root->_left) + new_root->_left->_count + _elements_left(new_root -> _left) : 0;
        return new_root;
    }

    Node<T, V>* _right_rotate(Node<T, V>* root) {
        Node<T, V>* temp = root -> _left -> _right;
        Node<T, V>* new_root = root -> _left;
        new_root -> _right = root;
        root -> _left = temp;

        root -> _height = max(_height(root->_left), _height(root -> _right)) + 1;
        new_root -> _height = max(_height(new_root->_left), _height(new_root -> _right)) + 1;

        
        root -> _elements_right = root -> _right ? _elements_right(root -> _right) + 1 + _elements_left(root->_right) : 0;
        root -> _elements_left = root -> _left ? _elements_left(root -> _left) + 1 + _elements_right(root ->_left) : 0;
        new_root -> _elements_right = new_root -> _right ? _elements_right(new_root -> _right) + 1 + _elements_left(new_root->_right) : 0;
        new_root -> _elements_left = new_root -> _left ? _elements_right(new_root->_left) + 1 + _elements_left(new_root -> _left) : 0;
        return new_root;
    }

    void _inorder(const Node<T, V>* root) const{
        if(!root) {
            return;
        }
        _inorder(root->_left);
        for(int i = 0; i < root->_count; i++) {
            cout << root->_data << " ";
        }
        _inorder(root -> _right);
    }

    bool _is_leaf(Node<T, V>* root) {
        return !root->_left && !root->_right;
    }

    Node<T, V>* _find_min(Node<T, V>* root) {
        Node<T, V>* temp = root;
        while(temp ->_left) {
            temp = temp->_left;
        }
        return temp;
    }

    Node<T, V>* _delete(Node<T, V>* root, T ip) {
        if(!root) {
            return root;
        }
        // cout << "at " << root->_data << " for deleting "<< ip << endl;
        if(root->_data == ip) {
            // cout << "element to be deleted matched " << endl;
            if( _is_leaf(root)) {
                // cout << "is leaf" << endl;
                if(root -> _count > 1) {
                    root -> _count--;
                    return root;
                }
                delete root;
                return NULL;
            }
            else if(!root->_left || !root->_right) {
                // cout << "has single child" << endl;
                if(root -> _count > 1) {
                    root -> _count--;
                    return root;
                }
                delete root;
                return root -> _left ? root->_left : root ->_right;
                
            }
            else {
                // cout << "double children" << endl;
                if(root -> _count > 1) {
                    root -> _count--;
                    return root;
                }
                Node<T, V>* temp = _find_min(root -> _right);
                // cout << "swapped " << root->_data << " with " << temp->_data << endl;
                root->_data = temp->_data;
                root->_right = _delete(root->_right, temp->_data);
                // cout << root->_data << "'s right is now" << root->_right->_data << endl;
                root -> _height = max(_height(root->_left), _height(root -> _right)) + 1;

                root -> _elements_right = root -> _right ? _elements_right(root->_right) + _elements_left(root ->_right) + root->_right->_count : 0;
                root -> _elements_left = root -> _left ? _elements_left(root -> _left) + _elements_right(root -> _left) + root->_left->_count : 0; 
                // cout << root ->_data << " height is " << root -> _height << endl;

                int balance = _get_balance(root);

                if (balance > 1 &&  _get_balance(root->_left) >= 0)  
                    return _right_rotate(root);  
            
                // Left Right Case  
                if (balance > 1 &&  _get_balance(root->_left) < 0)  
                {  
                    root->_left = _left_rotate(root->_left);  
                    return _right_rotate(root);  
                }  
            
                // Right Right Case  
                if (balance < -1 &&  _get_balance(root->_right) <= 0)  
                    return _left_rotate(root);  
            
                // Right Left Case  
                if (balance < -1 &&  _get_balance(root->_right) > 0)  
                {  
                    root->_right = _right_rotate(root->_right);  
                    return _left_rotate(root);  
                }  
                // root = _check_balance(root, ip);
                // cout << "balanced check inside insert" << endl;
                // cout << "now root is " << root -> _data << endl;
                // cout << "right child of " << root -> _data << " is " << get_elements_right(root->_data) << endl;
                return root;
            }


        }
        else {
            if(_comparator(root->_data, ip)) {
                root->_right = _delete(root->_right, ip);
            }
            else {
                root->_left = _delete(root->_left, ip);
            }
            root -> _height = max(_height(root->_left), _height(root -> _right)) + 1;
            // cout << "height of " << root->_data << " is updated to " << root->_height << endl;
            root -> _elements_right = root -> _right ? _elements_right(root->_right) + _elements_left(root ->_right) + root->_right->_count : 0;
            root -> _elements_left = root -> _left ? _elements_left(root -> _left) + _elements_right(root -> _left) + root->_left->_count : 0; 
            // cout << root ->_data << " height is " << root -> _height << endl;
            int balance = _get_balance(root);

                if (balance > 1 &&  _get_balance(root->_left) >= 0)  
                    return _right_rotate(root);  
            
                // Left Right Case  
                if (balance > 1 &&  _get_balance(root->_left) < 0)  
                {  
                    root->_left = _left_rotate(root->_left);  
                    return _right_rotate(root);  
                }  
            
                // Right Right Case  
                if (balance < -1 &&  _get_balance(root->_right) <= 0)  
                    return _left_rotate(root);  
            
                // Right Left Case  
                if (balance < -1 &&  _get_balance(root->_right) > 0)  
                {  
                    root->_right = _right_rotate(root->_right);  
                    return _left_rotate(root);  
                }
            // cout << "balanced check inside insert" << endl;
            // cout << "now root is " << root -> _data << endl;
            // cout << "right child of " << root -> _data << " is " << get_elements_right(root->_data) << endl;
            return root;
        }

    }

    Node<T, V>* _get(T ip) {
        if(!_root) {
            return NULL;
        }
        Node<T, V>* temp = _root;
        while(temp) {
            if(temp ->_data == ip) {
                return temp;
            }
            if(_comparator(temp->_data, ip)) {
                temp = temp -> _right;
                continue;
            }
            temp = temp -> _left;
        }
        return NULL;
    }

    void _clear(Node<T,V>* root) {
        if(!root) {
            return;
        }
        _clear(root->_left);
        _clear(root->_right);
        delete root;
        return;
    }
public:

    AVL_Tree(Comp ip_comparator = Comp()): _root(NULL), _comparator(ip_comparator) {}
    void insert(T ip, V val) {
        // cout << "inserting " << ip << endl;
        if(!_root) {
            _root = new Node<T, V>(ip, val);
            return;
        }

        _root = _insert(_root, ip, val);
    }

    int get_height(T ip) {
        // cout << "getting height for " << ip << endl;
        if(!_root) {
            return 0;
        }
        if(_root -> _data == ip) {
            return _root -> _height;
        }

        Node<T, V>* temp = _root;
        while(temp) {
            // cout << temp -> _data << endl;
            if(temp -> _data == ip) {
                return temp -> _height;
            }
            if(_comparator(temp->_data, ip)) {
                temp = temp -> _right;
                continue;
            }
            else if(!_comparator(temp->_data, ip)) {
                temp = temp ->_left;
                continue;
            }
        } 
        return 0;
    }

    int get_elements_right(T ip) {
        // cout << "getting height for " << ip << endl;
        if(!_root) {
            return 0;
        }
        if(_root -> _data == ip) {
            return _root -> _elements_right;
        }

        Node<T, V>* temp = _root;
        while(temp) {
            // cout << temp -> _data << endl;
            if(temp -> _data == ip) {
                return temp -> _elements_right;
            }
            if(_comparator(temp->_data, ip)) {
                temp = temp -> _right;
                continue;
            }
            else if(!_comparator(temp->_data, ip)) {
                temp = temp ->_left;
                continue;
            }
        } 
        return 0;
    }

    bool search(T ip) {
        if(!_root) {
            return false;
        }

        Node<T, V>* temp = _root;
        while(temp) {
            if(temp ->_data == ip) {
                return true;
            }
            if(_comparator(temp->_data, ip)) {
                temp = temp -> _right;
                continue;
            }
            temp = temp -> _left;
        }
        return false;
    }

    int occurences(T ip) {
        if(!_root) {
            return 0;
        }
        Node<T, V>* temp = _root;
        while(temp) {
            if(temp ->_data == ip) {
                return temp->_count;
            }
            if(_comparator(temp->_data, ip)) {
                temp = temp -> _right;
                continue;
            }
            temp = temp -> _left;
        }
        return 0;
    }

    void inorder() {
        if(!_root) {
            return;
        }
        _inorder(_root);
    }

    void delete_node(T ip) {
        if(!_root) {
            return;
        }
        _root =  _delete(_root, ip);
        return;
    }

    long long int size() {
        if(!_root) {
            return 0;
        }
        return _root->_elements_right + _root -> _elements_left + 1;
    }

    V & operator[](T ip) {
        if(search(ip)) {
            return _get(ip)->_value;
        }
        insert(ip, NULL);
        return _get(ip) -> _value;
    }

    void clear() {
        if(!_root) {
            return;
        }
        _clear(_root);
    }
};

template<typename key, typename value>
class Ordered_Map{
    AVL_Tree<key, value> map;

public:
    Ordered_Map(){}

    void insert(key k, value v) {
        map.insert(k, v);
        return;
    }

    void erase(key k) {
        map.delete_node(k);
        return;
    }

    bool find(key k) {
        return map.search(k);
    }

    value & operator[](key k) {
        return map[k];
    }

    long long int size() {
        return map.size();
    }

    void clear() {
        map.clear();
        return;
    }
};


int main() {

    Ordered_Map<string, int> om;
    string s = "asldfkj";
    om.insert(s, 123);
    cout << om[s] << endl;
    om[s] = om[s] + 3;
    cout << om[s] << endl;
    cout << om.size() << endl;

    string s2 = "wibzw";
    om.insert(s2, 987);
    cout << endl << endl << om[s2] << endl;

    om[s2] = om[s2] + 255;
    cout << om[s2] << endl;
    // cout << om.erase('a') << endl;
    // om.erase('a');
    // cout << om.size() << endl;
    // cout << om['a'] << endl;
    // om['a'] = 1234;
    // cout <<om['a'] << endl;
    // om.insert('d', 456);
    // cout<<om['d']<<endl;
    return 0;
}


