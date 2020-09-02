#include <bits/stdc++.h>

using namespace std;

class BigInteger {
    long long int m_INIT_LENGTH = 16;
    long long int m_containerSize;
    long long int m_numLength;
    long long int m_lastDigitPointer;
    int *m_container;

    long long int m_size(long long int &num) const{
        long long int temp = num;
        long long int count = 0;
        while(temp) {
            count++;
            temp /= 10;
        }
        return count;
    }

public:
    BigInteger(): m_lastDigitPointer(0), m_numLength(0) , m_containerSize(m_INIT_LENGTH){
        m_container = new int[m_containerSize];
    }

    BigInteger(long long int &t_num): m_lastDigitPointer(0), m_containerSize(m_INIT_LENGTH) {
        m_container = new int[m_containerSize];
        
        long long int numSize = m_size(t_num);
        m_resize();
    }

    BigInteger(BigInteger &t_bi){}

    string value(){}
};

int main() {

    return 0;
}