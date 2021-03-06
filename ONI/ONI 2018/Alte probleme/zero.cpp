#include <bits/stdc++.h>

using namespace std;

class Int{
    private:
        std::vector<int> v;

        int max(int x, int y)
        {
            return x > y ? x : y;
        }

        int& operator[] (int indx)
        {
            return v[indx];
        }

        void clear()
        {
            v.clear();
        }

        void push_back(int x)
        {
            v.push_back(x);
        }

        void pop_back()
        {
            v.pop_back();
        }

        void resize(int x, int y = 0)
        {
            v.resize(x, y);
        }

        int back()
        {
            return v.back();
        }

        std::vector<int>::iterator begin()
        {
            return v.begin();
        }

        std::vector<int>::iterator end()
        {
            return v.end();
        }

        void sum(Int &dest, Int x, Int y)
        {
            dest.clear();
            reverse(x.begin(), x.end());
            reverse(y.begin(), y.end());
            int mn = max(x.size(), y.size()), t=0;
            for (int i = 0; i < mn; ++i){
                int X = 0, Y = 0;
                if(x.size() > i)
                    X = x[i];
                if(y.size() > i)
                    Y = y[i];
                dest.push_back(X+Y+t);
                t = dest[i]/10;
                dest[i] %= 10;
            }
            if(t)
                dest.push_back(t);
            reverse(dest.begin(), dest.end());
        }

        void sub(Int &c, Int x, Int y)
        {
            if(x < y)
                throw 1;
            c.clear();
            reverse(x.begin(), x.end());
            reverse(y.begin(), y.end());
            int mn = max(x.size(), y.size()), t=0;
            for (int i = 0; i < mn; ++i){
                int X = 0, Y = 0;
                if(x.size() > i)
                    X = x[i];
                if(y.size() > i)
                    Y = y[i];
                c.push_back(X-Y-t);
                if(c[i] < 0){
                    t = 1;
                    c[i] += 10;
                }else
                    t = 0;
            }
            while(c.size() > 1 && c.back() == 0)
                c.pop_back();
            reverse(c.begin(), c.end());
        }

        void prod(Int &c, Int a, Int b)
        {
            c.clear();
            reverse(a.begin(), a.end());
            reverse(b.begin(), b.end());
            c.resize(a.size() + b.size()-1, 0);
            for (int i = 0; i < a.size(); ++i)
                for (int j = 0; j < b.size(); ++j)
                    c[i+j] += a[i] * b[j];
            int t = 0;
            for (int i = 0; i <= a.size() + b.size()-2; ++i){
                c[i] += t;
                t = c[i]/10;
                c[i] %= 10;
            }
            if(t)
                c.push_back(t);
            reverse(c.begin(), c.end());
        }

        void div(Int &c, Int a, Int b)
        {
            c.clear();
            if(a < b){
                c = 0;
                return;
            }
            if(b == 0)
                throw 2;
            Int remainder = a, res = 0;
            while(remainder >= b){
                Int sz = remainder.size()-b.size()-1, p = 1;
                if(b*pow(10, sz+1) <= remainder)
                    sz = sz+1;
                Int dv = b*pow(10, sz);
                Int dv2 = dv;
                for (int i = 2; i <= 9; ++i)
                    if(remainder-dv2 >= dv)
                        dv2 = dv2 + dv,
                        p = p+1;
                    else break;
                remainder = remainder - dv2;
                res = res + pow(10, sz) * p;
            }
            c = res;
        }

        void mod(Int &c, Int a, Int b)
        {
            c.clear();
            if(a < b){
                c = 0;
                return;
            }
            if(b == 0)
                throw 2;
            Int remainder = a, res = 0;
            while(remainder >= b){
                Int sz = remainder.size()-b.size()-1, p = 1;
                if(b*pow(10, sz+1) <= remainder)
                    sz = sz+1;
                Int dv = b*pow(10, sz);
                Int dv2 = dv;
                for (int i = 2; i <= 9; ++i)
                    if(remainder-dv2 >= dv)
                        dv2 = dv2 + dv,
                        p = p+1;
                    else break;
                remainder = remainder - dv2;
                res = res + pow(10, sz) * p;
            }
            c = remainder;
        }

