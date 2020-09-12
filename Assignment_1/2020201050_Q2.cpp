#include <bits/stdc++.h>

using namespace std;

class BigInteger {
    long long int m_INIT_LENGTH = 16;
    long long int m_containerSize;
    long long int m_numLength;
    long long int m_lastDigitPointer;
    string m_container;

    static inline bool m_size_gt_2(int &num) {
        long long int temp = num;
        long long int count = 0;
        while(temp) {
            count++;
            temp /= 10;
            if(count >= 2) {
                return true;
            }
        }
        return false;
    }

    static inline int m_add_chars(char t_ch_a, char t_ch_b) {
        int a = t_ch_a - '0';
        int b = t_ch_b - '0';

        return a + b;
    }

    static inline int m_multiply_chars(char t_ch_a, char t_ch_b) {
        int a = t_ch_a - '0';
        int b = t_ch_b - '0';

        return a * b;
    }

    static inline int m_divide_chars(char t_ch_a, char t_ch_b) {
        int a = t_ch_a - '0';
        int b = t_ch_b - '0';

        return a / b;
    }

    static inline int m_subtract_chars(char t_ch_a, char t_ch_b) {
        int a = t_ch_a - '0';
        int b = t_ch_b - '0';

        return a - b;
    }

    static inline char m_int_to_char(int t_num) {
        return t_num + '0';
    }

    static int m_compare(string &t_num_a, string t_num_b) {
        if(t_num_a.size() > t_num_b.size()) {
            return 1;
        }
        else if(t_num_b.size() > t_num_a.size()) {
            return -1;
        }
        else {
            string :: iterator ita;
            string :: iterator itb;
            for(ita = t_num_a.begin(), itb = t_num_b.begin() ; ita != t_num_a.end(); ita++, itb++) {
                if(*ita > *itb) { return 1; }
                if(*itb > *ita) { return -1; }
            }

            return 0;
        }
    }

    void m_add_bigint(string &t_bigint_a, string &t_bigint_b, long long int t_buffer = 0) {
        long long int carry = 0;
        long long int container_index = t_bigint_a.length() - 1 - t_buffer;

        int intermediate_addition_result = 0;
        for(int i = t_bigint_b.length() - 1; i >= 0; i--) {
            if(container_index < 0) {
                intermediate_addition_result = m_add_chars('0', t_bigint_b[i]);
                intermediate_addition_result += carry;
                if(m_size_gt_2(intermediate_addition_result)) {
                    t_bigint_a = m_int_to_char(intermediate_addition_result % 10) + t_bigint_a;
                    carry = intermediate_addition_result / 10;
                } 
                else {
                    t_bigint_a = m_int_to_char(intermediate_addition_result) + t_bigint_a;
                    carry = 0;
                }
            } else {
                intermediate_addition_result = m_add_chars(t_bigint_a[container_index], t_bigint_b[i]);
                intermediate_addition_result += carry;
                if(m_size_gt_2(intermediate_addition_result)) {
                    t_bigint_a[container_index] = m_int_to_char(intermediate_addition_result % 10);
                    carry = intermediate_addition_result / 10;
                }
                else {
                    t_bigint_a[container_index] = m_int_to_char(intermediate_addition_result);
                    carry = 0;
                }
            }
            container_index--;
        }
        while(carry != 0) {
            if(container_index < 0) {
                intermediate_addition_result = m_add_chars('0', carry + '0');
                t_bigint_a = m_int_to_char(intermediate_addition_result % 10) + t_bigint_a;
                carry = intermediate_addition_result / 10;
            } 
            else {
                intermediate_addition_result = m_add_chars(t_bigint_a[container_index], carry + '0');
                t_bigint_a[container_index] = m_int_to_char(intermediate_addition_result % 10);
                carry = intermediate_addition_result / 10;
            }
            container_index--;
        }
    }

