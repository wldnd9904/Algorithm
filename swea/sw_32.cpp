#include <stdio.h>
#include <string.h>

typedef enum { CMD_INIT, CMD_ADD, CMD_DELETE, CMD_CHANGE, CMD_SEARCH } COMMAND;

typedef enum { NAME, NUMBER, BIRTHDAY, EMAIL, MEMO } FIELD;

typedef struct {
    int count;
    char str[20];
} RESULT;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

extern void InitDB();
extern void Add(char* name, char* number, char* birthday, char* email,
                char* memo);
extern int Delete(FIELD field, char* str);
extern int Change(FIELD field, char* str, FIELD changefield, char* changestr);
extern RESULT Search(FIELD field, char* str, FIELD returnfield);
extern size_t djb2(char*);
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

static int dummy[100];
static int Score, ScoreIdx;
static char name[20], number[20], birthday[20], email[20], memo[20];

static char lastname[10][5] = {"kim",  "lee", "park", "choi", "jung",
                               "kang", "cho", "oh",   "jang", "lim"};
static int lastname_length[10] = {3, 3, 4, 4, 4, 4, 3, 2, 4, 3};

static int mSeed;
static int mrand(int num) {
    mSeed = mSeed * 1103515245 + 37209;
    if (mSeed < 0) mSeed *= -1;
    return ((mSeed >> 8) % num);
}

static void make_field(int seed) {
    int name_length, email_length, memo_length;
    int idx, num;

    mSeed = (unsigned int)seed;

    name_length = 6 + mrand(10);
    email_length = 10 + mrand(10);
    memo_length = 5 + mrand(10);

    num = mrand(10);
    for (idx = 0; idx < lastname_length[num]; idx++)
        name[idx] = lastname[num][idx];
    for (; idx < name_length; idx++) name[idx] = 'a' + mrand(26);
    name[idx] = 0;

    for (idx = 0; idx < memo_length; idx++) memo[idx] = 'a' + mrand(26);
    memo[idx] = 0;

    for (idx = 0; idx < email_length - 6; idx++) email[idx] = 'a' + mrand(26);
    email[idx++] = '@';
    email[idx++] = 'a' + mrand(26);
    email[idx++] = '.';
    email[idx++] = 'c';
    email[idx++] = 'o';
    email[idx++] = 'm';
    email[idx] = 0;

    idx = 0;
    number[idx++] = '0';
    number[idx++] = '1';
    number[idx++] = '0';
    for (; idx < 11; idx++) number[idx] = '0' + mrand(10);
    number[idx] = 0;

    idx = 0;
    birthday[idx++] = '1';
    birthday[idx++] = '9';
    num = mrand(100);
    birthday[idx++] = '0' + num / 10;
    birthday[idx++] = '0' + num % 10;
    num = 1 + mrand(12);
    birthday[idx++] = '0' + num / 10;
    birthday[idx++] = '0' + num % 10;
    num = 1 + mrand(30);
    birthday[idx++] = '0' + num / 10;
    birthday[idx++] = '0' + num % 10;
    birthday[idx] = 0;
}

static void cmd_init() {
    scanf("%d", &ScoreIdx);

    InitDB();
}

static void cmd_add() {
    int seed;
    scanf("%d", &seed);

    make_field(seed);

    Add(name, number, birthday, email, memo);
}

static void cmd_delete() {
    int field, check, result;
    char str[20];
    scanf("%d %s %d", &field, str, &check);

    result = Delete((FIELD)field, str);
    if (result != check) Score -= ScoreIdx;
}

static void cmd_change() {
    int field, changefield, check, result;
    char str[20], changestr[20];
    scanf("%d %s %d %s %d", &field, str, &changefield, changestr, &check);

    result = Change((FIELD)field, str, (FIELD)changefield, changestr);
    if (result != check) Score -= ScoreIdx;
}

static void cmd_search() {
    int field, returnfield, check;
    char str[20], checkstr[20];
    scanf("%d %s %d %s %d", &field, str, &returnfield, checkstr, &check);

    RESULT result = Search((FIELD)field, str, (FIELD)returnfield);

    if (result.count != check ||
        (result.count == 1 && (strcmp(checkstr, result.str) != 0)))
        Score -= ScoreIdx;
}

static void run() {
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        int cmd;
        scanf("%d", &cmd);
        switch (cmd) {
            case CMD_INIT:
                cmd_init();
                break;
            case CMD_ADD:
                cmd_add();
                break;
            case CMD_DELETE:
                cmd_delete();
                break;
            case CMD_CHANGE:
                cmd_change();
                break;
            case CMD_SEARCH:
                cmd_search();
                break;
            default:
                break;
        }
    }
}

