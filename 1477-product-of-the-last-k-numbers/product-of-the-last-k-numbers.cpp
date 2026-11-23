class ProductOfNumbers {
private:
    vector<int> st;

public:
    ProductOfNumbers() { st.push_back(1); }

    void add(int num) {
        if (num == 0) {
            st.clear();
            st.push_back(1);
        } else {
            st.push_back(st.back() * num);
        }
    }

    int getProduct(int k) {
        int n = static_cast<int>(st.size()) - 1;
        if (k > n) {
            return 0;
        }
        return st.back() / st[st.size() - 1 - k];
    }
};

/**
 * Your ProductOfNumbers object will be instantiated and called as such:
 * ProductOfNumbers* obj = new ProductOfNumbers();
 * obj->add(num);
 * int param_2 = obj->getProduct(k);
 */