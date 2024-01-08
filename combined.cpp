#ifndef LOCAL
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#endif

#include <bits/stdc++.h>
namespace mitsuha {
    template <class T> bool chmin(T& x, const T& y) { return y >= x ? false : (x = y, true); }
    template <class T> bool chmax(T& x, const T& y) { return y <= x ? false : (x = y, true); }
    template <class T> constexpr int pow_m1(T n) { return -(n & 1) | 1; }
    template <class T> constexpr T floor(const T x, const T y) { T q = x / y, r = x % y; return q - ((x ^ y) < 0 and (r != 0)); }
    template <class T> constexpr T ceil(const T x, const T y) { T q = x / y, r = x % y; return q + ((x ^ y) > 0 and (r != 0)); }
}

namespace mitsuha::macro {
#define IMPL_REPITER(cond) auto& begin() { return *this; } auto end() { return nullptr; } auto& operator*() { return _val; } auto& operator++() { return _val += _step, *this; } bool operator!=(std::nullptr_t) { return cond; }
    template <class Int, class IntL = Int, class IntStep = Int, std::enable_if_t<(std::is_signed_v<Int> == std::is_signed_v<IntL>), std::nullptr_t> = nullptr> struct rep_impl {
        Int _val; const Int _end, _step;
        rep_impl(Int n) : rep_impl(0, n) {}
        rep_impl(IntL l, Int r, IntStep step = 1) : _val(l), _end(r), _step(step) {}
        IMPL_REPITER((_val < _end))
    };
    template <class Int, class IntL = Int, class IntStep = Int, std::enable_if_t<(std::is_signed_v<Int> == std::is_signed_v<IntL>), std::nullptr_t> = nullptr> struct rrep_impl {
        Int _val; const Int _end, _step;
        rrep_impl(Int n) : rrep_impl(0, n) {}
        rrep_impl(IntL l, Int r) : _val(r - 1), _end(l), _step(-1) {}
        rrep_impl(IntL l, Int r, IntStep step) : _val(l + floor<Int>(r - l - 1, step) * step), _end(l), _step(-step) {}
        IMPL_REPITER((_val >= _end))
    };
#undef IMPL_REPITER
}

namespace mitsuha::io {
    template <typename T>
    struct is_container {
        template <typename T2>
        static auto test(T2 t) -> decltype(++t.begin() != t.end(), *t.begin(), std::true_type{});
        static std::false_type test(...);
    public:
        static constexpr bool value = decltype(test(std::declval<T>()))::value;
    };
    template <typename T>
    constexpr bool is_container_v = is_container<T>::value;

    template <typename T>
    using is_integral = std::disjunction<std::is_integral<T>, std::is_same<T, __int128_t>, std::is_same<T, __uint128_t>>;
    template <typename T>
    constexpr bool is_integral_v = is_integral<T>::value;

    void read(char &c) { do c = getchar(); while (not isgraph(c)); }
    template <typename T, std::enable_if_t<is_integral_v<T>, std::nullptr_t> = nullptr>
    void read(T& x) {
        char c;
        do c = getchar(); while (not isgraph(c));
        if (c == '-') {
            read<T>(x), x = -x;
            return;
        }
        if (not (isdigit(c))) throw - 1;
        x = 0;
        do x = x * 10 + (std::exchange(c, getchar()) - '0'); while (isdigit(c));
    }
    void read(std::string& x) {
        x.clear();
        char c;
        do c = getchar(); while (not isgraph(c));
        do x += std::exchange(c, getchar()); while (isgraph(c));
    }
    template <typename T, typename U>
    void read(std::pair<T, U>& a) { read(a.first), read(a.second); }
    template <size_t N = 0, typename ...Args>
    void read(std::tuple<Args...>& a) { if constexpr (N < sizeof...(Args)) read(std::get<N>(a)), read<N + 1>(a); }
    template <typename T, std::enable_if_t<is_container_v<T>, std::nullptr_t> = nullptr>
    void read(T& x) { for (auto &e : x) read(e); }

    void write(char c) { putchar(c); }
    template <typename T, std::enable_if_t<is_integral_v<T>, std::nullptr_t> = nullptr>
    void write(T x) {
        static char buf[50];
        if constexpr (std::is_signed_v<T>) if (x < 0) putchar('-'), x = -x;
        int i = 0;
        do buf[i++] = '0' + (x % 10), x /= 10; while (x);
        while (i--) putchar(buf[i]);
    }
    void write(const std::string& x) { for (char c : x) putchar(c); }
    template <typename T, typename U>
    void write(const std::pair<T, U>& a) { write(a.first), write(' '), write(a.second); }
    template <size_t N = 0, typename ...Args>
    void write(const std::tuple<Args...>& a) {
        if constexpr (N < std::tuple_size_v<std::tuple<Args...>>) {
            if constexpr (N) write(' ');
            write(std::get<N>(a)), write<N + 1>(a);
        }
    }
    template <typename T, std::enable_if_t<is_container_v<T>, std::nullptr_t> = nullptr>
    void write(const T& x) {
        bool insert_delim = false;
        for (auto it = x.begin(); it != x.end(); ++it) {
            if (std::exchange(insert_delim, true)) write(' ');
            write(*it);
        }
    }

