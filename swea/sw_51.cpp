#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
using namespace std;
extern void init();
extern int buy(int bId, int mProduct, int mPrice, int mQuantity);
extern int cancel(int bId);
extern int sell(int sId, int mProduct, int mPrice, int mQuantity);
extern int refund(int sId);

/////////////////////////////////////////////////////////////////////////

#define CMD_INIT 1
#define CMD_BUY 2
#define CMD_CANCEL 3
#define CMD_SELL 4
#define CMD_REFUND 5

static bool run() {
    int q;
    scanf("%d", &q);

    int id, product, price, quantity;
    int cmd, ans, ret = 0;
    bool okay = false;

    for (int i = 0; i < q; ++i) {
        scanf("%d", &cmd);
        switch (cmd) {
            case CMD_INIT:
                init();
                okay = true;
                break;
            case CMD_BUY:
                scanf("%d %d %d %d %d", &id, &product, &price, &quantity, &ans);
                ret = buy(id, product, price, quantity);
                // printf("buy: %d, %d\n", ret, ans);
                if (ans != ret) okay = false;
                break;
            case CMD_CANCEL:
                scanf("%d %d", &id, &ans);
                ret = cancel(id);
                // printf("cancel: %d, %d\n", ret, ans);
                if (ans != ret) okay = false;
                break;
            case CMD_SELL:
                scanf("%d %d %d %d %d", &id, &product, &price, &quantity, &ans);
                ret = sell(id, product, price, quantity);
                // printf("sell: %d, %d\n", ret, ans);
                if (ans != ret) okay = false;
                break;
            case CMD_REFUND:
                scanf("%d %d", &id, &ans);
                ret = refund(id);
                // printf("refund: %d, %d\n", ret, ans);
                if (ans != ret) okay = false;
                break;
            default:
                okay = false;
                break;
        }
    }
    return okay;
}

int main() {
    setbuf(stdout, NULL);
    freopen("input.txt", "r", stdin);

    int T, MARK;
    scanf("%d %d", &T, &MARK);

    for (int tc = 1; tc <= T; tc++) {
        int score = run() ? MARK : 0;
        printf("#%d %d\n", tc, score);
    }

    return 0;
}

#include <map>
#include <queue>
#include <stack>
#include <vector>
using namespace std;
struct Buy {
    int bid, product, price, quantity, originQuantity;
    bool valid;
};
struct Sell {
    int sid, product, price, quantity;
    bool valid;
    vector<pair<int, int>> bIdQuantities;
};
unordered_map<int, Buy *> buys;
unordered_map<int, Sell *> sells;
unordered_map<int, int> products;
struct cmp {
    bool operator()(Buy *a, Buy *b) {
        if (a->price == b->price)
            return a->bid > b->bid;
        else
            return a->price > b->price;
    }
};

unordered_map<int, priority_queue<Buy *, vector<Buy *>, cmp>> product_buys;
void init() {
    buys.clear();
    sells.clear();
    products.clear();
    return;
}

int buy(int bId, int mProduct, int mPrice, int mQuantity) {
    Buy *tmp = new Buy;
    tmp->bid = bId;
    tmp->valid = true;
    tmp->product = mProduct;
    tmp->price = mPrice;
    tmp->quantity = mQuantity;
    tmp->originQuantity = mQuantity;
    buys[bId] = tmp;
    if (!product_buys.count(mProduct))
        product_buys[mProduct] = priority_queue<Buy *, vector<Buy *>, cmp>();
    product_buys[mProduct].push(tmp);
    if (products.count(mProduct))
        products[mProduct] += mQuantity;
    else
        products[mProduct] = mQuantity;
    return products[mProduct];
}

int cancel(int bId) {
    if (!buys.count(bId)) return -1;
    Buy *buy = buys[bId];
    if (!buy->valid || buy->quantity < buy->originQuantity) return -1;
    products[buy->product] -= buy->originQuantity;
    buy->valid = false;
    return products[buy->product];
}

int sell(int sId, int mProduct, int mPrice, int mQuantity) {
    if (!products.count(mProduct) || products[mProduct] < mQuantity) return -1;
    Sell *tmp = new Sell;
    tmp->sid = sId;
    tmp->valid = true;
    tmp->product = mProduct;
    tmp->price = mPrice;
    tmp->quantity = mQuantity;
    tmp->bIdQuantities = vector<pair<int, int>>();
    sells[sId] = tmp;
    int ans = 0, left = mQuantity;
    while (!product_buys[mProduct].empty() && left > 0) {
        Buy *buy = product_buys[mProduct].top();
        if (buy->valid == false || buy->quantity == 0) {
            product_buys[mProduct].pop();
            continue;
        }
        if (buy->quantity >= left) {
            tmp->bIdQuantities.push_back({buy->bid, left});
            buy->quantity -= left;
            products[mProduct] -= left;
            ans += left * (mPrice - buy->price);
            left = 0;
        } else {
            tmp->bIdQuantities.push_back({buy->bid, buy->quantity});
            left -= buy->quantity;
            products[mProduct] -= buy->quantity;
            ans += buy->quantity * (mPrice - buy->price);
            buy->quantity = 0;
            product_buys[mProduct].pop();
        }
    }
    return ans;
}

int refund(int sId) {
    if (!sells.count(sId) || sells[sId]->valid == false) return -1;
    Sell *tmp = sells[sId];
    for (auto it = sells[sId]->bIdQuantities.begin();
         it != sells[sId]->bIdQuantities.end(); it++) {
        if (buys[it->first]->quantity == 0 || !buys[it->first]->valid)
            product_buys[tmp->product].push(buys[it->first]);
        buys[it->first]->quantity += it->second;
        buys[it->first]->valid = true;
    }
    products[tmp->product] += tmp->quantity;
    tmp->valid = false;
    return tmp->quantity;
}