        friend std::ostream &operator<<(std::ostream &os, Int a)
        {
            std::string c;
            for (int i = 0; i < a.size(); ++i)
                c.push_back(a[i]+'0');
            return os << c;
        }

        friend std::istream &operator>>(std::istream &is, Int &a)
        {
            a.clear();
            std::string s;
            is >> s;
            for (std::string::iterator it = s.begin(); it != s.end(); ++it)
                if(*it >= '0' && *it <= '9')
                    a.push_back(*it-'0');
            return is;
        }
    public:

        Int()
        {
            v.push_back(0);
        }

        Int(int x)
        {
            if(x < 0)
                x = -x;
            else if(x == 0)
                v.push_back(0);
            else
                while(x){
                    v.push_back(x%10);
                    x/=10;
                }
            reverse(v.begin(), v.end());
        }

        Int(const char *q){
            int n = strlen(q);
            for (int i = 0; i < n; ++i)
                v.push_back(q[i]-'0');
        }

        ~Int()
        {
            v.clear();
        }

        int size()
        {
            return v.size();
        }

        static Int pow(Int a, Int b)
        {
            Int p = 1;
            while(b > 0)
                if(b.back()%2 == 0)
                    a = a*a,
                    b = b/2;
                else
                    p = p*a,
                    b = b-1;
            return p;
        }

        Int operator+(const Int b)
        {
            Int res;
            sum(res, *this, b);
            return res;
        }

        Int operator-(const Int b)
        {
            try{
                Int res;
                sub(res, *this, b);
                return res;
            }catch(int x){
                if(x == 1)
                    std::cout << "Int is not a signed class\n";
            }
            return 0;
        }

        Int operator*(const Int b)
        {
            Int res;
            prod(res, *this, b);
            return res;
        }

        Int operator/(const Int b)
        {
            try{
                Int res;
                div(res, *this, b);
                return res;
            }catch(int x){
                if(x == 2)
                    std::cout << "division by 0 is not permitted";
            }
            return 0;
        }

        Int operator%(const Int b)
        {
            try{
                Int res;
                mod(res, *this, b);
                return res;
            }catch(int x){
                if(x == 2)
                    std::cout << "division by 0 is not permitted";
            }
            return 0;
        }

        bool operator>(Int b)
        {
            if(this->size() > b.size())
                return true;
            if(this->size() < b.size())
                return false;
            for (int i = 0; i < b.size(); ++i)
                if((*this)[i] > b[i])
                    return true;
                else if((*this)[i] < b[i])
                    return false;
            return false;
        }

        bool operator<(Int b)
        {
            if(this->size() > b.size())
                return false;
            if(this->size() < b.size())
                return true;
            for (int i = 0; i < b.size(); ++i)
                if((*this)[i] > b[i])
                    return false;
                else if((*this)[i] < b[i])
                    return true;
                return false;
        }

        bool operator>=(Int b){
            if(this->size() > b.size())
                return true;
            if(this->size() < b.size())
                return false;
            for (int i = 0; i < b.size(); ++i)
                if((*this)[i] > b[i])
                    return true;
                else if((*this)[i] < b[i])
                    return false;
            return true;
        }

        bool operator<=(Int b)
        {
            if(this->size() > b.size())
                return false;
            if(this->size() < b.size())
                return true;
            for (int i = 0; i < b.size(); ++i)
                if((*this)[i] > b[i])
                    return false;
                else if((*this)[i] < b[i])
                    return true;
            return true;
        }

        bool operator==(Int b)
        {
            if(this->size() != b.size())
                return false;
            for (int i = 0; i < b.size(); ++i)
                if((*this)[i] != b[i])
                    return false;
            return true;
        }

        bool operator!=(Int b)
        {
            if(this->size() != b.size())
                return true;
            for (int i = 0; i < b.size(); ++i)
                if((*this)[i] != b[i])
                    return true;
            return false;
        }

        bool operator>(const int &c)
        {
            Int b = c;
            if(this->size() > b.size())
                return true;
            if(this->size() < b.size())
                return false;
            for (int i = 0; i < b.size(); ++i)
                if((*this)[i] > b[i])
                    return true;
                else if((*this)[i] < b[i])
                    return false;
            return false;
        }