    template <typename ...Args>
    void read(Args &...args) { (read(args), ...); }
    template <typename Head, typename ...Tails>
    void print(Head&& head, Tails &&...tails) { write(head), ((write(' '), write(tails)), ...), write('\n'); }
}
namespace mitsuha{ using io::print; using io::read; using io::write; }

namespace mitsuha {
    template <class T, class ToKey, class CompKey = std::less<>, std::enable_if_t<std::conjunction_v<std::is_invocable<ToKey, T>, std::is_invocable_r<bool, CompKey, std::invoke_result_t<ToKey, T>, std::invoke_result_t<ToKey, T>>>, std::nullptr_t> = nullptr>
    auto lambda(const ToKey& to_key, const CompKey& comp_key = std::less<>()) {
        return [=](const T& x, const T& y) { return comp_key(to_key(x), to_key(y)); };
    }
    template <class Compare, std::enable_if_t<std::is_invocable_r_v<bool, Compare, int, int>, std::nullptr_t> = nullptr>
    std::vector<int> sorted_indices(int n, const Compare& compare) {
        std::vector<int> p(n);
        return std::iota(p.begin(), p.end(), 0), std::sort(p.begin(), p.end(), compare), p;
    }
    template <class ToKey, std::enable_if_t<std::is_invocable_v<ToKey, int>, std::nullptr_t> = nullptr>
    std::vector<int> sorted_indices(int n, const ToKey& to_key) { return sorted_indices(n, lambda<int>(to_key)); }

    template <typename T, typename Gen>
    auto generate_vector(int n, Gen generator) { std::vector<T> v(n); for (int i = 0; i < n; ++i) v[i] = generator(i); return v; }
    template <typename T> auto generate_range(T l, T r) { return generate_vector<T>(r - l, [l](int i) { return l + i; }); }
    template <typename T> auto generate_range(T n) { return generate_range(0, n); }

    template <class Iterable>
    void settify(Iterable& a) { std::sort(a.begin(), a.end()), a.erase(std::unique(a.begin(), a.end()), a.end()); }

    template <size_t D> struct Dim : std::array<int, D> {
        template <typename ...Ints> Dim(const Ints& ...ns) : std::array<int, D>::array{ static_cast<int>(ns)... } {}
    };
    template <typename ...Ints> Dim(const Ints& ...) -> Dim<sizeof...(Ints)>;
    template <class T, size_t D, size_t I = 0>
    auto ndvec(const Dim<D> &ns, const T& value = {}) {
        if constexpr (I + 1 < D) {
            return std::vector(ns[I], ndvec<T, D, I + 1>(ns, value));
        } else {
            return std::vector<T>(ns[I], value);
        }
    }
} // namescape mitsuha

namespace mitsuha {
    using str = std::string;
    using int128 = __int128_t;
    using uint128 = __uint128_t;
    template <class T> using min_priority_queue = std::priority_queue<T, std::vector<T>, std::greater<T>>;
    template <class T> using max_priority_queue = std::priority_queue<T, std::vector<T>, std::less<T>>;
}
namespace mitsuha { const std::string Yes = "Yes", No = "No", YES = "YES", NO = "NO"; }

#define Int(...) int __VA_ARGS__; read(__VA_ARGS__)
#define Ll(...) long long __VA_ARGS__; read(__VA_ARGS__)
#define Dbl(...) double __VA_ARGS__; read(__VA_ARGS__)
#define Chr(...) char __VA_ARGS__; read(__VA_ARGS__)
#define Str(...) string __VA_ARGS__; read(__VA_ARGS__)
#define Vt(type, name, size) vector<type> name(size); read(name)
#define Vvt(type, name, h, w) vector<vector<type>> name(h, vector<type>(w)); read(name)
#define die(...)  do { print(__VA_ARGS__); return; } while (false)
#define kill(...) do { print(__VA_ARGS__); return 0; } while (false)

#define Each(e, v) for (auto &&e : v)
#define CFor(e, v) for (const auto &e : v)
#define For(i, ...) CFor(i, mitsuha::macro::rep_impl(__VA_ARGS__))
#define Frr(i, ...) CFor(i, mitsuha::macro::rrep_impl(__VA_ARGS__))
#define Loop(n) for ([[maybe_unused]] const auto& _ : mitsuha::macro::rep_impl(n))