    string m_subtract(string t_a, string t_b) {
        int borrow = 0;
        int i;
        int t_a_index = t_a.size() - 1;
        for( i = t_b.size() - 1; i >= 0; i--, t_a_index--) {
            if(t_a[t_a_index] == '0') {
                if(borrow) {
                    t_a[t_a_index] = '9';
                    borrow = 1;
                }
            }
            else {
                if(borrow) {
                    t_a[t_a_index]--;
                }
            }

            if(t_a[t_a_index] < t_b[i]) {
                int intermediate_result = (t_a[t_a_index] - '0') + 10 - (t_b[i] - '0');
                t_a[t_a_index] = intermediate_result + '0';
                borrow = 1;
            }
            else {
                int intermediate_result = (t_a[t_a_index] - '0')  - (t_b[i] - '0');
                if(t_a[t_a_index] == '9' && borrow) {
                    borrow = 1;
                }
                else {
                    borrow = 0;
                }
                t_a[t_a_index] = intermediate_result + '0';
            }
        }

        while(borrow != 0 && t_a_index >= 0) {
            if(t_a[t_a_index] == '0') {
                t_a[t_a_index--] = '9';
                borrow = 1;
            }
            else {
                t_a[t_a_index--]--;
                borrow = 0;
            }
        }
        
        t_a_index = 0;
        while(t_a[t_a_index] == '0') {
            t_a_index++;
        }

        return t_a.substr(t_a_index, t_a.length() - t_a_index);
    }

    void m_multiply(string &t_container, string t_multiplier) {
        if(t_multiplier == "1") {
            return;
        }

        string intermediate = "";
        string ans = "0";
        int carry = 0;
        for(int i = t_multiplier.size() - 1; i >= 0; i--) {
            intermediate = "";
            for(int j = t_container.size() - 1; j >= 0; j--) {
                int intermediate_result = m_multiply_chars(t_multiplier[i], t_container[j]);
                intermediate_result += carry;
                if(m_size_gt_2(intermediate_result)) {
                    carry = intermediate_result / 10;
                }
                else {
                    carry = 0;
                }
                intermediate =  m_int_to_char(intermediate_result % 10) + intermediate;
            }
            if(carry != 0) {
                intermediate = m_int_to_char(carry) + intermediate;
                carry = 0;
            }
            if(ans != "0") {
                m_add_bigint(ans, intermediate, (t_multiplier.size() - 1) - i);
            }
            else {
                ans = intermediate;
            }
        }

        t_container = ans;
    }

    void m_half_helper(string t_num, string &t_ans, bool t_one_is_carried = false) {
        if(t_num.length() == 0) { 
            int index = 0;
            while(t_ans[index] == 0 && index < t_ans.length()) {
                index++;
            }
            t_ans = t_ans.substr(index, t_ans.length() - index);
            return; 
        }
        if(t_num.length() == 1) {
            int intermediate_result = m_divide_chars(t_num[0], '2');
            t_ans += to_string(intermediate_result);
            return;
        }
        if(t_num[0] == '1') {
            switch(t_num[1] - '0') {
                case 0:
                case 1:
                    t_ans += "05";
                    break;
                case 2:
                case 3:
                    t_ans += "06";
                    break;
                case 4:
                case 5:
                    t_ans += "07";
                    break;
                case 6:
                case 7:
                    t_ans += "08";
                    break;
                case 8:
                case 9:
                    t_ans += "09";
                    break;
            }

            if(t_one_is_carried) {
                t_ans = t_ans.substr(0, t_ans.length() - 2) + t_ans[t_ans.length() - 1];
            }
            if(t_num.length() == 2) {
                int index = 0;
                while(t_ans[index] == 0 && index < t_ans.length()) {
                    index++;
                }
                t_ans = t_ans.substr(index, t_ans.length() - index);
                return;
            }
            else {
                int temp_a = t_num[1] - '0';
                if(temp_a % 2 == 1) {
                    t_num = "1" + t_num.substr(2, t_num.length() - 2);
                    return m_half_helper(t_num, t_ans, true);
                } 
                return m_half_helper(t_num.substr(2, t_num.length() - 2), t_ans);
            }
        }
        int intermediate_result = m_divide_chars(t_num[0], '2');
        t_ans += to_string(intermediate_result);

        int temp_a = t_num[0] - '0';
        if(temp_a % 2 == 1) {
            t_num = '1' + t_num.substr(1, t_num.length() - 1);
            return m_half_helper(t_num, t_ans, true);
        } 
        return 1 >= t_num.length() ? m_half_helper("", t_ans) : m_half_helper(t_num.substr(1, t_num.length() - 1), t_ans);

    }

