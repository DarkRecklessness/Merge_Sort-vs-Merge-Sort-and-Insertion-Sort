#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using ql = __int128_t;

// [l, r)
void insertion_sort(vector<int>& a, int l, int r) {
    for (int i = l + 1; i < r; ++i) {
        int idx = i;
        int val = a[i];
        for (; idx > l; --idx) {
            if (a[idx - 1] <= val) break;
            a[idx] = a[idx - 1];
        }
        a[idx] = val;
    }
}

// [l, r)
void merge_sort(vector<int>& a, int l, int r) {
    if (r - l <= 15) {
        insertion_sort(a, l, r);
        return;
    }

    int m = l + (r - l) / 2;
    merge_sort(a, l, m);
    merge_sort(a, m, r);

    vector<int> res(r - l);
    int ptr = 0;
    int left = l;
    int right = m;
    while (left < m && right < r) {
        if (a[left] <= a[right]) {
            res[ptr++] = a[left++];
            continue;
        }
        res[ptr++] = a[right++];
    }
    while (left < m) {
        res[ptr++] = a[left++];
    }
    while (right < r) {
        res[ptr++] = a[right++];
    }

    for (int i = 0; i < r - l; ++i) {
        a[i + l] = res[i];
    }
}

void usual_merge_sort(vector<int>& a, int l, int r) {
    if (l + 1 == r) {
        return;
    }

    int m = l + (r - l) / 2;
    usual_merge_sort(a, l, m);
    usual_merge_sort(a, m, r);

    vector<int> res(r - l);
    int ptr = 0;
    int left = l;
    int right = m;
    while (left < m && right < r) {
        if (a[left] <= a[right]) {
            res[ptr++] = a[left++];
            continue;
        }
        res[ptr++] = a[right++];
    }
    while (left < m) {
        res[ptr++] = a[left++];
    }
    while (right < r) {
        res[ptr++] = a[right++];
    }

    for (int i = 0; i < r - l; ++i) {
        a[i + l] = res[i];
    }
}

class ArrayGenerator {
    mt19937 rnd;

public:
    explicit ArrayGenerator(int seed) : rnd(seed) {}

    vector<int> GetRandom(size_t n, int min, int max) {
        vector<int> res(n);
        std::uniform_int_distribution<int> distribution(min, max);
        for (size_t i = 0; i < n; ++i) {
            res[i] = distribution(rnd);
        }
        return res;
    }

    vector<int> GetSorted(size_t n, bool descending = false) {
        vector<int> res(n);
        iota(res.begin(), res.end(), 0);

        if (descending) {
            reverse(res.begin(), res.end());
        }
        return res;
    }

    vector<int> GetAlmostSorted(size_t n, int swaps_count) {
        vector<int> res = GetSorted(n, false);

        for (int i = 0; i < swaps_count; ++i) {
            size_t idx1 = rnd() % n;
            size_t idx2 = rnd() % n;
            swap(res[idx1], res[idx2]);
        }
        return res;
    }
};

class SortTester {
    ArrayGenerator& generator;

public:
    explicit SortTester(ArrayGenerator& gen) : generator(gen) {}

    void RunTest(
        const string& sort_type,
        const string& data_type,
        size_t min_size,
        size_t max_size,
        size_t step,
        int runs_per_size,
        const string& output_filename)
    {
        ofstream outFile(output_filename);

        outFile << "N,AverageTime_ms" << endl;

        for (size_t currentSize = min_size; currentSize <= max_size; currentSize += step) {

            vector<ll> durations;
            vector<int> src;
            if (data_type == "random") {
                src = generator.GetRandom(currentSize, 0, 10000);
            } else if (data_type == "reversed") {
                src = generator.GetSorted(currentSize, true);
            } else {
                src = generator.GetAlmostSorted(currentSize, currentSize / 100);
            }

            for (int i = 0; i < runs_per_size; ++i) {
                auto data = src;

                auto start = std::chrono::high_resolution_clock::now();

                if (sort_type == "standard") {
                    usual_merge_sort(data, 0, currentSize);
                } else if (sort_type == "hybrid") {
                    merge_sort(data, 0, currentSize);
                }

                auto elapsed = std::chrono::high_resolution_clock::now() - start;
                long long msec = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
                durations.push_back(msec);
            }

            ll sum = accumulate(durations.begin(), durations.end(), 0LL);
            ll average_ms = sum / runs_per_size;

            outFile << currentSize << "," << average_ms << endl;
            cout << currentSize << " done!" << endl;
        }

        outFile.close();
    }
};

void solve() {
    ArrayGenerator generator(69426942);
    SortTester tester(generator);

    const size_t MAX_SIZE = 100'000;
    const size_t STEP = 100;
    const size_t MIN_SIZE = 500;
    const int RUNS = 5;

    tester.RunTest("standard", "random", MIN_SIZE, MAX_SIZE, STEP, RUNS, "standard_random.csv");
    tester.RunTest("standard", "reversed", MIN_SIZE, MAX_SIZE, STEP, RUNS, "standard_reversed.csv");
    tester.RunTest("standard", "almost_sorted", MIN_SIZE, MAX_SIZE, STEP, RUNS, "standard_almost_sorted.csv");
    tester.RunTest("hybrid", "random", MIN_SIZE, MAX_SIZE, STEP, RUNS, "hybrid_random.csv");
    tester.RunTest("hybrid", "reversed", MIN_SIZE, MAX_SIZE, STEP, RUNS, "hybrid_reversed.csv");
    tester.RunTest("hybrid", "almost_sorted", MIN_SIZE, MAX_SIZE, STEP, RUNS, "hybrid_almost_sorted.csv");
}

signed main() {
#ifdef DarkReck
    //freopen("..\\input.txt", "r", stdin);
    //freopen("..\\output.txt", "w", stdout);
#endif
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    solve();
}