#define All(iterable) std::begin(iterable), std::end(iterable)
#define len(iterable) (long long) iterable.size()
#define elif else if
 
using namespace mitsuha;
using namespace std;

struct io_setup {
    io_setup(int precision = 15) {
#if defined(LOCAL) and not defined(STRESS)
        freopen("input.txt",  "r", stdin);
        freopen("output.txt", "w", stdout);
        freopen("error.txt", "w", stderr);
#endif
#if not defined(LOCAL) and not defined(STRESS)
        std::cin.tie(0)->sync_with_stdio(0);
        std::cin.exceptions(std::ios::badbit | std::ios::failbit);
#endif
        std::cout << std::fixed << std::setprecision(precision);
    }
} io_setup_{};

#ifdef LOCAL
#include "library/debug/pprint.hpp"
#else
#  define debug(...) void(0)
#endif
 
constexpr int iinf = std::numeric_limits<int>::max() / 2;
constexpr long long linf = std::numeric_limits<long long>::max() / 2;

namespace mitsuha{
struct has_mod_impl {
    template <class T>
    static auto check(T &&x) -> decltype(x.get_mod(), std::true_type{});
    template <class T>
    static auto check(...) -> std::false_type;
};

template <class T>
class has_mod : public decltype(has_mod_impl::check<T>(std::declval<T>())) {};

template <typename mint>
mint inv(int n) {
    static const int mod = mint::get_mod();
    static vector<mint> dat = {0, 1};
    assert(0 <= n);
    if (n >= mod) n %= mod;
    while (len(dat) <= n) {
        int k = len(dat);
        int q = (mod + k - 1) / k;
        dat.emplace_back(dat[k * q - mod] * mint::raw(q));
    }
    return dat[n];
}

template <typename mint>
mint fact(int n) {
    static const int mod = mint::get_mod();
    assert(0 <= n && n < mod);
    static vector<mint> dat = {1, 1};
    while (len(dat) <= n) dat.emplace_back(dat[len(dat) - 1] * mint::raw(len(dat)));
    return dat[n];
}

template <typename mint>
mint fact_inv(int n) {
    static vector<mint> dat = {1, 1};
    if (n < 0) return mint(0);
    while (len(dat) <= n) dat.emplace_back(dat[len(dat) - 1] * inv<mint>(len(dat)));
    return dat[n];
}

template <class mint, class... Ts>
mint fact_invs(Ts... xs) {
    return (mint(1) * ... * fact_inv<mint>(xs));
}

template <typename mint, class Head, class... Tail>
mint multinomial(Head &&head, Tail &&... tail) {
    return fact<mint>(head) * fact_invs<mint>(std::forward<Tail>(tail)...);
}

template <typename mint>
mint C_dense(int n, int k) {
    static vector<vector<mint>> C;
    static int H = 0, W = 0;
    auto calc = [&](int i, int j) -> mint {
        if (i == 0) return (j == 0 ? mint(1) : mint(0));
        return C[i - 1][j] + (j ? C[i - 1][j - 1] : 0);
    };
    if (W <= k) {
        for(int i = 0; i < H; ++i) {
            C[i].resize(k + 1);
            for(int j = W; j < k + 1; ++j) { C[i][j] = calc(i, j); }
        }
        W = k + 1;
    }
    if (H <= n) {
        C.resize(n + 1);
        for(int i = H; i < n + 1; ++i) {
            C[i].resize(W);
            for(int j = 0; j < W; ++j) { C[i][j] = calc(i, j); }
        }
        H = n + 1;
    }
    return C[n][k];
}

template <typename mint, bool large = false, bool dense = false>
mint C(long long n, long long k) {
    assert(n >= 0);
    if (k < 0 || n < k) return 0;
    if constexpr (dense) return C_dense<mint>(n, k);
    if constexpr (!large) return multinomial<mint>(n, k, n - k);
    k = min(k, n - k);
    mint x(1);
    for(int i = 0; i < k; ++i) x *= mint(n - i);
    return x * fact_inv<mint>(k);
}

template <typename mint, bool large = false>
mint C_inv(long long n, long long k) {
    assert(n >= 0);
    assert(0 <= k && k <= n);
    if (not large) return fact_inv<mint>(n) * fact<mint>(k) * fact<mint>(n - k);
    return mint(1) / C<mint, true>(n, k);
}

// [x^d](1-x)^{-n}
template <typename mint, bool large = false, bool dense = false>
mint C_negative(long long n, long long d) {
    assert(n >= 0);
    if (d < 0) return mint(0);
    if (n == 0) { return (d == 0 ? mint(1) : mint(0)); }
    return C<mint, large, dense>(n + d - 1, d);
}
} // namespace mitsuha