    string m_half(string t_num) {
        string half = "";
        m_half_helper(t_num, half);
        return half;
    }
    
    void m_push_back(char t_ch) {
        m_container = m_container + t_ch;
    }
public:
    BigInteger(): m_lastDigitPointer(0), m_numLength(0) , m_containerSize(m_INIT_LENGTH){}

    BigInteger(string t_ip): m_container(t_ip){};

    BigInteger(BigInteger &t_bi){}

    string value(){
        return m_container;
    }

    void add(string t_bigint, long long int t_buffer = 0) {
        m_add_bigint(m_container, t_bigint, t_buffer);
    }

    string subtract(string t_a, string t_b) {
        return m_subtract(t_a, t_b);
    }

    string factorial(int t_ip) {
        m_container = to_string(t_ip);
        for(int i = 1; i < t_ip; i++) {
            m_multiply(m_container, to_string(i));
        }

        return m_container;
    }

    string half(string t_num) {
        return m_half(t_num);
    }

    string gcd(string t_a, string t_b) {
        if(t_b.length() == 1 && t_b[0] == '0') {
            return t_a;
        }
        return gcd(t_b, mod(t_a, t_b));
    }

    string mod(string t_a, string t_b) {
        if(m_compare(t_a, t_b) == -1) {
            return t_a;
        }

        string multiplier = "1";
        string temp = t_b;
        while(m_compare(t_a, temp) == 1) {
            temp = t_b;
            m_multiply(multiplier, "2");
            m_multiply(temp, multiplier);
        }
        string left = m_half(multiplier);
        string right = multiplier;

        string temp_left;
        string temp_b;
        string half;

        int comparison_result = -1;
        
        bool equal = false;
        while(m_compare(left, right) < 1) {
            temp_left = left;
            m_add_bigint(temp_left, right);

            half = m_half(temp_left);
            
            temp_b = t_b;
            m_multiply(temp_b, half);
            
            comparison_result = m_compare(t_a, temp_b);
            
            if(comparison_result == 1) {
                string one = "1";
                m_add_bigint(half, one);
                left = half;
            }
            else if(comparison_result == -1) {
                string one = "1";
                right = m_subtract(half, one);
            }
            else {
                equal = true;
                break;
            }
        }

        if(equal) { return "0"; }

        if(half.length() == 0) {
            return left;
        }
        half = m_subtract(half, "1");

        m_multiply(t_b, half);
        return m_subtract(t_a, t_b);
    }

    string exponentiation(string t_num_a, string t_num_b) {
        if(t_num_b == "1") {
            return t_num_a;
        }
        if(t_num_b == "0") {
            return "1";
        }
        if((t_num_b[t_num_b.length() - 1] - '0') % 2 == 1) {
            string power = m_half(m_subtract(t_num_b, "1"));
            string num = exponentiation(t_num_a, power);
            m_multiply(num, num);
            m_multiply(num, t_num_a);
            return num;
        }
        string power = m_half(t_num_b);
        string num = exponentiation(t_num_a, power);
        m_multiply(num, num);
        return num;
    }

};

int main() {

    BigInteger b;

    long long int q;
    cin >> q;

    int query;
    while(q--) {
        cin >> query;
        string num_a, num_b;
        int num;
        switch (query)
        {
        case 1:
            cin >> num_a >> num_b;
            cout << b.exponentiation(num_a, num_b) << endl;
            break;
        case 2:
            cin >> num_a >> num_b;
            cout << b.gcd(num_a, num_b) << endl;
            break;
        case 3:
            cin >> num;
            cout << b.factorial(num);
        default:
            break;
        }
    }
    return 0;
}