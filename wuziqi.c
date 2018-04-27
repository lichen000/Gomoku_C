//
// Created by mangolost on 2018/4/26.
//

#include <stdio.h>
#include <malloc.h>
#include "common.h"

struct Loc {
    int row; //row表示行，col表示列
    int col;
};

struct Node {
    struct Loc loc;
    int user;
};

const int LineNum = 15;

struct Node nodes[225];

int finished = 0;
int currentTurn = 0;
int currentUser = 1;

/**
 *
 * @param row
 * @param col
 * @return
 */
int getExistNodes(int row, int col) {
    for (int i = 0; i < currentTurn; i++) {
        struct Node node = nodes[i];
        if (node.loc.row == row && node.loc.col == col) {
            return node.user;
        }
    }
    return 0;
}

/**
 *
 * @param nodes
 */
void drawQipan() {
    for (int i = 0; i <= LineNum + 1; i++) {
        if (i == 0 || i == LineNum + 1) {
            printf(" X ");
        } else {
            printf("%2d ", i);
        }
    }
    printf("\n");
    for (int i = 1; i <= LineNum; i++) {
        printf("%2d ", i);
        for (int j = 1; j <= LineNum; j++) {
            //检查i,j位置上是否有棋子了
            int flag = getExistNodes(i,j);
            switch (flag) {
                case 0:
                    printf(" * ");
                    break;
                case 1:
                    printf(" @ ");
                    break;
                case 2:
                    printf(" + ");
                    break;
                default:
                    break;
            }
        }
        printf("%2d ", i);
        printf("\n");
    }
    for (int i = 0; i <= LineNum + 1; i++) {
        if (i == 0 || i == LineNum + 1) {
            printf(" X ");
        } else {
            printf("%2d ", i);
        }
    }
    printf("\n");
}

/**
 *
 * @param row
 * @param col
 * @return
 */