namespace mitsuha{
template <int mod>
struct modint {
    static constexpr unsigned int umod = (unsigned int)(mod);
    static_assert(umod < 1U << 31);
    unsigned int val;

    static modint raw(unsigned int v) {
        modint x;
        x.val = v;
        return x;
    }
    constexpr modint() : val(0) {}
    constexpr modint(unsigned int x) : val(x % umod) {}
    constexpr modint(unsigned long long x) : val(x % umod) {}
    constexpr modint(unsigned __int128 x) : val(x % umod) {}
    constexpr modint(int x) : val((x %= mod) < 0 ? x + mod : x){};
    constexpr modint(long long x) : val((x %= mod) < 0 ? x + mod : x){};
    constexpr modint(__int128 x) : val((x %= mod) < 0 ? x + mod : x){};
    bool operator<(const modint &other) const { return val < other.val; }
    modint &operator+=(const modint &p) {
        if ((val += p.val) >= umod) val -= umod;
        return *this;
    }
    modint &operator-=(const modint &p) {
        if ((val += umod - p.val) >= umod) val -= umod;
        return *this;
    }
    modint &operator*=(const modint &p) {
        val = (unsigned long long)(val) * p.val % umod;
        return *this;
    }
    modint &operator/=(const modint &p) {
        *this *= p.inverse();
        return *this;
    }
    modint operator-() const { return modint::raw(val ? mod - val : 0U); }
    modint operator+(const modint &p) const { return modint(*this) += p; }
    modint operator-(const modint &p) const { return modint(*this) -= p; }
    modint operator*(const modint &p) const { return modint(*this) *= p; }
    modint operator/(const modint &p) const { return modint(*this) /= p; }
    bool operator==(const modint &p) const { return val == p.val; }
    bool operator!=(const modint &p) const { return val != p.val; }
    modint inverse() const {
        int a = val, b = mod, u = 1, v = 0, t;
        while (b > 0) {
            t = a / b;
            swap(a -= t * b, b), swap(u -= t * v, v);
        }
        return modint(u);
    }
    modint pow(long long n) const {
        assert(n >= 0);
        modint ret(1), mul(val);
        while (n > 0) {
            if (n & 1) ret *= mul;
            mul *= mul;
            n >>= 1;
        }
        return ret;
    }
    static constexpr int get_mod() { return mod; }
   // (n, r), r is the 2^nth root of 1
    static constexpr pair<int, int> ntt_info() {
        if (mod == 120586241) return {20, 74066978};
        if (mod == 167772161) return {25, 17};
        if (mod == 469762049) return {26, 30};
        if (mod == 754974721) return {24, 362};
        if (mod == 880803841) return {23, 211};
        if (mod == 943718401) return {22, 663003469};
        if (mod == 998244353) return {23, 31};
        if (mod == 1045430273) return {20, 363};
        if (mod == 1051721729) return {20, 330};
        if (mod == 1053818881) return {20, 2789};
        return {-1, -1};
    }
    static constexpr bool can_ntt() { return ntt_info().first != -1; }

    template<int _mod> 
    friend void read(modint<_mod> &number){
        io::read(number.val);
        number.val %= _mod;
    }
    template<int _mod>
    friend void write(const modint<_mod> &number){
        io::write(number.val);
    }
};

using modint107 = modint<1000000007>;
using modint998 = modint<998244353>;
} // namespace mitsuha

namespace mitsuha{
// Long is okay
// Make sure (val * x - 1) is a multiple of mod
// Especially if mod=0, x=0 satisfies
long long mod_inv(long long val, long long mod) {
    if (mod == 0) return 0;
    mod = abs(mod);
    val %= mod;
    if (val < 0) val += mod;
    long long a = val, b = mod, u = 1, v = 0, t;
    while (b > 0) {
        t = a / b;
        swap(a -= t * b, b), swap(u -= t * v, v);
    }
    if (u < 0) u += mod;
    return u;
}
} // namespace mitsuha

namespace mitsuha{
constexpr unsigned int mod_pow_constexpr(unsigned long long a, unsigned long long n, unsigned long long mod) {
    a %= mod;
    unsigned long long res = 1;
    for (int _ = 0; _ < 32; ++_) {
        if (n & 1) res = res * a % mod;
        a = a * a % mod, n /= 2;
    }
    return res;
}

template <typename T, unsigned int p0, unsigned int p1, unsigned int p2>
T CRT3(unsigned long long a0, unsigned long long a1, unsigned long long a2) {
    static_assert(p0 < p1 && p1 < p2);
    static constexpr unsigned long long x0_1 = mod_pow_constexpr(p0, p1 - 2, p1);
    static constexpr unsigned long long x01_2 = mod_pow_constexpr((unsigned long long)(p0) * p1 % p2, p2 - 2, p2);
    unsigned long long c = (a1 - a0 + p1) * x0_1 % p1;
    unsigned long long a = a0 + c * p0;
    c = (a2 - a % p2 + p2) * x01_2 % p2;
    return T(a) + T(c) * T(p0) * T(p1);
}
} // namespace mitsuha

