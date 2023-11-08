#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define CMD_MKDIR 1
#define CMD_RM 2
#define CMD_CP 3
#define CMD_MV 4
#define CMD_FIND 5

#define NAME_MAXLEN 6
#define PATH_MAXLEN 1999

extern void init(int n);
extern void cmd_mkdir(char path[PATH_MAXLEN + 1], char name[NAME_MAXLEN + 1]);
extern void cmd_rm(char path[PATH_MAXLEN + 1]);
extern void cmd_cp(char srcPath[PATH_MAXLEN + 1],
                   char dstPath[PATH_MAXLEN + 1]);
extern void cmd_mv(char srcPath[PATH_MAXLEN + 1],
                   char dstPath[PATH_MAXLEN + 1]);
extern int cmd_find(char path[PATH_MAXLEN + 1]);
extern void print();

static bool run(int m) {
    bool isAccepted = true;
    int cmd;
    char name[NAME_MAXLEN + 1];
    char path1[PATH_MAXLEN + 1], path2[PATH_MAXLEN + 1];
    while (m--) {
        scanf("%d", &cmd);

        if (cmd == CMD_MKDIR) {
            scanf("%s%s", path1, name);
            cmd_mkdir(path1, name);
        } else if (cmd == CMD_RM) {
            scanf("%s", path1);
            cmd_rm(path1);
        } else if (cmd == CMD_CP) {
            scanf("%s%s", path1, path2);
            cmd_cp(path1, path2);
        } else if (cmd == CMD_MV) {
            scanf("%s%s", path1, path2);
            cmd_mv(path1, path2);
        } else {
            int ret;
            int answer;
            scanf("%s", path1);
            ret = cmd_find(path1);
            scanf("%d", &answer);
            isAccepted &= (ret == answer);
        }
    }

    return isAccepted;
}

int main(void) {
    int test, T;
    int n, m;

    freopen("input.txt", "r", stdin);

    setbuf(stdout, NULL);

    scanf("%d", &T);

    for (test = 1; test <= T; ++test) {
        scanf("%d%d", &n, &m);

        init(n);

        if (run(m)) {
            printf("#%d 100\n", test);
        } else {
            printf("#%d 0\n", test);
        }
    }

    return 0;
}

//-----------USER CODE-----------//
#define NAME_MAXLEN 6
#define PATH_MAXLEN 1999
#define MAX_DIR 100000

struct Node {
    char name[NAME_MAXLEN + 1];
    int nextSibling;
    int firstChild;
};
int nodeCnt = 0;
Node node[MAX_DIR + 1];

int mstrcmp(const char *a, const char *b) {
    int i;
    for (i = 0; a[i] != '\0'; i++) {
        if (a[i] != b[i]) return a[i] - b[i];
    }
    return a[i] - b[i];
}

void mstrcpy(char *dest, const char *src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = src[i];
}
int makeNode(char *name) {
    Node *ret = &node[nodeCnt];
    mstrcpy(ret->name, name);
    ret->nextSibling = -1;
    ret->firstChild = -1;
    return nodeCnt++;
}

int getNode(char path[PATH_MAXLEN + 1]) {
    if (path[1] == '\0') return 0;  // root
    int i = 1, j, cur = 0;          // "/"
    char nextdir[NAME_MAXLEN + 1];
    while (path[i] != '\0' && cur != -1) {
        j = 0;
        cur = node[cur].firstChild;
        while (path[i] != '/') {
            nextdir[j++] = path[i++];
        }
        nextdir[j] = '\0';
        while (cur != -1) {
            if (mstrcmp(nextdir, node[cur].name) == 0) {
                i++;
                break;
            } else
                cur = node[cur].nextSibling;
        }
    }
    return cur;
}