static void init() {
    Score = 1000;
    ScoreIdx = 1;
}

int main() {
    setbuf(stdout, NULL);
    freopen("input.txt", "r", stdin);

    int T;
    scanf("%d", &T);
    int TotalScore = 0;
    for (int tc = 1; tc <= T; tc++) {
        init();

        run();

        if (Score < 0) Score = 0;

        TotalScore += Score;
        printf("#%d %d\n", tc, Score);
    }
    printf("TotalScore = %d\n", TotalScore);
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
size_t djb2(char* str) {
    size_t hash = 5381;
    while (*str) {
        hash = (hash << 5) + hash + *str;
        str++;
    }
    return hash % 100000;
}
struct Node {
    FIELD field;
    size_t hash;
    int id;
    Node *prev, *next;
};
struct Record {
    Node* node[5];
    char data[5][20];
};
Node* nodes[100000];      // 해시 버킷 10만개
Record* records[100000];  // 걍 10만개
int recordCnt = 0;

void InitDB() {
    for (int i = 0; i < 100000; i++) {
        nodes[i] = nullptr;
        records[i] = nullptr;
    }
    recordCnt = 0;
}
Node* AddNode(FIELD field, int id, char* str) {
    size_t hash = djb2(str);
    Node* node = new Node;
    node->field = field;
    node->hash = hash;
    node->id = id;
    if (nodes[hash] == nullptr) {
        nodes[hash] = node;
        node->prev = nullptr;
        node->next = nullptr;
    } else {
        Node* cur = nodes[hash];
        while (cur->next != nullptr) cur = cur->next;
        cur->next = node;
        node->prev = cur;
        node->next = nullptr;
    }
    return node;  // 역인덱스
}
void DeleteNode(Node* node) {
    if (node->prev == nullptr) {
        nodes[node->hash] = node->next;
        if (node->next != nullptr) node->next->prev = nullptr;
    } else {
        node->prev->next = node->next;
        if (node->next != nullptr) node->next->prev = node->prev;
    }
    delete node;
}
void DeleteRecord(int id) {
    for (int i = 0; i < 5; i++) {
        DeleteNode(records[id]->node[i]);
    }
}

void Add(char* name, char* number, char* birthday, char* email, char* memo) {
    Record* record = new Record;
    strcpy(record->data[NAME], name);
    strcpy(record->data[NUMBER], number);
    strcpy(record->data[BIRTHDAY], birthday);
    strcpy(record->data[EMAIL], email);
    strcpy(record->data[MEMO], memo);
    record->node[NAME] = AddNode(NAME, recordCnt, name);
    record->node[NUMBER] = AddNode(NUMBER, recordCnt, number);
    record->node[BIRTHDAY] = AddNode(BIRTHDAY, recordCnt, birthday);
    record->node[EMAIL] = AddNode(EMAIL, recordCnt, email);
    record->node[MEMO] = AddNode(MEMO, recordCnt, memo);
    records[recordCnt++] = record;
}

int Delete(FIELD field, char* str) {
    int ret = 0;
    size_t hash = djb2(str);
    Node* cur = nodes[hash];
    while (cur != nullptr) {
        if (cur->field == field &&
            strcmp(records[cur->id]->data[cur->field], str) == 0) {
            Node* next = cur->next;
            DeleteRecord(cur->id);
            cur = next;
            ret++;
        } else {
            cur = cur->next;
        }
    }
    return ret;
}

int Change(FIELD field, char* str, FIELD changefield, char* changestr) {
    int ret = 0;
    size_t hash = djb2(str);
    Node* cur = nodes[hash];
    while (cur != nullptr) {
        if (cur->field == field &&
            strcmp(records[cur->id]->data[field], str) == 0) {
            Node* next = cur->next;
            int id = cur->id;
            DeleteNode(records[id]->node[changefield]);
            strcpy(records[id]->data[changefield], changestr);
            records[id]->node[changefield] =
                AddNode(changefield, id, changestr);
            cur = next;
            ret++;
        } else {
            cur = cur->next;
        }
    }
    return ret;
}

RESULT Search(FIELD field, char* str, FIELD ret_field) {
    RESULT result;
    int ret = 0;
    size_t hash = djb2(str);
    Node* cur = nodes[hash];
    while (cur != nullptr) {
        if (cur->field == field &&
            strcmp(records[cur->id]->data[field], str) == 0) {
            if (++ret == 1)
                strcpy(result.str, records[cur->id]->data[ret_field]);
        }
        cur = cur->next;
    }
    result.count = ret;
    return result;
}