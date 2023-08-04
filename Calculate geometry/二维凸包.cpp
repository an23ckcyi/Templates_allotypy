#include <bits/stdc++.h>
using i64 = long long;
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()

using namespace std;

using ld = long double;
// using ld = ll;
const double PI = acos(-1.0);
const double EPS = 1e-4;
inline int dcmp(ld x) {
    return (x > EPS) - (x < -EPS);
}
// inline int dcmp(ld x) { return (x > 0) - (x < 0); }
ld sqr(ld x) {
    return x * x;
}

// Point
using Point = complex<ld>;
ostream& operator<<(ostream& os, const Point& p) {
    os << "[" << p.real() << "," << p.imag() << "]";
    return os;
}
Point ReadPoint() {
    ld x, y;
    cin >> x >> y;
    return Point(x, y);
}
bool operator==(const Point& a, const Point& b) {
    return dcmp(abs(a - b)) == 0;
}
ld operator%(const Point& a, const Point& b) {
    return (conj(a) * b).real();
}
ld operator^(const Point& a, const Point& b) {
    return (conj(a) * b).imag();
}
ld dot(const Point& a, const Point& b, const Point& c) {
    return (b - a) % (c - a);
}
ld cross(const Point& a, const Point& b, const Point& c) {
    return (b - a) ^ (c - a);
}

void solve() {
    int n;
    cin >> n;
    vector<Point> a(n);
    for (auto& x : a) {
        x = ReadPoint();
    }
    sort(all(a), [&](Point& x, Point& y) {
        return x.real() == y.real() ?  x.imag() < y.imag() : x.real() < y.real();
    });
    vector<Point> st;

    st.push_back(a[0]);
    for (int i = 1; i < n; i++) {
        while (sz(st) > 1 && cross(st.back(), st[sz(st) - 2], a[i])  >= 0) {
            st.pop_back();
        }
        st.push_back(a[i]);
    }

    int tmp = sz(st);
    for (int i = n - 2; i >= 0; i--) {
        while (sz(st) > tmp && cross(st.back(), st[sz(st) - 2], a[i]) >= 0) {
            st.pop_back();
        }
        st.push_back(a[i]);
    }

    // 0号点在首尾都出现
    ld res = 0;
    auto dis = [&](Point a, Point b) {
        return sqrtl(dot(a, b, b));
    };
    for (int i = 0; i < sz(st) - 1; i++) {
        res += dis(st[i], st[i + 1]);
    }
    cout << fixed << setprecision(2) << round(res * 100) / 100 << '\n';
}

signed main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int t = 1;
    // cin >> t;
    while (t--)
        solve();
    return 0;
}