int getBeforeNode(
    char path[PATH_MAXLEN +
              1]) {  // 이전노드번호+아들인지(100000),형제인지(200000)
    if (path[1] == '\0') return 100000;    // root
    int i = 1, j, cur = 0, beforecur = 0;  // "/"
    int flag;
    char nextdir[NAME_MAXLEN + 1];
    while (path[i] != '\0' && cur != -1) {
        j = 0;
        beforecur = cur;
        cur = node[cur].firstChild;
        flag = 100000;
        while (path[i] != '/') {
            nextdir[j++] = path[i++];
        }
        nextdir[j] = '\0';
        while (cur != -1) {
            if (mstrcmp(nextdir, node[cur].name) == 0) {
                i++;
                break;
            } else {
                beforecur = cur;
                cur = node[cur].nextSibling;
                flag = 200000;
            }
        }
    }
    return beforecur + flag;
}

void init(int n) {
    nodeCnt = 1;
    node[0].name[0] = '/';
    node[0].name[1] = '\0';
    node[0].firstChild = -1;
    node[0].nextSibling = -1;
}

void cmd_mkdir(char path[PATH_MAXLEN + 1], char name[NAME_MAXLEN + 1]) {
    int parent = getNode(path), child = makeNode(name);
    if (node[parent].firstChild == -1) {
        node[parent].firstChild = child;
    } else {
        int brother = node[parent].firstChild;
        while (node[brother].nextSibling != -1)
            brother = node[brother].nextSibling;
        node[brother].nextSibling = child;
    }
}

void cmd_rm(char path[PATH_MAXLEN + 1]) {
    int beforenode = getBeforeNode(path);
    int target = beforenode % 100000;  // 이전 노드 번호
    int flag = beforenode / 100000;  // 1이면 아들 지움, 2면 형제 지움
    if (flag == 1) {
        node[target].firstChild = node[node[target].firstChild].nextSibling;
    } else {
        node[target].nextSibling = node[node[target].nextSibling].nextSibling;
    }
}

int cpdir(int target) {
    if (target == -1) return -1;
    int ret = makeNode(node[target].name);
    node[ret].firstChild = cpdir(node[target].firstChild);
    node[ret].nextSibling = cpdir(node[target].nextSibling);
    return ret;
}

void cmd_cp(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
    int cur = getNode(dstPath);
    int target = getNode(srcPath);

    if (node[cur].firstChild == -1) {
        node[cur].firstChild = cpdir(target);
        node[node[cur].firstChild].nextSibling = -1;
    } else {
        cur = node[cur].firstChild;
        while (node[cur].nextSibling != -1) {
            cur = node[cur].nextSibling;
        }
        node[cur].nextSibling = cpdir(target);
        node[node[cur].nextSibling].nextSibling = -1;
    }
}

void cmd_mv(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
    int cur = getNode(dstPath);
    int beforetarget = getBeforeNode(srcPath);
    int flag = beforetarget / 100000;  // 1이면 아들 지움, 2면 형제 지움
    int target;
    beforetarget %= 100000;
    if (flag == 1) {
        target = node[beforetarget].firstChild;
        node[beforetarget].firstChild =
            node[node[beforetarget].firstChild].nextSibling;
    } else {
        target = node[beforetarget].nextSibling;
        node[beforetarget].nextSibling =
            node[node[beforetarget].nextSibling].nextSibling;
    }
    node[target].nextSibling = -1;
    if (node[cur].firstChild == -1)
        node[cur].firstChild = target;
    else {
        cur = node[cur].firstChild;
        while (node[cur].nextSibling != -1) {
            cur = node[cur].nextSibling;
        }
        node[cur].nextSibling = target;
    }
}

int rec_count(int no) {
    int child, siblings;
    child = node[no].firstChild == -1 ? 0 : rec_count(node[no].firstChild);
    siblings = node[no].nextSibling == -1 ? 0 : rec_count(node[no].nextSibling);
    return child + siblings + 1;
}

int cmd_find(char path[PATH_MAXLEN + 1]) {
    int parent = getNode(path), child;
    child =
        node[parent].firstChild == -1 ? 0 : rec_count(node[parent].firstChild);
    return child;
}