namespace mitsuha{
template <class T, typename enable_if<!has_mod<T>::value>::type* = nullptr>
vector<T> convolution_naive(const vector<T>& a, const vector<T>& b) {
    int n = int(a.size()), m = int(b.size());
    if (n > m) return convolution_naive<T>(b, a);
    if (n == 0) return {};
    vector<T> ans(n + m - 1);
    For(i, n) For(j, m) ans[i + j] += a[i] * b[j];
    return ans;
}

template <class T, typename enable_if<has_mod<T>::value>::type* = nullptr>
vector<T> convolution_naive(const vector<T>& a, const vector<T>& b) {
    int n = int(a.size()), m = int(b.size());
    if (n > m) return convolution_naive<T>(b, a);
    if (n == 0) return {};
    vector<T> ans(n + m - 1);
    if (n <= 16 && (T::get_mod() < (1 << 30))) {
        for (int k = 0; k < n + m - 1; ++k) {
            int s = max(0, k - m + 1);
            int t = min(n, k + 1);
            unsigned long long sm = 0;
            for (int i = s; i < t; ++i) { sm += (unsigned long long)(a[i].val) * (b[k - i].val); }
            ans[k] = sm;
        }
    } else {
        for (int k = 0; k < n + m - 1; ++k) {
            int s = max(0, k - m + 1);
            int t = min(n, k + 1);
            unsigned __int128 sm = 0;
            for (int i = s; i < t; ++i) { sm += (unsigned long long)(a[i].val) * (b[k - i].val); }
            ans[k] = T::raw(sm % T::get_mod());
        }
    }
    return ans;
}
} // namespace mitsuha

namespace mitsuha{
// Can be done with any ring
template <typename T>
vector<T> convolution_karatsuba(const vector<T>& f, const vector<T>& g) {
    const int thresh = 30;
    if (min(len(f), len(g)) <= thresh) return convolution_naive(f, g);
    int n = max(len(f), len(g));
    int m = (n + 1) / 2;
    vector<T> f1, f2, g1, g2;
    if (len(f) < m) f1 = f;
    if (len(f) >= m) f1 = {f.begin(), f.begin() + m};
    if (len(f) >= m) f2 = {f.begin() + m, f.end()};
    if (len(g) < m) g1 = g;
    if (len(g) >= m) g1 = {g.begin(), g.begin() + m};
    if (len(g) >= m) g2 = {g.begin() + m, g.end()};
    vector<T> a = convolution_karatsuba(f1, g1);
    vector<T> b = convolution_karatsuba(f2, g2);
    for(int i = 0; i < (int) f2.size(); i++) f1[i] += f2[i];
    for(int i = 0; i < (int) g2.size(); i++) g1[i] += g2[i];
    vector<T> c = convolution_karatsuba(f1, g1);
    vector<T> F((int) f.size() + (int) g.size() - 1);
    assert(2 * m + len(b) <= len(F));
    for(int i = 0; i < (int) a.size(); i++) F[i] += a[i], c[i] -= a[i];
    for(int i = 0; i < (int) b.size(); i++) F[2 * m + i] += b[i], c[i] -= b[i];
    if (c.back() == T(0)) c.pop_back();
    for(int i = 0; i < (int) c.size(); i++) if (c[i] != T(0)) F[m + i] += c[i];
    return F;
}
} // namespace mitsuha