        bool operator<(const int &c)
        {
            Int b = c;
            if(this->size() > b.size())
                return false;
            if(this->size() < b.size())
                return true;
            for (int i = 0; i < b.size(); ++i)
                if((*this)[i] > b[i])
                    return false;
                else if((*this)[i] < b[i])
                    return true;
                return false;
        }

        bool operator>=(const int &c)
        {
            Int b = c;
            if(this->size() > b.size())
                return true;
            if(this->size() < b.size())
                return false;
            for (int i = 0; i < b.size(); ++i)
                if((*this)[i] > b[i])
                    return true;
                else if((*this)[i] < b[i])
                    return false;
            return true;
        }

        bool operator<=(const int &c)
        {
            Int b = c;
            if(this->size() > b.size())
                return false;
            if(this->size() < b.size())
                return true;
            for (int i = 0; i < b.size(); ++i)
                if((*this)[i] > b[i])
                    return false;
                else if((*this)[i] < b[i])
                    return true;
            return true;
        }

        bool operator==(const int &c)
        {
            Int b = c;
            if(this->size() != b.size())
                return false;
            for (int i = 0; i < b.size(); ++i)
                if((*this)[i] != b[i])
                    return false;
            return true;
        }

        bool operator!=(const int &c)
        {
            Int b = c;
            if(this->size() != b.size())
                return true;
            for (int i = 0; i < b.size(); ++i)
                if((*this)[i] != b[i])
                    return true;
            return false;
        }

        Int operator+(const int c)
        {
            Int b = c;
            Int res;
            sum(res, *this, b);
            return res;
        }

        Int operator-(const int c)
        {
            try{
                Int b = c;
                Int res;
                sub(res, *this, b);
                return res;
            }catch(int x){
                if(x == 1)
                    std::cout << "Int is not a signed class\n";
            }
            return 0;
        }

        Int operator*(const int c)
        {
            Int b = c;
            Int res;
            prod(res, *this, b);
            return res;
        }

        Int operator/(const int c)
        {
            try{
                Int b = c;
                Int res;
                div(res, *this, b);
                return res;
            }catch(int x){
                if(x == 2)
                    std::cout << "division by 0 is not permitted";
            }
            return 0;
        }

        Int operator%(const int c)
        {
            try{
                Int b = c;
                Int res;
                mod(res, *this, b);
                return res;
            }catch(int x){
                if(x == 2)
                    std::cout << "division by 0 is not permitted";
            }
            return 0;
        }

        operator bool()
        {
            if(*this != 0)
                return true;
            return false;
        }

        operator int()
        {
            int aux = 0;
            for (int i = 0; i < this->size(); ++i)
                aux = aux*10 + (*this)[i];
            return aux;
        }
};

int l, b, p, q;
Int pd[50][50], pd2[50][50];

int main()
{
    ifstream fin ("zero.in");
    ofstream fout ("zero.out");
    fin >> l >> b >> p >> q;
    pd[1][0] = b-1;
    for (int i = 2; i <= l; ++i){
        for (int k = 0; k <= min(i-1, p); ++k)
            pd[i][0] = pd[i][0] + pd[i-1][k]*(b-1);
        for (int j = 1; j <= min(i, p); ++j)
            pd[i][j] = pd[i-j][0];
    }
    pd2[1][0] = b-1;
    --q;
    for (int i = 2; i <= l; ++i){
        for (int k = 0; k <= min(i-1, q); ++k)
            pd2[i][0] = pd2[i][0] + pd2[i-1][k]*(b-1);
        for (int j = 1; j <= min(i, q); ++j)
            pd2[i][j] = pd2[i-j][0];
    }
    Int sol = 0, sol2;
    sol2 = sol2.pow(b, l-1);
    sol2 = sol2*(b-1);
    for (int i = 0; i <= p; ++i)
        sol = sol + pd[l][i];
    for (int i = 0; i <= q; ++i)
        sol2 = sol2 - pd2[l][i];
    fout << sol << "\n" << sol2 << "\n";
    return 0;
}

