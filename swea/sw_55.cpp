#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <string.h>

extern void init();
extern void create(int mTime, char mBranch[], char mFile[], char mData[]);
extern void edit(int mTime, char mBranch[], char mFile[], char mData[]);
extern void branch(int mTime, char mBranch[], char mChild[]);
extern void merge(int mTime, char mBranch[]);
extern int readfile(int mTime, char mBranch[], char mFile[], char retString[]);

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

#define CMD_CREATE 100
#define CMD_EDIT 200
#define CMD_BRANCH 300
#define CMD_MERGE 400
#define CMD_READ 500

#define MAXN 10000
#define MAXL 11

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

static bool run() {
    int Q, ans;
    bool isOkey = true;

    scanf("%d", &Q);
    init();
    for (int q = 1; q <= Q; ++q) {
        int cmd, len;
        char mBranch[MAXL], mChild[MAXL], mFile[MAXL], mData[MAXL],
            retString[MAXL];
        scanf("%d", &cmd);

        switch (cmd) {
            case CMD_CREATE:
                scanf(" %s %s %s", mBranch, mFile, mData);
                create(q, mBranch, mFile, mData);
                break;

            case CMD_EDIT:
                scanf(" %s %s %s", mBranch, mFile, mData);
                edit(q, mBranch, mFile, mData);
                break;

            case CMD_BRANCH:
                scanf(" %s %s", mBranch, mChild);
                branch(q, mBranch, mChild);
                break;

            case CMD_MERGE:
                scanf(" %s", mBranch);
                merge(q, mBranch);
                break;

            case CMD_READ:
                scanf(" %s %s", mBranch, mFile);
                len = readfile(q, mBranch, mFile, retString);

                scanf(" %d %s", &ans, mData);
                if (ans != len) {
                    printf("%s(%d), %s(%d)\n", retString, len, mData, ans);
                    isOkey = false;
                } else if (strcmp(retString, mData) != 0)
                    isOkey = false;
                break;

            default:
                isOkey = false;
        }
    }
    return isOkey;
}

int main() {
    setbuf(stdout, NULL);
    freopen("input.txt", "r", stdin);

    int T, MARK;
    scanf("%d %d", &T, &MARK);
    for (int tc = 1; tc <= T; tc++) {
        printf("#%d %d\n", tc, run() ? MARK : 0);
    }
    return 0;
}

#include <list>
#include <string>
#include <unordered_map>
using namespace std;
struct File {
    string name, content;
    int created, edited;
};

struct Branch {
    string name;
    Branch *parent;
    list<Branch *> childs;
    list<File *> files;
    bool isValid;
};
unordered_map<string, Branch *> branches;
int branchCnt;

void init() {
    branches.clear();
    Branch *root = new Branch;
    root->isValid = true;
    root->name = "root";
    root->parent = nullptr;
    branches["root"] = root;
}

void create(int mTime, char mBranch[], char mFile[], char mData[]) {
    Branch *parent = branches[mBranch];
    File *file = new File;
    file->content = mData;
    file->created = mTime;
    file->edited = mTime;
    file->name = mFile;
    if (parent->files.size() == 50) parent->files.pop_front();
    parent->files.push_back(file);
}

void edit(int mTime, char mBranch[], char mFile[], char mData[]) {
    Branch *parent = branches[mBranch];
    for (auto it : parent->files) {
        if (it->name == mFile) {
            it->content = mData;
            it->edited = mTime;
            break;
        }
    }
}

void branch(int mTime, char mBranch[], char mChild[]) {
    Branch *parent = branches[mBranch];
    Branch *child = new Branch;
    parent->childs.push_back(child);
    branches[mChild] = child;
    child->isValid = true;
    child->name = mChild;
    child->parent = parent;
    for (auto it : parent->files) {
        File *tmp = new File;
        tmp->content = it->content;
        tmp->created = it->created;
        tmp->edited = it->edited;
        tmp->name = it->name;
        child->files.push_back(tmp);
    };
}
list<File *> q1, q2;
unordered_map<string, File *> duplicates;

void merge(Branch *branch) {
    Branch *parent = branch->parent;
    while (!branch->childs.empty()) {
        Branch *child = branch->childs.front();
        if (child->isValid)
            merge(child);
        else {
            printf("%s \n", child->name.c_str());
        }
        branch->childs.pop_front();
    }
    duplicates.clear();
    q1.clear();
    q2.clear();
    for (File *it : parent->files) {
        duplicates[it->name] = it;
    }
    for (File *it : branch->files) {
        if (duplicates.count(it->name)) {
            if (it->created == duplicates[it->name]->created &&
                it->edited > duplicates[it->name]->edited) {
                duplicates[it->name]->content = it->content;
                duplicates[it->name]->edited = it->edited;
            }
        } else {
            q2.push_back(it);
        }
    }
    for (auto it : parent->files) {
        q1.push_back(it);
    }
    parent->files.clear();
    while (!q1.empty() || !q2.empty()) {
        auto q = (q2.empty() || !q1.empty() && !q2.empty() &&
                                    q1.front()->created < q2.front()->created)
                     ? &q1
                     : &q2;
        if (parent->files.size() == 50) parent->files.pop_front();
        parent->files.push_back(q->front());
        q->pop_front();
    }
    branch->isValid = false;
}

void merge(int mTime, char mBranch[]) { merge(branches[mBranch]); }

int readfile(int mTime, char mBranch[], char mFile[], char retString[]) {
    Branch *parent = branches[mBranch];
    for (auto it : parent->files) {
        if (it->name == mFile) {
            strcpy(retString, it->content.c_str());
            return it->content.size();
        }
    }
    return -1;
}