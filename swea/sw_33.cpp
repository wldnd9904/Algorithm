#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define INIT 0
#define SENDMAIL 1
#define GETCOUNT 2
#define DELETEMAIL 3
#define SEARCHMAIL 4

extern void init(int N, int K);
extern void sendMail(char subject[], int uID, int cnt, int rIDs[]);
extern int getCount(int uID);
extern int deleteMail(int uID, char subject[]);
extern int searchMail(int uID, char text[]);

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

#define MAX_WORD 10000
static char Word[MAX_WORD][11];

static int N, W, minR, maxR, SW;

static int mSeed;
static int pseudo_rand(void) {
    mSeed = mSeed * 214013 + 2531011;
    return (mSeed >> 16) & 0x7FFF;
}

static void make_string(int seed) {
    mSeed = seed;

    for (int i = 0; i < W; ++i) {
        int length = 5 + pseudo_rand() % 6;
        for (int k = 0; k < length; ++k) {
            Word[i][k] = 'a' + pseudo_rand() % 26;
        }
        Word[i][length] = '\0';
    }
}

static void send_mail(int seed) {
    char str[200];
    int pos = 0;

    mSeed = seed;

    int wcnt = 1 + pseudo_rand() % SW;
    for (int i = 0; i < wcnt; ++i) {
        int widx = pseudo_rand() % W;
        for (int k = 0; k < 10; ++k) {
            if (Word[widx][k] == '\0') break;
            str[pos++] = Word[widx][k];
        }
        str[pos++] = ' ';
    }
    str[pos - 1] = '\0';

    int uid = pseudo_rand() % N;
    int rcnt = minR + pseudo_rand() % (maxR - minR + 1);
    int rids[50];
    for (int i = 0; i < rcnt; ++i) {
        rids[i] = pseudo_rand() % N;
    }

    sendMail(str, uid, rcnt, rids);
}

static int delete_mail(int uid, int seed) {
    char str[200];
    int pos = 0;

    mSeed = seed;

    int wcnt = 1 + pseudo_rand() % SW;
    for (int i = 0; i < wcnt; ++i) {
        int widx = pseudo_rand() % W;
        for (int k = 0; k < 10; ++k) {
            if (Word[widx][k] == '\0') break;
            str[pos++] = Word[widx][k];
        }
        str[pos++] = ' ';
    }
    str[pos - 1] = '\0';

    return deleteMail(uid, str);
}

static int run(int answer) {
    int Q, K, cmd, sample, seed, param1, param2, ret;
    char str[30];

    scanf("%d %d %d %d", &Q, &sample, &N, &K);
    if (sample == 0) {
        scanf("%d %d %d %d %d", &W, &minR, &maxR, &SW, &seed);
        make_string(seed);
    }

    init(N, K);

    for (int i = 1; i < Q; ++i) {
        scanf("%d", &cmd);
        switch (cmd) {
            case SENDMAIL:
                if (sample == 1) {
                    int uid, rcnt;
                    int rids[10];
                    scanf("%s %d %d", str, &uid, &rcnt);
                    for (int k = 0; k < rcnt; ++k) scanf("%d", &rids[k]);
                    for (int k = 0; k < 30; ++k) {
                        if (str[k] == '\0') break;
                        if (str[k] == '_') str[k] = ' ';
                    }
                    sendMail(str, uid, rcnt, rids);
                } else {
                    scanf("%d", &seed);
                    send_mail(seed);
                }
                break;
            case GETCOUNT:
                scanf("%d %d", &param1, &param2);
                ret = getCount(param1);
                printf("count: %d, %d\n", ret, param2);
                if (ret != param2) answer = 0;
                break;
            case DELETEMAIL:
                if (sample == 1) {
                    int uid;
                    scanf("%d %s %d", &param1, str, &param2);
                    for (int k = 0; k < 30; ++k) {
                        if (str[k] == '\0') break;
                        if (str[k] == '_') str[k] = ' ';
                    }
                    ret = deleteMail(param1, str);
                    if (ret != param2) answer = 0;
                } else {
                    scanf("%d %d %d", &param1, &seed, &param2);
                    ret = delete_mail(param1, seed);
                    printf("delete: %d, %d\n", ret, param2);
                    if (ret != param2) answer = 0;
                }
                break;
            case SEARCHMAIL:
                scanf("%d %s %d", &param1, str, &param2);
                ret = searchMail(param1, str);
                printf("search: %d, %d\n", ret, param2);
                if (ret != param2) answer = 0;
                break;
            default:
                break;
        }
    }

    return answer;
}