namespace mitsuha{
template <class mint>
void ntt(vector<mint>& a, bool inverse) {
    assert(mint::can_ntt());
    const int rank2 = mint::ntt_info().fi;
    const int mod = mint::get_mod();
    static array<mint, 30> root, iroot;
    static array<mint, 30> rate2, irate2;
    static array<mint, 30> rate3, irate3;

    assert(rank2 != -1 && len(a) <= (1 << max(0, rank2)));

    static bool prepared = 0;
    if (!prepared) {
        prepared = 1;
        root[rank2] = mint::ntt_info().se;
        iroot[rank2] = mint(1) / root[rank2];
        for(int i = rank2 - 1; i >= 0; --i) {
            root[i] = root[i + 1] * root[i + 1];
            iroot[i] = iroot[i + 1] * iroot[i + 1];
        }
        mint prod = 1, iprod = 1;
        for (int i = 0; i <= rank2 - 2; i++) {
            rate2[i] = root[i + 2] * prod;
            irate2[i] = iroot[i + 2] * iprod;
            prod *= iroot[i + 2];
            iprod *= root[i + 2];
        }
        prod = 1, iprod = 1;
        for (int i = 0; i <= rank2 - 3; i++) {
            rate3[i] = root[i + 3] * prod;
            irate3[i] = iroot[i + 3] * iprod;
            prod *= iroot[i + 3];
            iprod *= root[i + 3];
        }
    }

    int n = int(a.size());
    int h = (n == 0 ? -1 : 31 - __builtin_clz(n));
    assert(n == 1 << h);
    if (!inverse) {
        int len = 0;
        while (len < h) {
            if (h - len == 1) {
                int p = 1 << (h - len - 1);
                mint rot = 1;
                For(s, 1 << len) {
                    int offset = s << (h - len);
                    For(i, p) {
                        auto l = a[i + offset];
                        auto r = a[i + offset + p] * rot;
                        a[i + offset] = l + r;
                        a[i + offset + p] = l - r;
                    }
                    rot *= rate2[((~s & -~s) == 0 ? -1 : 31 - __builtin_clz(~s & -~s))];
                }
                len++;
            } else {
                int p = 1 << (h - len - 2);
                mint rot = 1, imag = root[2];
                for (int s = 0; s < (1 << len); s++) {
                    mint rot2 = rot * rot;
                    mint rot3 = rot2 * rot;
                    int offset = s << (h - len);
                    for (int i = 0; i < p; i++) {
                        unsigned long long mod2 = (unsigned long long)(mod) * mod;
                        unsigned long long a0 = a[i + offset].val;
                        unsigned long long a1 = (unsigned long long)(a[i + offset + p].val) * rot.val;
                        unsigned long long a2 = (unsigned long long)(a[i + offset + 2 * p].val) * rot2.val;
                        unsigned long long a3 = (unsigned long long)(a[i + offset + 3 * p].val) * rot3.val;
                        unsigned long long a1na3imag = (a1 + mod2 - a3) % mod * imag.val;
                        unsigned long long na2 = mod2 - a2;
                        a[i + offset] = a0 + a2 + a1 + a3;
                        a[i + offset + 1 * p] = a0 + a2 + (2 * mod2 - (a1 + a3));
                        a[i + offset + 2 * p] = a0 + na2 + a1na3imag;
                        a[i + offset + 3 * p] = a0 + na2 + (mod2 - a1na3imag);
                    }
                    rot *= rate3[((~s & -~s) == 0 ? -1 : 31 - __builtin_clz(~s & -~s))];
                }
                len += 2;
            }
        }
    } else {
        mint coef = mint(1) / mint(len(a));
        For(i, len(a)) a[i] *= coef;
        int len = h;
        while (len) {
            if (len == 1) {
                int p = 1 << (h - len);
                mint irot = 1;
                For(s, 1 << (len - 1)) {
                    int offset = s << (h - len + 1);
                    For(i, p) {
                        unsigned long long l = a[i + offset].val;
                        unsigned long long r = a[i + offset + p].val;
                        a[i + offset] = l + r;
                        a[i + offset + p] = (mod + l - r) * irot.val;
                    }
                    irot *= irate2[((~s & -~s) == 0 ? -1 : 31 - __builtin_clz(~s & -~s))];
                }
                len--;
            } else {
                int p = 1 << (h - len);
                mint irot = 1, iimag = iroot[2];
                For(s, (1 << (len - 2))) {
                    mint irot2 = irot * irot;
                    mint irot3 = irot2 * irot;
                    int offset = s << (h - len + 2);
                    for (int i = 0; i < p; i++) {
                        unsigned long long a0 = a[i + offset + 0 * p].val;
                        unsigned long long a1 = a[i + offset + 1 * p].val;
                        unsigned long long a2 = a[i + offset + 2 * p].val;
                        unsigned long long a3 = a[i + offset + 3 * p].val;
                        unsigned long long x = (mod + a2 - a3) * iimag.val % mod;
                        a[i + offset] = a0 + a1 + a2 + a3;
                        a[i + offset + 1 * p] = (a0 + mod - a1 + x) * irot.val;
                        a[i + offset + 2 * p] = (a0 + a1 + 2 * mod - a2 - a3) * irot2.val;
                        a[i + offset + 3 * p] = (a0 + 2 * mod - a1 - x) * irot3.val;
                    }
                    irot *= irate3[((~s & -~s) == 0 ? -1 : 31 - __builtin_clz(~s & -~s))];
                }
                len -= 2;
            }
        }
    }
}
} // namespace mitsuha

namespace mitsuha{
namespace CFFT {
    using real = double;

    struct C {
        real x, y;

        C() : x(0), y(0) {}

