#include <bits/stdc++.h>
#include "Stack.h"

using namespace std;


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
        // cout << "string size = "<< t_s.length() << " and index = " << index << endl;
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
            // cout << "postfix string " << m_postfixString << endl;
            // cout << "now doing for " << m_ipString[i] << endl;

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
                    // cout << m_charStack.top() << " is at the top " << endl;
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

        // cout << m_charStack.size() << endl;
        // cout << " "  + string(1, m_charStack.top()) << endl;
        while(!m_charStack.empty()) {
            m_postfixString += ' ' + string(1, m_charStack.top());
            m_charStack.pop();
        }

        cout << m_postfixString << endl;
    }

    double m_evaluate() {
        string token = m_strTok(m_postfixString);
        while(token.length() > 0) {
            cout << token << endl;
            cout << "length: " << token.length() << endl;
            if(token.length() == 1 && m_isOperator(token[0])) {
                cout << "operator " << token[0] << endl;
                double a = m_valuesStack.top();
                m_valuesStack.pop();
                double b = m_valuesStack.top();
                m_valuesStack.pop();
                double c;
                cout << a << "  " << b << endl;
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
                        c = (int)b % (int)a;
                        m_valuesStack.push(c);
                        break;
                }
            } else {
                double num = stod(token);
                m_valuesStack.push(num);
            }
            token = m_strTok(m_postfixString);
        }
        // cout << fixed << std::setprecision(5) << m_valuesStack.top() << endl;
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
    setprecision(9);
    // Stack<int> s;
    // for(int i = 0; i < 20; i++) {
    //     s.push(i);
    //     cout << "inserted " << i << endl;
    //     cout << "top " << s.top() << endl;
    //     cout << "size " << s.size() << endl;
    //     cout << "container size " << s.containerSize() << endl;
    //     cout << endl;
    // }


    // for(int i = 0; i < 7; i++) {
    //     s.pop();
    //     cout << "top " << s.top() << endl;
    //     cout << "size " << s.size() << endl;
    //     cout << "container size " << s.containerSize() << endl;
    //     cout << endl;
    // }

    
    // cout << s.size() << endl;

    Calculator c;
    c.evaluate("75*854/7953/6490*1641-100");
    return 0;
}