int checkInput(int row, int col) {
    if (row >=1 && row <=15 && col >=1 && col <= 15) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * 判断棋盘上某个位子是否落子及落子属于谁
 * 0：未落子，1：玩家1， 2：玩家2
 * @param loc
 * @return
 */
int getLocOwner(struct Loc loc) {
    return getExistNodes(loc.row, loc.col);
}

/**
 * 胜利条件1：西北向胜利，落子与其左上方4个子连成一线
 * 设落子为(row,col),则(row-1,col-1),(row-2,col-2),(row-3,col-3),(row-4,col-4)都被落子方占领
 * @return
 */
int checkWinCase1() {
    struct Node currentNode = nodes[currentTurn];
    int row = currentNode.loc.row;
    int col = currentNode.loc.col;
    if (row < 5 || col < 5) {
        return 0; //如果row或者col小于5，显然没有足够空间达成胜利条件
    }
    int user = currentNode.user;
    struct Loc loc1 = {row-1, col-1}, loc2 = {row-2,col-2}, loc3={row-3,col-3}, loc4={row-4,col-4};

    if (getLocOwner(loc1) == user
        && getLocOwner(loc2) == user
        && getLocOwner(loc3) == user
        && getLocOwner(loc4) == user ) {
        return 1;
    }

    return 0;
}

/**
 * 胜利条件2：东北向胜利，落子与其右上方4个子连成一线
 * 设落子为(row,col),则(row-1,col+1),(row-2,col+2),(row-3,col+3),(row-4,col+4)都被落子方占领
 * @return
 */
int checkWinCase2() {
    struct Node currentNode = nodes[currentTurn];
    int row = currentNode.loc.row;
    int col = currentNode.loc.col;
    if (row < 5 || col > 11) {
        return 0; //显然没有足够空间达成胜利条件
    }
    int user = currentNode.user;
    struct Loc loc1 = {row-1, col+1}, loc2 = {row-2,col+2}, loc3={row-3,col+3}, loc4={row-4,col+4};

    if (getLocOwner(loc1) == user
        && getLocOwner(loc2) == user
        && getLocOwner(loc3) == user
        && getLocOwner(loc4) == user ) {
        return 1;
    }

    return 0;
}

/**
 * 胜利条件3：西南向胜利，落子与其左下方4个子连成一线
 * 设落子为(row,col),则(row+1,col-1),(row+2,col-2),(row+3,col-3),(row+4,col-4)都被落子方占领
 * @return
 */
int checkWinCase3() {
    struct Node currentNode = nodes[currentTurn];
    int row = currentNode.loc.row;
    int col = currentNode.loc.col;
    if (row > 11 || col < 5) {
        return 0; //显然没有足够空间达成胜利条件
    }
    int user = currentNode.user;
    struct Loc loc1 = {row+1, col-1}, loc2 = {row+2,col-2}, loc3={row+3,col-3}, loc4={row+4,col-4};

    if (getLocOwner(loc1) == user
        && getLocOwner(loc2) == user
        && getLocOwner(loc3) == user
        && getLocOwner(loc4) == user ) {
        return 1;
    }

    return 0;
}

/**
 * 胜利条件4：东南向胜利，落子与其右下方4个子连成一线
 * 设落子为(row,col),则(row+1,col+1),(row+2,col+2),(row+3,col+3),(row+4,col+4)都被落子方占领
 * @return
 */
int checkWinCase4() {
    struct Node currentNode = nodes[currentTurn];
    int row = currentNode.loc.row;
    int col = currentNode.loc.col;
    if (row > 11 || col > 11) {
        return 0; //显然没有足够空间达成胜利条件
    }
    int user = currentNode.user;
    struct Loc loc1 = {row+1, col+1}, loc2 = {row+2,col+2}, loc3={row+3,col+3}, loc4={row+4,col+4};

    if (getLocOwner(loc1) == user
        && getLocOwner(loc2) == user
        && getLocOwner(loc3) == user
        && getLocOwner(loc4) == user ) {
        return 1;
    }

    return 0;
}

/**
 * 胜利条件5：正北向胜利，落子与其上方4个子连成一线
 * 设落子为(row,col),则(row-1,col),(row-2,col),(row-3,col),(row-4,col)都被落子方占领
 * @return
 */
int checkWinCase5() {
    struct Node currentNode = nodes[currentTurn];
    int row = currentNode.loc.row;
    int col = currentNode.loc.col;
    if (row < 5) {
        return 0; //显然没有足够空间达成胜利条件
    }
    int user = currentNode.user;
    struct Loc loc1 = {row-1, col}, loc2 = {row-2,col}, loc3={row-3,col}, loc4={row-4,col};

    if (getLocOwner(loc1) == user
        && getLocOwner(loc2) == user
        && getLocOwner(loc3) == user
        && getLocOwner(loc4) == user ) {
        return 1;
    }

    return 0;
}

/**
 * 胜利条件6：正南向胜利，落子与其下方4个子连成一线
 * 设落子为(row,col),则(row+1,col),(row+2,col),(row+3,col),(row+4,col)都被落子方占领
 * @return
 */
int checkWinCase6() {
    struct Node currentNode = nodes[currentTurn];
    int row = currentNode.loc.row;
    int col = currentNode.loc.col;
    if (row > 11) {
        return 0; //显然没有足够空间达成胜利条件
    }
    int user = currentNode.user;
    struct Loc loc1 = {row+1, col}, loc2 = {row+2,col}, loc3={row+3,col}, loc4={row+4,col};

    if (getLocOwner(loc1) == user
        && getLocOwner(loc2) == user
        && getLocOwner(loc3) == user
        && getLocOwner(loc4) == user ) {
        return 1;
    }

    return 0;
}

/**
 * 胜利条件7：正西向胜利，落子与其左方4个子连成一线
 * 设落子为(row,col),则(row,col-1),(row,col-2),(row,col-3),(row,col-4)都被落子方占领
 * @return
 */
int checkWinCase7() {
    struct Node currentNode = nodes[currentTurn];
    int row = currentNode.loc.row;
    int col = currentNode.loc.col;
    if (col < 5) {
        return 0; //显然没有足够空间达成胜利条件
    }
    int user = currentNode.user;
    struct Loc loc1 = {row, col-1}, loc2 = {row,col-2}, loc3={row,col-3}, loc4={row,col-4};

    if (getLocOwner(loc1) == user
        && getLocOwner(loc2) == user
        && getLocOwner(loc3) == user
        && getLocOwner(loc4) == user ) {
        return 1;
    }

    return 0;
}

/**
 * 胜利条件6：正东向胜利，落子与其右方4个子连成一线
 * 设落子为(row,col),则(row,col+1),(row,col+2),(row,col+3),(row,col+4)都被落子方占领
 * @return
 */
int checkWinCase8() {
    struct Node currentNode = nodes[currentTurn];
    int row = currentNode.loc.row;
    int col = currentNode.loc.col;
    if (col > 11) {
        return 0; //显然没有足够空间达成胜利条件
    }
    int user = currentNode.user;
    struct Loc loc1 = {row, col+1}, loc2 = {row,col+2}, loc3={row,col+3}, loc4={row,col+4};

    if (getLocOwner(loc1) == user
        && getLocOwner(loc2) == user
        && getLocOwner(loc3) == user
        && getLocOwner(loc4) == user ) {
        return 1;
    }

    return 0;
}

/**
 *
 * @return
 */
int calFinished() {

    if (currentTurn < 8) {
        return 0; //前8个棋子不可能获胜
    }

    if (checkWinCase1() == 1
        || checkWinCase2() == 1
        || checkWinCase3() == 1
        || checkWinCase4() == 1
        || checkWinCase5() == 1
        || checkWinCase6() == 1
        || checkWinCase7() == 1
        || checkWinCase8() == 1) {
        return 1; //满足8种胜利情况中的1种，判定胜利
    }

    return 0; //todo
}

/**
 *
 */
void runWuziqi() {

    setbuf(stdout,NULL);

    drawQipan();

    while (finished == 0) {
        printf("第%d回合请选手%d下棋\n", currentTurn + 1, currentUser);
        int row;
        int col;
        scanf("%d %d", &row, &col);
        while (checkInput(row, col) == 0) {
            printf("落子位置不合法，请重新输入\n");
            scanf("%d %d", &row, &col);
        }
        struct Loc loc = {row, col};
        struct Node node = {loc, currentUser};
        nodes[currentTurn] = node;
        printf("第%d回合，选手%d落子于(%d, %d)\n", currentTurn + 1, currentUser, row, col);
        finished = calFinished();
        if (finished == 1) {
            printf("恭喜，选手%d获胜!\n", currentUser);
            currentTurn ++;
            drawQipan();
            break;
        } else {
            currentTurn ++;
            currentUser = 3 - currentUser;
            drawQipan();

        }
    }
}
