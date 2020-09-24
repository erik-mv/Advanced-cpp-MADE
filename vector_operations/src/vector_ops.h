#pragma once
#include <vector>
#include <iostream>

namespace task {
    using std::vector;
    using std::cin;
    using std::cout;
    using std::ostream;
    using std::istream;
    using std::swap;

    vector<double> operator+ (const vector<double>& a, const vector<double>& b) {
        vector<double> c;

        for (size_t i = 0; i < a.size(); ++i)
            c.push_back(a[i] + b[i]);

        return c;
    }

    vector<double> operator+ (const vector<double>& a) {
        vector<double> c;

        for (size_t i = 0; i < a.size(); ++i)
            c.push_back(+a[i]);

        return c;
    }

    vector<double> operator- (const vector<double>& a, const vector<double>& b) {
        vector<double> c;

        for (size_t i = 0; i < a.size(); ++i)
            c.push_back(a[i] - b[i]);

        return c;
    }

    vector<double> operator- (const vector<double>& a) {
        vector<double> c;

        for (size_t i = 0; i < a.size(); ++i)
            c.push_back(-a[i]);

        return c;
    }

    double operator* (const vector<double>& a, const vector<double>& b) {
        double sum = 0;

        for (size_t i = 0; i < a.size(); ++i)
            sum += a[i] * b[i];

        return sum;
    }

    vector<double> operator% (const vector<double>& a, const vector<double>& b) {
        vector<double> c;

        c.push_back(a[1] * b[2] - a[2] * b[1]);
        c.push_back(a[2] * b[0] - a[0] * b[2]);
        c.push_back(a[0] * b[1] - a[1] * b[0]);

        return c;
    }

    bool operator|| (const vector<double>& a, const vector<double>& b) {
        const double eps = 1e-12;
        double flag = a[0] / b[0];

        for (size_t i = 1; i < a.size(); ++i) {
            double temp = flag - a[i] / b[i];

            if (temp > eps || -temp > eps)
                return 0;
        }

        return 1;
    }

    bool operator&& (const vector<double>& a, const vector<double>& b) {
        const double eps = 1e-12;
        double flag = a[0] / b[0];

        if (flag < 0 && b[0])
            return 0;

        for (size_t i = 1; i < a.size(); ++i) {
            double temp = flag - a[i] / b[i];

            if (temp > eps || -temp > eps)
                return 0;
        }

        return 1;
    }


    vector<double> reverse(vector<double>& a) {
        int n = a.size();

        for (size_t i = 0; i < n / 2; ++i)
            swap(a[i], a[n - 1 - i]);

        return a;
    }

    istream& operator>> (istream& strm, vector<double>& b) {
        b.clear();
        size_t n;
        strm >> n;

        for (size_t i = 0; i < n; ++i) {
            double x;
            strm >> x;

            b.push_back(x);
        }

        return strm;
    }

    ostream& operator<<(ostream& strm, const vector<double>& a) {
        strm << a[0];

        for (size_t i = 1; i < a.size(); ++i)
            strm << " " << a[i];

        strm << "\n";

        return strm;
    }

    istream& operator>> (istream& strm, vector<int>& b) {
        b.clear();
        size_t n;
        strm >> n;

        for (size_t i = 0; i < n; ++i) {
            int x;
            strm >> x;

            b.push_back(x);
        }

        return strm;
    }

    ostream& operator<<(ostream& strm, const vector<int>& a) {
        strm << a[0];

        for (size_t i = 1; i < a.size(); ++i)
            strm << " " << a[i];

        strm << "\n";

        return strm;
    }

    vector<int> operator| (const vector<int>& a, const vector<int>& b) {
        vector<int> c;

        for (size_t i = 0; i < a.size(); ++i)
            c.push_back(a[i] | b[i]);

        return c;
    }

    vector<int> operator& (const vector<int>& a, const vector<int>& b) {
        vector<int> c;

        for (size_t i = 0; i < a.size(); ++i)
            c.push_back(a[i] & b[i]);

        return c;
    }
}  // namespace task
