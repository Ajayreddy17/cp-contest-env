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

int main(){

    Int(a, b);
    print(a - b - b);
    return 0;
}

