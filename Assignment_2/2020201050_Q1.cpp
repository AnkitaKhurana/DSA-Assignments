#include<bits/stdc++.h>

using namespace std;

template<typename L>
struct Lesser {
    bool operator()(const L ip1, const L ip2) {
        return ip1 < ip2;
    }
};

template<typename N>
class Node {
    N _data;
    int _height;
    int _count;
    Node* _left;
    Node* _right;
    int _elements_right;
    int _elements_left;
    public:
    Node(N ip): _data(ip), _left(NULL), _right(NULL), _count(1), _height(1), _elements_right(0), _elements_left(0){}
    // Node(): _left(NULL), _right(NULL){}

    template<typename T, typename C>
    friend class AVL_Tree;
};

template <typename T, typename Comp = Lesser<T> >
class AVL_Tree {
    Node<T>* _root;
    Comp _comparator;

    int _height(Node<T>* root) const{
        if(!root) {
            return 0;
        }
        return root -> _height;
    }

    int _elements_right(Node<T>* root) const{
        if(!root) {
            return 0;
        }
        return root -> _elements_right;
    }

    int _elements_left(Node<T>* root) const{
        if(!root) {
            return 0;
        }
        return root -> _elements_left;
    }

    Node<T>* _insert(Node<T>* root, T ip) {
        if(!root) {
            // cout << "inserted " << ip << endl;
            return new Node<T>(ip);
        }
        if(root -> _data == ip) {
            root -> _count++;
            return root;
        }
        int comparison_result = _comparator(root -> _data, ip);
        if(comparison_result == true) {
            // cout << ip << " is greater than " << root ->_data << endl;
            root -> _right = _insert(root -> _right, ip);
        }
        else {
            // cout << ip << " is greater than " << root ->_data << endl;
            root -> _left = _insert(root -> _left, ip);
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

    Node<T>* _check_balance(Node<T>* (&root), T ip) {

        if(abs(_height(root ->_left) - _height(root -> _right)) >= 2) {
            // cout << root ->_data << " is disbalanced " << endl;
            root = _balance(root, ip);
        }
        return root;
    }

    Node<T>* _balance(Node<T>* (&root), T ip) {
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

    Node<T>* _left_rotate(Node<T>* root) {
        Node<T>* temp = root -> _right -> _left;
        Node<T>* new_root = root -> _right;
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

    Node<T>* _right_rotate(Node<T>* root) {
        Node<T>* temp = root -> _left -> _right;
        Node<T>* new_root = root -> _left;
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

    void _inorder(const Node<T>* root) const{
        if(!root) {
            return;
        }
        _inorder(root->_left);
        for(int i = 0; i < root->_count; i++) {
            cout << root->_data << " ";
        }
        _inorder(root -> _right);
    }

    void _elements_in_range(Node<T>* root, T ip1, T ip2, int &count){
        if(!root) {
            return;
        }
        // cout << "at node " << root -> _data << endl;;

        if(!_comparator(root -> _data, ip1)) {
            _elements_in_range(root ->_left, ip1, ip2, count);
        }
        if(root->_data >= ip1 && root->_data <= ip2) {
            count += root ->_count;
            // cout << "added " << root -> _count << " for " << root -> _data << endl;
        }
        if(_comparator(root->_data, ip2)) {
            _elements_in_range(root -> _right, ip1, ip2, count);
        }

        return;
    }

    void _closest_element(Node<T>* root, T ip, T &ans) {
        if(!root) {
            return;
        }

        if(root->_data == ip) {
            ans = root->_data;
            return;
        }

        int curr_diff = abs(ip - root->_data);
        int min_diff_so_far = abs(ip - ans);

        if(curr_diff < min_diff_so_far) {
            ans = root->_data;
        }
        else if(curr_diff == min_diff_so_far) {
            ans = min(ans, root->_data);
        }

        if(_comparator(root->_data, ip)) {
            return _closest_element(root ->_right, ip, ans);
        }
        return _closest_element(root -> _left, ip, ans);
    }

    T _kth_largest(Node<T>* root, int k) {
        if(!root) {
            return NULL;
        }
        // if(root -> _elements_right == k) {
        //     return root -> _right->_data;
        // }
        if(root ->_elements_right >= k) {
            return _kth_largest(root -> _right, k);
        }
        if(root -> _elements_right < k && root->_elements_right + root->_count >= k) {
            return root -> _data;
        }
        return _kth_largest(root->_left, k - (root -> _elements_right + root->_count));
    }

    bool _is_leaf(Node<T>* root) {
        return !root->_left && !root->_right;
    }

    Node<T>* _find_min(Node<T>* root) {
        Node<T>* temp = root;
        while(temp ->_left) {
            temp = temp->_left;
        }
        return temp;
    }

    Node<T>* _delete(Node<T>* root, T ip) {
        if(!root) {
            return root;
        }

        if(root->_data == ip) {
            if( _is_leaf(root)) {
                if(root -> _count > 1) {
                    root -> _count--;
                    return root;
                }
                delete root;
                return NULL;
            }
            else if(!root->_left || !root->_right) {
                if(root -> _count > 1) {
                    root -> _count--;
                    return root;
                }
                delete root;
                return root -> _left ? root->_left : root ->_right;
                
            }
            else {
                if(root -> _count > 1) {
                    root -> _count--;
                    return root;
                }
                Node<T>* temp = _find_min(root -> _right);
                root->_data = temp->_data;
                root->_right = _delete(root->_right, temp->_data);
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


        }
        else {
            if(_comparator(root->_data, ip)) {
                root->_right = _delete(root->_right, ip);
            }
            else {
                root->_left = _delete(root->_left, ip);
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

    }
public:

    AVL_Tree(Comp ip_comparator = Comp()): _root(NULL), _comparator(ip_comparator) {}
    void insert(T ip) {
        // cout << "inserting " << ip << endl;
        if(!_root) {
            _root = new Node<T>(ip);
            return;
        }

        _root = _insert(_root, ip);
    }

    int get_height(T ip) {
        // cout << "getting height for " << ip << endl;
        if(!_root) {
            return 0;
        }
        if(_root -> _data == ip) {
            return _root -> _height;
        }

        Node<T>* temp = _root;
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

        Node<T>* temp = _root;
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

        Node<T>* temp = _root;
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
        Node<T>* temp = _root;
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

    T lower_bound(T ip) {
        if(!_root) {
            return NULL;
        }

        Node<T>* temp = _root;
        Node<T>* ans = NULL;
        while(temp) {
            if(temp ->_data == ip) {
                ans = temp;
                break;
            }
            if(_comparator(temp->_data, ip)) {
                temp = temp -> _right;
            }
            else {
                ans = temp;
                temp = temp->_left;
            }
        }

        if(!ans) {
            return NULL;
        }
        return ans -> _data;
    }

    T upper_bound(T ip) {
        if(!_root) {
            return NULL;
        }

        Node<T>* temp = _root;
        Node<T>* ans = NULL;
        while(temp) {
            if(temp -> _data == ip || _comparator(temp -> _data, ip)) {
                temp = temp -> _right;
            }
            else {
                ans = temp;
                temp = temp->_left;
            }
        }

        if(!ans) {
            return NULL;
        }
        return ans -> _data;
    }

    void inorder() {
        if(!_root) {
            return;
        }
        _inorder(_root);
    }

    int elements_in_range(T ip1, T ip2) {
        if(!_root) {
            return 0;
        }

        int count = 0;
        _elements_in_range(_root, ip1, ip2, count);
        return count;
    }

    T closest_element(T ip) {
        if(!_root) {
            return NULL;
        }

        T ans = NULL;
        _closest_element(_root, ip, ans);
        return ans;
    }

    T kth_largest(int k) {
        if(!_root || k <= 0) {
            return NULL;
        }
        return _kth_largest(_root, k);
    }

    void delete_node(T ip) {
        if(!_root) {
            return;
        }
        _root =  _delete(_root, ip);
        return;
    }
};

int main() {
    AVL_Tree<int> a;

    // int n = 1000;
    // for (int i = 1; i <= n; i ++) a.insert(i);
    // a.inorder();
    // cout << endl;
    
    // for (int i = 2; i <= n; i += 4) cout << a.search(i) << " ";
    // cout << endl;
    // // for(int i = 0; i < 20; i++) {
    // //     cout << tree.occurences(i) << endl;
    // // }
    // for (int i = 1; i <= n; i += 13) a.insert(i);
    // a.inorder();
    // cout << endl;
    
    // for (int i = 1; i <= n; i += 17) cout << a.occurences(i) << " ";
    // cout << endl;

    // for (int i = 1; i <= n; i += 21) cout << a.lower_bound(i) << " ";
    // cout << endl;

    // for (int i = 1; i <= n; i += 11) cout << a.upper_bound(i) << " ";
    // cout << endl;

    // tree.inorder();

    a.insert(1);
    // for(int i = 1; i <= 1; i++) {
    //     cout << i << ": " << a.get_height(i) << "   ";
    // }
    // cout << endl;
    a.insert(2);
    a.insert(2);
    // for(int i = 1; i <= 2; i++) {
    //     cout << i << ": " << a.get_height(i) << "   ";
    // }
    // cout << endl;
    a.insert(5);
    a.insert(5);
    a.insert(5);
    // for(int i = 1; i <= 5; i++) {
    //     cout << i << ": " << a.get_height(i) << "   ";
    // }
    // cout << endl;
    a.insert(3);
    // for(int i = 1; i <= 5; i++) {
    //     cout << i << ": " << a.get_height(i) << "   ";
    // }
    // cout << endl;
    a.insert(4);
    a.insert(4);
    // for(int i = 1; i <= 5; i++) {
    //     cout << i << ": " << a.get_height(i) << "   ";
    // }
    // cout << endl;
    a.insert(6);
    // for(int i = 1; i <= 6; i++) {
    //     cout << i << ": " << a.get_height(i) << "   ";
    // }
    // cout << endl;
    a.insert(7);
    // for(int i = 1; i <= 7; i++) {
    //     cout << i << ": " << a.get_height(i) << "   ";
    // }
    // cout << endl;
    a.insert(8);
    // a.insert(10);
    // a.insert(11);
    for(int i = 1; i <= 8; i++) {
        cout << i << ": " << a.get_height(i) << "   ";
    }
    cout << endl;

    for(int i = 1; i <= 8; i++) {
        cout << i << ": " << a.get_elements_right(i) << "   ";
    }
    cout << endl;
    // cout << a.elements_in_range(7, 8) << endl;
    // cout << a.closest_element(9) << endl;

    for(int i = 1; i <= 12; i++) {
        cout << a.kth_largest(i) << " ";
    }

    cout << endl;
    for(int i = 1; i <= 15; i++) {
        cout << a.search(i) << " ";
    }

    cout << endl;

    cout << "------------------------------------------------------" << endl;
    a.inorder();
    cout << endl;
    a.delete_node(8);
    for(int i = 1; i <= 8; i++) {
        cout << i << ": " << a.get_height(i) << "   ";
    }
    cout << endl;

    for(int i = 1; i <= 8; i++) {
        cout << i << ": " << a.get_elements_right(i) << "   ";
    }
    cout << endl;
    a.inorder();
    cout << endl << endl;
    
    a.inorder();
    cout << endl;
    a.delete_node(6);
    for(int i = 1; i <= 8; i++) {
        cout << i << ": " << a.get_height(i) << "   ";
    }
    cout << endl;

    for(int i = 1; i <= 8; i++) {
        cout << i << ": " << a.get_elements_right(i) << "   ";
    }
    cout << endl;
    a.inorder();
    cout << endl << endl;

    a.inorder();
    cout << endl;
    a.delete_node(2);
    for(int i = 1; i <= 8; i++) {
        cout << i << ": " << a.get_height(i) << "   ";
    }
    cout << endl;

    for(int i = 1; i <= 8; i++) {
        cout << i << ": " << a.get_elements_right(i) << "   ";
    }
    cout << endl;
    a.inorder();
    cout << endl << endl;

    a.inorder();
    cout << endl;
    a.delete_node(2);
    for(int i = 1; i <= 8; i++) {
        cout << i << ": " << a.get_height(i) << "   ";
    }
    cout << endl;

    for(int i = 1; i <= 8; i++) {
        cout << i << ": " << a.get_elements_right(i) << "   ";
    }
    cout << endl;
    a.inorder();
    cout << endl << endl;

    
    return 0;
}