        C(real x, real y) : x(x), y(y) {}
        inline C operator+(const C& c) const { return C(x + c.x, y + c.y); }
        inline C operator-(const C& c) const { return C(x - c.x, y - c.y); }
        inline C operator*(const C& c) const {
            return C(x * c.x - y * c.y, x * c.y + y * c.x);
        }

        inline C conj() const { return C(x, -y); }
    };

    const real PI = acosl(-1);
    int base = 1;
    vector<C> rts = {{0, 0}, {1, 0}};
    vector<int> rev = {0, 1};

    void ensure_base(int nbase) {
        if (nbase <= base) return;
        rev.resize(1 << nbase);
        rts.resize(1 << nbase);
        for (int i = 0; i < (1 << nbase); i++) {
            rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (nbase - 1));
        }
        while (base < nbase) {
            real angle = PI * 2.0 / (1 << (base + 1));
            for (int i = 1 << (base - 1); i < (1 << base); i++) {
                rts[i << 1] = rts[i];
                real angle_i = angle * (2 * i + 1 - (1 << base));
                rts[(i << 1) + 1] = C(cos(angle_i), sin(angle_i));
            }
            ++base;
        }
    }

    void fft(vector<C>& a, int n) {
        assert((n & (n - 1)) == 0);
        int zeros = __builtin_ctz(n);
        ensure_base(zeros);
        int shift = base - zeros;
        for (int i = 0; i < n; i++) {
            if (i < (rev[i] >> shift)) { swap(a[i], a[rev[i] >> shift]); }
        }
        for (int k = 1; k < n; k <<= 1) {
            for (int i = 0; i < n; i += 2 * k) {
                for (int j = 0; j < k; j++) {
                    C z = a[i + j + k] * rts[j + k];
                    a[i + j + k] = a[i + j] - z;
                    a[i + j] = a[i + j] + z;
                }
            }
        }
    }
} // namespace CFFT
} // namespace mitsuha

