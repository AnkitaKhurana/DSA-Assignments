#ifndef STACK_H
#define STACK_H
template <typename S>
class Stack
{
    const long long int m_INIT_SIZE = 16;
    long long int m_containerSize;
    long long int m_stackPointer;
    long long int m_numElements;
    S* m_container;

    void m_Resize() {
        if(m_numElements + 1 == m_containerSize) {
            S* temp = new S[2*m_containerSize];
            m_containerSize *= 2;
            m_Copy(temp);
            delete [] m_container;
            m_container = temp;
        }
        else if((m_numElements < (m_containerSize/2)) && (m_containerSize > m_INIT_SIZE)) {
            S* temp = new S[m_containerSize/2];
            m_containerSize /= 2;
            m_Copy(temp);
            delete [] m_container;
            m_container = temp;
        }
    }

    void m_Copy(S* t_temp) {
        for(int i = 0; i < m_numElements; i++) {
            t_temp[i] = m_container[i];
        }
        return;
    }


public:
    Stack(): m_containerSize(m_INIT_SIZE), m_stackPointer(0), m_numElements(0) {
        m_container = new S[m_containerSize];
    }   

    void push(S t_ip) {
        m_container[m_stackPointer++] = t_ip;
        m_numElements++;
        m_Resize();
        return;
    }

    void pop() {
        if( !m_numElements ) return;
        m_stackPointer--;
        m_numElements--;
        m_Resize();
        return;
    }

    long long int size() {
        return m_numElements;
    }

    S top() {
        if(m_numElements < 1) return NULL;
        return m_container[m_numElements - 1];
    }

    bool empty() {
        return m_numElements == 0;
    }

    void clear() {
        m_numElements = 0;
        m_stackPointer = 0;
        m_Resize();
        return;
    }
        
    //TODO: delete this method. Its purpose is only for debugging
    S containerSize() {
        return m_containerSize;
    }
};


#endif