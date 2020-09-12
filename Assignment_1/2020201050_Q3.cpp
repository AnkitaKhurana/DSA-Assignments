#include<bits/stdc++.h>

using namespace std;

template <typename D>
class Deque {

    const long long int m_INIT_SIZE = 16;
    long long int m_containerSize; // keep it in power of 2, prevents greatest integer bugs
    long long int m_frontPointer; // always points to the element at the front
    long long int m_backPointer; // always points to the last element
    long long int m_numElements;
    D* m_container;

    void m_resize_container(long long int t_size) {
        if(t_size == m_containerSize) {
            return;
        }
        D* temp = new D[t_size];
        m_copy(m_container, temp, m_numElements);
        m_containerSize = t_size;
        m_frontPointer = 0;
        m_backPointer = m_frontPointer + m_numElements - 1;
        delete [] m_container;
        m_container = temp;
    }

    void m_resize_internal(long long int t_size) {
        m_backPointer = (m_frontPointer + t_size - 1) % m_containerSize;
        m_numElements = t_size;

        long long int new_container_size = m_containerSize;
        while(new_container_size / 2 > m_numElements && new_container_size > m_INIT_SIZE) {
            new_container_size /= 2;
        }
        m_resize_container(new_container_size);
        return;
    }

    // Its not this function's job to verify if the space to copy is sufficient. Its only job is to copy the contents.
    void m_copy(D* t_source, D* t_destination, long long int t_num_elements) {
        long long int src_index = m_frontPointer;
        long long int dest_index = 0;
        long long int elementsCopied = 0;
        while(elementsCopied != t_num_elements) {
            t_destination[dest_index++] = t_source[src_index];
            src_index = (src_index + 1) % m_containerSize;
            elementsCopied++;;
        }

        t_destination[dest_index] = t_source[src_index];        
        return;
    }
public:
    Deque(): m_containerSize(m_INIT_SIZE), m_frontPointer(-1), m_backPointer(-1), m_numElements(0) {
        m_container = new D[m_containerSize];
    }

    Deque(long long int t_size, D t_default_val): m_frontPointer(-1), m_backPointer(-1), m_numElements(0){
        if(t_size <= 0) {
            m_container = new D[m_INIT_SIZE];
            m_containerSize = m_INIT_SIZE;
            m_frontPointer = m_backPointer = -1;
            m_numElements = 0;
            return;
        }

        long long int new_container_size = m_INIT_SIZE;
        while(new_container_size < t_size) {
            new_container_size *= 2;
        }

        m_containerSize = new_container_size;
        m_container = new D[m_containerSize];
        while(t_size--) {
            push_back(t_default_val);
        }
        
    }

    void push_front(D t_item) {
        if(m_frontPointer == -1) { // container empty
            m_container[++m_frontPointer] = t_item;
            m_backPointer = m_frontPointer;
            m_numElements++;
            return;
        }

        long long int temp_frontpointer = m_frontPointer;
        temp_frontpointer = (temp_frontpointer - 1 + m_containerSize) % m_containerSize;
        if(temp_frontpointer == m_backPointer) { // container full
            m_resize_container(m_containerSize * 2);
        }
        temp_frontpointer = (m_frontPointer - 1 + m_containerSize) % m_containerSize;
        m_container[temp_frontpointer] = t_item;
        m_frontPointer = temp_frontpointer;
        m_numElements++;
        return;
    }

    void push_back(D t_item) {
        if(m_backPointer == -1) {
            m_container[++m_backPointer] = t_item;
            m_frontPointer = m_backPointer;
            m_numElements++;
            return;
        }

        long long int temp_backpointer = m_backPointer;
        temp_backpointer = (temp_backpointer + 1) % m_containerSize;
        if(temp_backpointer == m_frontPointer) { // container full
            m_resize_container(m_containerSize * 2);
        }
        temp_backpointer = (m_backPointer + 1) % m_containerSize;
        m_container[temp_backpointer] = t_item;
        m_backPointer = temp_backpointer;
        m_numElements++;
        return;
    }

    void pop_front() {
        if(m_frontPointer == -1) { return; }
        if(m_frontPointer == m_backPointer) { // one element remaining, delete it and reduce container to original size
            m_frontPointer = m_backPointer = -1;
            m_numElements--;
            return;
        }

        m_frontPointer = (m_frontPointer + 1) % m_containerSize;
        m_numElements--;
        if(m_numElements < m_containerSize / 2 && m_containerSize > 16) { m_resize_container(m_containerSize / 2); }
        return;
    }

    void pop_back() {
        if(m_backPointer == -1) { return; }
        if(m_backPointer == m_frontPointer) { // one element remaining, delete it and reduce container to original size
            m_backPointer = m_frontPointer = -1;
            m_numElements--;
            return;
        }

        m_backPointer = (m_backPointer - 1 + m_containerSize) % m_containerSize;
        m_numElements--;
        if(m_numElements < m_containerSize / 2 && m_containerSize > 16) { m_resize_container(m_containerSize / 2); }
    }
    bool empty() {
        cout << (m_numElements == true) << endl;
        return m_numElements == 0;
    }

    D front() {
        if(m_frontPointer < 0) { 
            cout << endl;
            return NULL;
        }
        cout << m_container[m_frontPointer] << endl;
        return m_container[m_frontPointer];
    }

    D back() {
        if(m_backPointer < 0) { 
            cout << endl;
            return NULL;
        }
        // cout << "back pointer "<< m_backPointer << endl;
        cout << m_container[m_backPointer] << endl;
        return m_container[m_backPointer];
    }

    long long int size() {
        cout << m_numElements << endl;
        return m_numElements;
    }

    void clear() {
        m_numElements = 0;
        m_frontPointer = m_backPointer = -1;
        return;
    }

    D operator [] (long long int t_index) {
        if(t_index < 0 || t_index >= m_numElements) { return NULL; }
        return (m_container[(m_frontPointer + t_index) % m_containerSize]);
    }

    void resize(long long int t_size, D t_default_val) {
        if(t_size == 0) { clear(); }
        if(m_numElements == t_size || t_size < 0) {
            return;
        }
        if(m_numElements < t_size) {
            long long int elements_to_insert = t_size - m_numElements;
            while(elements_to_insert--) {
                push_back(t_default_val);
            }
            return;
        }
        m_resize_internal(t_size);
        return;
    }

    // TODO: Delete this function before final submission.
    long long int container_size() {
        cout << m_containerSize << endl;
        return m_containerSize;
    }

    void display() {
        if(m_frontPointer == -1) { return; }
        long long int i = m_frontPointer;
        long long int size = m_numElements;
        
        while(size--) {
            cout << m_container[m_frontPointer] << " ";
            i = (i + 1) % m_containerSize;
        }
        return;
    }
    
};

int main() {

    return 0;
}