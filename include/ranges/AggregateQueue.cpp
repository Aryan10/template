#include <bits/stdc++.h>
using namespace std;

template <typename T, class Func> 
struct AggregateStack : stack<pair<T, T>> {
    static Func merge;

    void push(T const& x) {
        this->emplace(x, this->empty() ? x : merge(this->query(), x));
    }

    T top() const {
        return stack<pair<T, T>>::top().first;
    }

    T query() const {
        return stack<pair<T, T>>::top().second;
    }
};

template <typename T, class Func>
struct AggregateQueue {
    AggregateStack<T, Func> in, out;
    
    void push(T const& x) {
        in.push(x);
    }

    void pop() {
        if (out.empty()) {
            while (!in.empty()) {
                out.push(in.top());
                in.pop();
            }
        }
        out.pop();
    }

    T query() const {
        if (in.empty()) return out.query();
        if (out.empty()) return in.query();
        return AggregateStack<T, Func>::merge(in.query(), out.query());
    }
};