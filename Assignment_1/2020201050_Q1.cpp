#include <bits/stdc++.h>
// #include "Stack.h"

using namespace std;

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
    // S containerSize() {
    //     return m_containerSize;
    // }
};

class Calculator {
    Stack<char> m_charStack;
    Stack<double> m_valuesStack;
    string m_postfixString;
    string m_ipString;

    char m_MUL = '*';
    const char m_DIV = '/';
    const char m_ADD = '+';
    const char m_SUB = '-';
    const char m_MOD = '%';

    int m_priority(char t_ch) {
        switch (t_ch) {
            case '(':
                return INT_MIN;
            case '*':
            case '/':
            case '%': 
                return 10;
            case '+':
            case '-':
                return 8;
            
            default:
                break;
        }
        return 0;
    }

    inline bool m_isDigit(char t_ch) {
        if(t_ch >= '0' && t_ch <= '9') {
            return true;
        }
        return false;
    }

    inline bool m_isDecimal(char t_ch) {
        if(t_ch == '.') {
            return true;
        }
        return false;
    }
    
    inline bool m_isOperator(char t_ch) {
        if(t_ch == '+' || t_ch == '-' || t_ch == '*' || t_ch == '/' || t_ch == '%') {
            return true;
        }
        return false;
    }

    inline bool m_isOpenBracket(char t_ch) {
        if(t_ch == '(') {
            return true;
        }
        return false;
    }

    inline bool m_isClosedBracket(char t_ch) {
        if(t_ch == ')') {
            return true;
        }
        return false;
    }

    static string m_strTok(string t_s) {
        static int index = 1;
        if(index >= t_s.length()) {
            return "";
        }
        int startIndex = index;
        while(t_s[index] != ' ' && index < t_s.length()) {
            index++;
        }
        return t_s.substr(startIndex, index++ - startIndex);
    }

    void m_convertInputToPostfix() {
        int strLen = m_ipString.length();
        
        int startIndex = 0;
        for(int i = 0; i < strLen; i++) {

            // If a number or double, directly add it to output string
            if(m_isDigit(m_ipString[i]) || m_isDecimal(m_ipString[i])) {
                startIndex = i;
                while(m_isDigit(m_ipString[i]) || m_isDecimal(m_ipString[i])) {
                    i++;
                }
                i--;
                m_postfixString += " " + m_ipString.substr(startIndex, i - startIndex + 1);
                continue;
            }

            // If open bracket, push to stack
            if(m_isOpenBracket(m_ipString[i])) {
                m_charStack.push(m_ipString[i]);
                continue;
            }

            // If closed bracket, pop till open bracket is encountered
            if(m_isClosedBracket(m_ipString[i])) {
                while(!m_charStack.empty() && m_charStack.top() != '(') {
                    m_postfixString += " " + string(1, m_charStack.top());
                    m_charStack.pop();
                }
                m_charStack.pop();
                continue;
            }

            // If operator, push to stack according to priority.
            if(m_isOperator(m_ipString[i])) {
                while(!m_charStack.empty() && (m_priority(m_ipString[i]) <= m_priority(m_charStack.top()))) {
                    m_postfixString += " " + string(1, m_charStack.top());
                    m_charStack.pop();
                }
                m_charStack.push(m_ipString[i]);
                continue;
            }
        }

        while(!m_charStack.empty()) {
            m_postfixString += ' ' + string(1, m_charStack.top());
            m_charStack.pop();
        }
    }

    double m_evaluate() {
        string token = m_strTok(m_postfixString);
        while(token.length() > 0) {
            if(token.length() == 1 && m_isOperator(token[0])) {
                double a = m_valuesStack.top();
                m_valuesStack.pop();
                double b = m_valuesStack.top();
                m_valuesStack.pop();
                double c;

                switch(token[0]) {
                    case '*':
                        c = a * b;
                        m_valuesStack.push(c);
                        break;
                    case '/':
                        c = b / a;
                        m_valuesStack.push(c);
                        break;
                    case '+':
                        c = a + b;
                        m_valuesStack.push(c);
                        break;
                    case '-':
                        c = b - a;
                        m_valuesStack.push(c);
                        break;
                    case '%':
                        c = fmod(b, a);
                        m_valuesStack.push(c);
                        break;
                }
            } else {
                double num = stod(token);
                m_valuesStack.push(num);
            }
            token = m_strTok(m_postfixString);
        }
        return m_valuesStack.top();
    }


public:
    Calculator(): m_postfixString(""){}
    Calculator(string t_expr): m_ipString(t_expr), m_postfixString("") {
        m_convertInputToPostfix();
        m_evaluate();
    }

    void evaluate(string t_expr) {
        m_ipString = t_expr;
        m_convertInputToPostfix();
        cout << fixed << setprecision(5) << m_evaluate();
    }
};

int main()
{
    Calculator c;
    string s;
    cin >> s;
    c.evaluate(s);
    return 0;
}