namespace mitsuha{
template <class mint>
vector<mint> convolution_ntt(vector<mint> a, vector<mint> b) {
    if (a.empty() || b.empty()) return {};
    int n = int(a.size()), m = int(b.size());
    int sz = 1;
    while (sz < n + m - 1) sz *= 2;

    // Speedup when sz = 2^k. Because it's a divide-and-conquer type of thing, you're going to lose a lot of money.
    if ((n + m - 3) <= sz / 2) {
        auto a_last = a.back(), b_last = b.back();
        a.pop_back(), b.pop_back();
        auto c = convolution(a, b);
        c.resize(n + m - 1);
        c[n + m - 2] = a_last * b_last;
        For(i, len(a)) c[i + len(b)] += a[i] * b_last;
        For(i, len(b)) c[i + len(a)] += b[i] * a_last;
        return c;
    }

    a.resize(sz), b.resize(sz);
    bool same = a == b;
    ntt(a, 0);
    if (same) {
        b = a;
    } else {
        ntt(b, 0);
    }
    For(i, sz) a[i] *= b[i];
    ntt(a, 1);
    a.resize(n + m - 1);
    return a;
}

template <typename mint>
vector<mint> convolution_garner(const vector<mint>& a, const vector<mint>& b) {
    int n = len(a), m = len(b);
    if (!n || !m) return {};
    static constexpr int p0 = 167772161;
    static constexpr int p1 = 469762049;
    static constexpr int p2 = 754974721;
    using mint0 = modint<p0>;
    using mint1 = modint<p1>;
    using mint2 = modint<p2>;
    vector<mint0> a0(n), b0(m);
    vector<mint1> a1(n), b1(m);
    vector<mint2> a2(n), b2(m);
    For(i, n) a0[i] = a[i].val, a1[i] = a[i].val, a2[i] = a[i].val;
    For(i, m) b0[i] = b[i].val, b1[i] = b[i].val, b2[i] = b[i].val;
    auto c0 = convolution_ntt<mint0>(a0, b0);
    auto c1 = convolution_ntt<mint1>(a1, b1);
    auto c2 = convolution_ntt<mint2>(a2, b2);
    vector<mint> c(len(c0));
    For(i, n + m - 1) {
        c[i] = CRT3<mint, p0, p1, p2>(c0[i].val, c1[i].val, c2[i].val);
    }
    return c;
}

template <typename R>
vector<double> convolution_fft(const vector<R>& a, const vector<R>& b) {
    using C = CFFT::C;
    int need = (int)a.size() + (int)b.size() - 1;
    int nbase = 1;
    while ((1 << nbase) < need) nbase++;
    CFFT::ensure_base(nbase);
    int sz = 1 << nbase;
    vector<C> fa(sz);
    for (int i = 0; i < sz; i++) {
        double x = (i < (int)a.size() ? a[i] : 0);
        double y = (i < (int)b.size() ? b[i] : 0);
        fa[i] = C(x, y);
    }
    CFFT::fft(fa, sz);
    C r(0, -0.25 / (sz >> 1)), s(0, 1), t(0.5, 0);
    for (int i = 0; i <= (sz >> 1); i++) {
        int j = (sz - i) & (sz - 1);
        C z = (fa[j] * fa[j] - (fa[i] * fa[i]).conj()) * r;
        fa[j] = (fa[i] * fa[i] - (fa[j] * fa[j]).conj()) * r;
        fa[i] = z;
    }
    for (int i = 0; i < (sz >> 1); i++) {
        C A0 = (fa[i] + fa[i + (sz >> 1)]) * t;
        C A1 = (fa[i] - fa[i + (sz >> 1)]) * t * CFFT::rts[(sz >> 1) + i];
        fa[i] = A0 + A1 * s;
    }
    CFFT::fft(fa, sz >> 1);
    vector<double> ret(need);
    for (int i = 0; i < need; i++) {
        ret[i] = (i & 1 ? fa[i >> 1].y : fa[i >> 1].x);
    }
    return ret;
}

vector<long long> convolution(const vector<long long>& a, const vector<long long>& b) {
    int n = len(a), m = len(b);
    if (!n || !m) return {};
    if (min(n, m) <= 2500) return convolution_naive(a, b);
    long long abs_sum_a = 0, abs_sum_b = 0;
    long long LIM = 1e15;
    For(i, n) abs_sum_a = min(LIM, abs_sum_a + abs(a[i]));
    For(i, m) abs_sum_b = min(LIM, abs_sum_b + abs(b[i]));
    if (__int128(abs_sum_a) * abs_sum_b < 1e15) {
        vector<double> c = convolution_fft<long long>(a, b);
        vector<long long> res(len(c));
        For(i, len(c)) res[i] = (long long)(std::floor(c[i] + .5));
        return res;
    }

    static constexpr unsigned long long MOD1 = 754974721; // 2^24
    static constexpr unsigned long long MOD2 = 167772161; // 2^25
    static constexpr unsigned long long MOD3 = 469762049; // 2^26
    static constexpr unsigned long long M2M3 = MOD2 * MOD3;
    static constexpr unsigned long long M1M3 = MOD1 * MOD3;
    static constexpr unsigned long long M1M2 = MOD1 * MOD2;
    static constexpr unsigned long long M1M2M3 = MOD1 * MOD2 * MOD3;

    static const unsigned long long i1 = mod_inv(MOD2 * MOD3, MOD1);
    static const unsigned long long i2 = mod_inv(MOD1 * MOD3, MOD2);
    static const unsigned long long i3 = mod_inv(MOD1 * MOD2, MOD3);

    using mint1 = modint<MOD1>;
    using mint2 = modint<MOD2>;
    using mint3 = modint<MOD3>;

    vector<mint1> a1(n), b1(m);
    vector<mint2> a2(n), b2(m);
    vector<mint3> a3(n), b3(m);
    For(i, n) a1[i] = a[i], a2[i] = a[i], a3[i] = a[i];
    For(i, m) b1[i] = b[i], b2[i] = b[i], b3[i] = b[i];

    auto c1 = convolution_ntt<mint1>(a1, b1);
    auto c2 = convolution_ntt<mint2>(a2, b2);
    auto c3 = convolution_ntt<mint3>(a3, b3);

    vector<long long> c(n + m - 1);
    For(i, n + m - 1) {
        unsigned long long x = 0;
        x += (c1[i].val * i1) % MOD1 * M2M3;
        x += (c2[i].val * i2) % MOD2 * M1M3;
        x += (c3[i].val * i3) % MOD3 * M1M2;
        long long diff = c1[i].val - ((long long)(x) % (long long)(MOD1));
        if (diff < 0) diff += MOD1;
        static constexpr unsigned long long offset[5]
                = {0, 0, M1M2M3, 2 * M1M2M3, 3 * M1M2M3};
        x -= offset[diff % 5];
        c[i] = x;
    }
    return c;
}

template <typename mint>
vector<mint> convolution(const vector<mint>& a, const vector<mint>& b) {
    int n = len(a), m = len(b);
    if (!n || !m) return {};
    if (mint::can_ntt()) {
        if (min(n, m) <= 50) return convolution_karatsuba<mint>(a, b);
        return convolution_ntt(a, b);
    }
    if (min(n, m) <= 200) return convolution_karatsuba<mint>(a, b);
    return convolution_garner(a, b);
}
} // namespace mitsuha

using mint = modint998;

int main(){
    
    vector<mint> a = {1, 3, 4, 5};
    vector<mint> b = {3, 4, 5};
    print(convolution(a, b));
    return 0;
}