int main() {
    setbuf(stdout, NULL);
    freopen("input.txt", "r", stdin);

    int T, Mark;
    scanf("%d %d", &T, &Mark);

    for (int tc = 1; tc <= T; tc++) {
        printf("#%d %d\n", tc, run(Mark));
    }

    return 0;
}

///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
#include <string>
#include <vector>
using namespace std;
int djb2(char *str) {
    size_t hash = 5381;
    while (*str) {
        hash = (hash << 5) + hash + *str;
        str++;
    }
    return hash % 10000;
}
struct Mail;
struct Node {
    int hash;
    char str[10];
    Mail *mail;
    Node *prev, *next;
};
struct Mail {
    char title[100];
    char firstword[10];
    int uID;
    vector<Node *> nodes;
    Mail *prev, *next;
};
Node *nodes[10000];
Mail *mails[1000];
int mailCnt[1000];

void init(int N, int K) {
    for (int i = 0; i < 10000; i++) {
        nodes[i] = nullptr;
    }
    for (int i = 0; i < N; i++) {
        mails[i] = nullptr;
        mailCnt[i] = 0;
    }
}
Node *addNode(char *str, Mail *mail) {
    printf("%s ", str);
    int hash = djb2(str);
    Node *node = new Node;
    node->hash = hash;
    node->mail = mail;
    strcpy(node->str, str);
    node->next = nullptr;
    if (nodes[hash] == nullptr) {
        nodes[hash] = node;
        node->prev = nullptr;
    } else {
        Node *cur = nodes[hash];
        while (cur->next != nullptr) cur = cur->next;
        cur->next = node;
        node->prev = cur;
    }
    return node;
}
void addMail(char subject[], int uID) {
    printf("mail: %s\n", subject);
    Mail *mail = new Mail;
    mail->uID = uID;
    char word[10];
    int i = 0, j = 0;
    while (subject[i] != '\0') {
        while (subject[i] != ' ' && subject[i] != '\0') {
            word[j++] = subject[i++];
        }
        word[j] = '\0';
        strcpy(mail->firstword, word);
        mail->nodes.push_back(addNode(word, mail));
        j = 0;
        if (subject[i] == '\0') break;
        i++;
    }
    strcpy(mail->title, subject);
    mail->next = nullptr;
    if (mails[uID] == nullptr) {
        mails[uID] = mail;
        mail->prev = nullptr;
    } else {
        Mail *cur = mails[uID];
        while (cur->next != nullptr) cur = cur->next;
        mail->prev = cur;
        cur->next = mail;
    }
    printf(" mail done!\n\n");
}

void sendMail(char subject[], int uID, int cnt, int rIDs[]) {
    printf("\nsend %d mail \n", cnt);
    for (int i = 0; i < cnt; i++) {
        printf("%d ", rIDs[i]);
    }
    for (int i = 0; i < cnt; i++) {
        printf("%d(%d): ", rIDs[i], ++mailCnt[rIDs[i]]);
        addMail(subject, rIDs[i]);
        printf("gd");
    }
}
int getCount(int uID) { return mailCnt[uID]; }
int deleteMail(int uID, char subject[]) {
    printf("delete\n");
    int ret = 0;
    char word[10];
    int i = 0, j = 0;
    while (subject[i] != ' ' && subject[i] != '\0') {
        word[j++] = subject[i++];
    }
    word[j] = '\0';
    int hash = djb2(word);
    Node *cur = nodes[hash];
    while (cur != nullptr) {
        if (strcmp(cur->mail->title, subject) == 0 && cur->mail->uID == uID) {
            Mail *mail = cur->mail;
            for (auto it = mail->nodes.begin(); it != mail->nodes.end(); it++) {
                if ((*it)->prev == nullptr) {
                    nodes[(*it)->hash] = (*it)->next;
                } else {
                    (*it)->prev->next = (*it)->next;
                }
                (*it)->next->prev = (*it)->prev;
                delete (*it);
            }
            if (mail->prev == nullptr) {
                mails[mail->uID] = mail->next;
            } else {
                mail->prev->next = mail->next;
            }
            mail->next->prev = mail->prev;
            delete mail;
            cur = nodes[hash];
            ret++;
        }
        cur = cur->next;
    }
    return ret;
}
int searchMail(int uID, char text[]) {
    printf("searchMail: %s\n", text);
    int ret = 0;
    Mail *prevMail = nullptr;
    int hash = djb2(text);
    Node *node = nodes[hash];
    while (node != nullptr) {
        if (node->mail->uID == uID && strcmp(node->str, text) == 0) {
            printf("catch %s", node->str);
            if (prevMail != node->mail) ret++;
            prevMail = node->mail;
        }
        node = node->next;
    }
    return ret;
}
