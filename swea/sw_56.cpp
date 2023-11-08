#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

extern void init(int N, int K);
extern void registerUser(int mTime, int mUID, int mNum, int mGroupIDs[]);
extern int offerNews(int mTime, int mNewsID, int mDelay, int mGroupID);
extern void cancelNews(int mTime, int mNewsID);
extern int checkUser(int mTime, int mUID, int mRetIDs[]);

/////////////////////////////////////////////////////////////////////////

#define INIT 0
#define REGI 1
#define OFFER 2
#define CANCEL 3
#define CHECK 4

static int gids[30];
static int ansids[3];
static int retids[3];
static bool run() {
    int N, K;
    int cmd, ans, ret;
    int time, num, uid, gid, nid, delay;

    int Q = 0;
    bool okay = false;

    scanf("%d", &Q);
    for (int q = 0; q < Q; ++q) {
        scanf("%d", &cmd);
        switch (cmd) {
            case INIT:
                scanf("%d %d", &N, &K);
                init(N, K);
                okay = true;
                break;

            case REGI:
                scanf("%d %d %d", &time, &uid, &num);
                for (int m = 0; m < num; m++) {
                    scanf("%d", &gids[m]);
                }
                registerUser(time, uid, num, gids);
                break;

            case OFFER:
                scanf("%d %d %d %d %d", &time, &nid, &delay, &gid, &ans);
                ret = offerNews(time, nid, delay, gid);
                if (ans != ret) {
                    okay = false;
                }
                break;

            case CANCEL:
                scanf("%d %d", &time, &nid);
                cancelNews(time, nid);
                break;

            case CHECK:
                scanf("%d %d %d", &time, &uid, &ans);
                ret = checkUser(time, uid, retids);

                num = ans;
                if (num > 3) num = 3;
                for (int m = 0; m < num; m++) {
                    scanf("%d", &ansids[m]);
                }
                if (ans != ret) {
                    okay = false;
                } else {
                    for (int m = 0; m < num; m++) {
                        if (ansids[m] != retids[m]) {
                            okay = false;
                        }
                    }
                }
                break;

            default:
                okay = false;
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

#include <list>
#include <queue>
#include <unordered_map>
using namespace std;
struct News {
    int time;
    int newsID;
    int channelID;
    bool expired;
};
struct cmp {
    bool operator()(News* a, News* b) {
        if (a->time == b->time) return a->newsID > b->newsID;
        return a->time > b->time;
    }
};
struct User {
    int userID;
    list<News*> news;
};
struct Channel {
    int channelID;
    list<int> users;
};
User* user[500];
Channel* channel[500];
News* news[30000];
int curTime;
unordered_map<int, int> userID;
unordered_map<int, int> channelID;
unordered_map<int, int> newsID;
priority_queue<News*, vector<News*>, cmp> newsQueue;
int userCnt;
int channelCnt;
int newsCnt;
void init(int N, int K) {
    userID.clear();
    channelID.clear();
    newsID.clear();
    curTime = 0;
    while (!newsQueue.empty()) newsQueue.pop();
    userCnt = 0;
    channelCnt = 0;
    newsCnt = 0;
    for (int i = 0; i < 500; i++) {
        user[i] = nullptr;
        channel[i] = nullptr;
    }
    for (int i = 0; i < 30000; i++) {
        news[i] = nullptr;
    }
}

void sendMail() {
    while (!newsQueue.empty()) {
        News* tmpNews = newsQueue.top();
        if (tmpNews->time > curTime) break;
        newsQueue.pop();
        if (tmpNews->expired) continue;
        for (int i : channel[channelID[tmpNews->channelID]]->users) {
            user[i]->news.push_back(tmpNews);
        }
    }
}
void registerUser(int mTime, int mUID, int mNum, int mChannelIDs[]) {
    // printf("register: %dx\n", mUID);
    curTime = mTime;
    sendMail();
    int uid, cid;
    if (userID.count(mUID))
        uid = userID[mUID];
    else {
        uid = userID[mUID] = userCnt++;
        User* tmpUser = new User;
        tmpUser->news.clear();
        tmpUser->userID = uid;
        user[uid] = tmpUser;
    }
    for (int i = 0; i < mNum; i++) {
        // printf("-%d", mChannelIDs[i]);
        if (channelID.count(mChannelIDs[i])) {
            cid = channelID[mChannelIDs[i]];
            channel[cid]->users.push_back(uid);
        } else {
            cid = channelID[mChannelIDs[i]] = channelCnt++;
            Channel* tmpChannel = new Channel;
            tmpChannel->channelID = cid;
            channel[cid] = tmpChannel;
            tmpChannel->users.push_back(uid);
        };
    }
    // printf("\n");
}

int offerNews(int mTime, int mNewsID, int mDelay, int mChannelID) {
    // printf("news: %d, %d\n", mChannelID, mNewsID);
    curTime = mTime;
    int cid = channelID[mChannelID];
    News* tmpNews = new News;
    newsID[mNewsID] = newsCnt;
    tmpNews->newsID = mNewsID;
    tmpNews->expired = false;
    tmpNews->time = mTime + mDelay;
    tmpNews->channelID = mChannelID;
    news[newsCnt++] = tmpNews;
    newsQueue.push(tmpNews);
    return channel[cid]->users.size();
}

void cancelNews(int mTime, int mNewsID) {
    curTime = mTime;
    sendMail();
    int nid = newsID[mNewsID];
    News* tmpNews = news[nid];
    tmpNews->expired = true;
}

int checkUser(int mTime, int mUID, int mRetIDs[]) {
    // printf("check: %d\n", mUID);
    curTime = mTime;
    int uid = userID[mUID];
    sendMail();
    int ret = user[uid]->news.size();
    auto cursur = user[uid]->news.rbegin();
    int cnt = 0;
    for (auto it = user[uid]->news.rbegin(); it != user[uid]->news.rend();
         it++) {
        // printf("%d ", (*it)->newsID);
        if ((*it)->expired) {
            ret--;
            continue;
        } else if (cnt < 3) {
            mRetIDs[cnt] = (*it)->newsID;
            cnt++;
        }
    }
    user[uid]->news.clear();
    return ret;
}