#include <iostream>
#include<vector>
#include<random>
#include<algorithm>
#include<windows.h>
#pragma comment(lib,"winmm")

/***************
オープニング画面
***************/
int OPENING() {
    int cursor = 0;
    printf("->Game Start\n  Music\n  Quit\n");
    while (true) {
        if ((GetAsyncKeyState(VK_DOWN) & 0x8000) && (GetAsyncKeyState('T') & 0x8000)) return 99;
        if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 0, 0 });
            ++cursor; cursor %= 3;
            if (cursor == 0) {
                printf("->Game Start\n  Music\n  Quit\n");
            }
            else if (cursor == 1) {
                printf("  Game Start\n->Music\n  Quit\n");
            }
            else if (cursor == 2) {
                printf("  Game Start\n  Music\n->Quit\n");
            }
            Sleep(100);
        }
        if (GetAsyncKeyState(VK_UP) & 0x8000) {
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 0, 0 });
            --cursor; cursor = (cursor + 3) % 3;
            if (cursor == 0) {
                printf("->Game Start\n  Music\n  Quit\n");
            }
            else if (cursor == 1) {
                printf("  Game Start\n->Music\n  Quit\n");
            }
            else if (cursor == 2) {
                printf("  Game Start\n  Music\n->Quit\n");
            }
            Sleep(100);
        }
        if (cursor == 0 && GetAsyncKeyState(VK_RETURN) & 0x8000) {
            return 1;
        }
        else if (cursor == 2 && GetAsyncKeyState(VK_RETURN) & 0x8000) {
            return 0;
        }
        else if (cursor == 1 && GetAsyncKeyState(VK_RETURN) & 0x8000) {
            return -1;
        }
        Sleep(100);
    }
}

/***********
音楽再生画面
***********/
int Music_Room() {
    int cursor = 0;
    system("cls");
    printf("->Discode Paradise\n  Old Cosmic\n  Moon Falls\n  quit\n");
    Sleep(100);
    while (true) {
        if (GetAsyncKeyState(VK_DOWN) & 0x8000 && GetAsyncKeyState('T') & 0x8000) {
            system("cls");
            printf("->Weekend");
            PlaySound(L"BGM/Weekend.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
            Sleep(100);
        }
        if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 0, 0 });
            ++cursor; cursor %= 4;
            if (cursor == 0) {
                printf("->Discode Paradise\n  Old Cosmic\n   Moon Falls\n  quit\n");
            }
            else if (cursor == 1) {
                printf("  Discode Paradise\n->Old Cosmic\n   Moon Falls\n  quit\n");
            }
            else if (cursor == 2) {
                printf("  Discode Paradise\n  Old Cosmic\n-> Moon Falls\n  quit\n");
            }
            else if (cursor == 3) {
                printf("  Discode Paradise\n  Old Cosmic\n   Moon Falls\n->quit\n");
            }
            Sleep(100);
        }
        if (GetAsyncKeyState(VK_UP) & 0x8000) {
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 0, 0 });
            --cursor; cursor = (cursor + 4) % 4;
            if (cursor == 0) {
                printf("->Discode Paradise\n  Old Cosmic\n   Moon Falls\n  quit\n");
            }
            else if (cursor == 1) {
                printf("  Discode Paradise\n->Old Cosmic\n   Moon Falls\n  quit\n");
            }
            else if (cursor == 2) {
                printf("  Discode Paradise\n  Old Cosmic\n-> Moon Falls\n  quit\n");
            }
            else if (cursor == 3) {
                printf("  Discode Paradise\n  Old Cosmic\n  Moon Falls\n\=>quit\n");
            }
            Sleep(100);
        }
        if (cursor == 0 && GetAsyncKeyState(VK_RETURN) & 0x8000) {
            PlaySound(NULL, 0, 0);
            PlaySound(L"BGM/Discode_Paradise.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
        }
        else if (cursor == 2 && GetAsyncKeyState(VK_RETURN) & 0x8000) {
            PlaySound(NULL, 0, 0);
            PlaySound(L"BGM/Moon_Falls.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
        }
        else if (cursor == 1 && GetAsyncKeyState(VK_RETURN) & 0x8000) {
            PlaySound(NULL, 0, 0);
            PlaySound(L"BGM/old_cosmic.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
        }
        else if (cursor == 3 && GetAsyncKeyState(VK_RETURN) & 0x8000) {
            system("cls");
            Sleep(100);
            return 0;
        }
        Sleep(100);
    }
}

/*************
ステージの作成
*************/
std::vector < std::vector<int>> make_field() {
    std::vector<std::vector<int>> field(20, std::vector<int>(70));
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 70; ++j) {
            if (i == 0 || j == 0 || i == 19 || j == 69) {
                field.at(i).at(j) = -5;
            }
        }
    }
    return field;
}

/*ステージの表示*/
void print_field(std::vector<std::vector<int>> const field) {
    int n = field.size(), m = field.at(0).size();
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 0, 0 });
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (field.at(i).at(j) == -1) printf("@");
            else if (field.at(i).at(j) == -5) printf("#");
            else if (field.at(i).at(j) > 0) printf("+");
            else if (field.at(i).at(j) == -2) printf("*");
            else if (field.at(i).at(j) == -3) printf("\x1b[31m*\x1b[39m"); 
            else printf(" ");
        }
        puts("");
    }
}

/*敵の生成*/
void gen_boss(std::vector<std::vector<int>>& field, const int i, const int j, const int n) {field.at(j).at(i) = n;}

/*弾の挙動*/
void update_bullet(std::vector<std::vector<int>>& field, int& x, int& y, bool& UP, bool& RIGHT) {
    field.at(y).at(x) = 0;
    /*上方向に進んでいるとき*/
    if (y > 0 && y < 19 && x > 0 && x < 69)
    if (UP) {
        /*右方向に進んでいるとき*/
        if (RIGHT) {
            /*上に衝突*/
            if ((field.at(y - 1).at(x) != 0 && field.at(y - 1).at(x) != -1 && field.at(y - 1).at(x) != -2) && (field.at(y).at(x + 1) == 0 || field.at(y).at(x + 1) == -1 || field.at(y).at(x + 1) == -2)) {
                UP = false;
                field.at(y + 1).at(x + 1) = -3;
                ++y; ++x;
            }
            /*右に衝突*/
            else if ((field.at(y - 1).at(x) == 0 || field.at(y - 1).at(x) == -1 || field.at(y - 1).at(x) == -2) && (field.at(y).at(x + 1) != 0 && field.at(y).at(x + 1) != -1 && field.at(y).at(x + 1) != -2)) {
                RIGHT = false;
                field.at(y - 1).at(x - 1) = -3;
                --y; --x;
            }
            /*右上角に衝突*/
            else if ((field.at(y - 1).at(x) != 0 && field.at(y - 1).at(x) != -1 && field.at(y - 1).at(x) != -2) && (field.at(y).at(x + 1) != 0 && field.at(y).at(x + 1) != -1 && field.at(y).at(x + 1) != -2)) {
                UP = false; RIGHT = false;
                field.at(y).at(x) = -3;
            }
            else if ((field.at(y - 1).at(x + 1) != 0 && field.at(y - 1).at(x + 1) != -1 && field.at(y - 1).at(x + 1) != -2)) {
                UP = false; RIGHT = false;
                field.at(y).at(x) = -3;
            }
            /*衝突しない*/
            else {
                field.at(y - 1).at(x + 1) = -3;
                --y; ++x;
            }
        }
        /*左に進んでいるとき*/
        else {
            /*上に衝突*/
            if ((field.at(y - 1).at(x) != 0 && field.at(y - 1).at(x) != -1 && field.at(y - 1).at(x) != -2) && (field.at(y).at(x - 1) == 0 || field.at(y).at(x - 1) == -1 || field.at(y).at(x - 1) == -2)) {
                UP = false;
                field.at(y + 1).at(x - 1) = -3;
                ++y; --x;
            }

            /*左に衝突*/
            else if ((field.at(y - 1).at(x) == 0 || field.at(y - 1).at(x) == -1 || field.at(y - 1).at(x) == -2) && (field.at(y).at(x - 1) != 0 && field.at(y).at(x - 1) != -1 && field.at(y).at(x - 1) != -2)) {
                RIGHT = true;
                field.at(y - 1).at(x + 1) = -3;
                --y; ++x;
            }

            /*左上に衝突*/
            else if ((field.at(y - 1).at(x) != 0 && field.at(y - 1).at(x) != -1 && field.at(y - 1).at(x) != -2) && (field.at(y).at(x - 1) != 0 && field.at(y).at(x - 1) != -1 && field.at(y).at(x - 1) != -2)) {
                UP = false; RIGHT = true;
                field.at(y).at(x) = -3;
            }

            else if (field.at(y - 1).at(x - 1) != 0 && field.at(y - 1).at(x - 1) != -1 && field.at(y - 1).at(x - 1) != -2) {
                UP = false; RIGHT = true;
                field.at(y).at(x) = -3;
            }

            /*衝突しない*/
            else {
                field.at(y - 1).at(x - 1) = -3;
                --y; --x;
            }
        }
    }
    /*下に進んでいるとき*/
    else {
        /*右方向に進んでいるとき*/
        if(y < 19)
        if (RIGHT) {
            if ((field.at(y + 1).at(x) != 0 && field.at(y + 1).at(x) != -1 && field.at(y + 1).at(x) != -2) && (field.at(y).at(x + 1) == 0 || field.at(y).at(x + 1) == -1 || field.at(y).at(x + 1) == -2) && (field.at(y - 1).at(x + 1) == 0 || field.at(y - 1).at(x + 1) == -1 || field.at(y - 1).at(x + 1) == -2)) {
                UP = true;
                field.at(y - 1).at(x + 1) = -3;
                --y; ++x;
            }
            else if ((field.at(y + 1).at(x) == 0 || field.at(y + 1).at(x) == -1 || field.at(y + 1).at(x) == -2) && (field.at(y).at(x + 1) != 0 && field.at(y).at(x + 1) != -1 && field.at(y).at(x + 1) != -2) && (field.at(y + 1).at(x - 1) == 0 || field.at(y + 1).at(x - 1) == -1 || field.at(y + 1).at(x - 1) == -2)) {
                RIGHT = false;
                field.at(y + 1).at(x - 1) = -3;
                ++y; --x;
            }
            else if ((field.at(y + 1).at(x) != 0 && field.at(y + 1).at(x) != -1 && field.at(y + 1).at(x) != -2) && (field.at(y).at(x + 1) != 0 && field.at(y).at(x + 1) != -1 && field.at(y).at(x + 1) != -2) && (field.at(y).at(x) == 0 || field.at(y).at(x) == -1 || field.at(y).at(x) == -2)) {
                UP = true; RIGHT = false;
                field.at(y).at(x) = -3;
            }
            else if (field.at(y + 1).at(x + 1) != 0 && field.at(y + 1).at(x + 1) != -1 && field.at(y + 1).at(x + 1) != -2) {
                UP = true; RIGHT = false;
                field.at(y).at(x) = -3;
            }
            else {
                field.at(y + 1).at(x + 1) = -3;
                ++y; ++x;
            }
        }
        /*左に進んでいるとき*/
        else {
            if ((field.at(y + 1).at(x) != 0 && field.at(y + 1).at(x) != -1 && field.at(y + 1).at(x) != -2) && (field.at(y).at(x - 1) == 0 || field.at(y).at(x - 1) == -1 || field.at(y).at(x - 1) == -2) && (field.at(y - 1).at(x - 1) == 0 || field.at(y - 1).at(x - 1) == -1 || field.at(y - 1).at(x - 1) == -2)) {
                UP = true;
                field.at(y - 1).at(x - 1) = -3;
                --y; --x;
            }
            else if ((field.at(y + 1).at(x) == 0 || field.at(y + 1).at(x) == -1 || field.at(y + 1).at(x) == -2) && (field.at(y).at(x - 1) != 0 && field.at(y).at(x - 1) != -1 && field.at(y).at(x - 1) != -2) && (field.at(y + 1).at(x + 1) == 0 || field.at(y + 1).at(x + 1) == -1 || field.at(y + 1).at(x + 1) == -2)) {
                RIGHT = true;
                field.at(y + 1).at(x + 1) = -3;
                ++y; ++x;
            }
            else if ((field.at(y + 1).at(x) != 0 && field.at(y + 1).at(x) != -1 && field.at(y + 1).at(x) != -2) && (field.at(y).at(x - 1) != 0 && field.at(y).at(x - 1) != -1 && field.at(y).at(x - 1) != -2) && (field.at(y).at(x) == 0 || field.at(y).at(x) == -1 || field.at(y).at(x) == -2)) {
                UP = true; RIGHT = true;
                field.at(y).at(x) = -3;
            }
            else if (field.at(y + 1).at(x - 1) != 0 && field.at(y + 1).at(x - 1) != -1 && field.at(y + 1).at(x - 1) != -2) {
                UP = true; RIGHT = true;
                field.at(y).at(x) = -3;
            }
            else {
                field.at(y + 1).at(x - 1) = -3;
                ++y; --x;
            }
        }
    }
}

/*自機の挙動*/
int Move_Player(std::vector<std::vector<int>>& field, int& x, int& y) {
    int n = field.size(), m = field.at(0).size();

    if (field.at(y).at(x) != -1) return -1;

    if (GetAsyncKeyState(VK_UP) & 0x8000) {
        if (y != 1) {
            field.at(y).at(x) = 0;
            field.at(y - 1).at(x) = -1;
            --y;
            return 1;
        }
    }
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
        if (x != m - 2) {
            field.at(y).at(x) = 0;
            field.at(y).at(x + 1) = -1;
            ++x;
            return 1;
        }
    }
    if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
        if (y != n - 2) {
            field.at(y).at(x) = 0;
            field.at(y + 1).at(x) = -1;
            ++y;
            return 1;
        }
    }
    if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
        if (x != 1) {
            field.at(y).at(x) = 0;
            field.at(y).at(x - 1) = -1;
            --x;
            return 1;
        }
    }
    return 0;
}

/*弾の発射*/
void rel_bullet(std::vector<std::vector<int>>& field, const int x, const int y) {
    if (GetAsyncKeyState(0x5A) & 0x8000) {
        if (y != 1) field.at(y - 1).at(x) = -2;
    }
}

/*弾の挙動*/
void update_bullet_player(std::vector<std::vector<int>>& field) {
    int n = field.size(), m = field.at(0).size();
    for (int i = 1; i <= n - 2; ++i) {
        for (int j = 1; j <= m - 2; ++j) {
            if (field.at(i).at(j) == -2) {
                field.at(i).at(j) = 0;
                if (field.at(i - 1).at(j) == 0) field.at(i - 1).at(j) = -2;
                else if (field.at(i - 1).at(j) > 0) --field.at(i - 1).at(j);
            }
        }
    }
}

/*ステージ*/
bool stage_1() {
    /*初期化*/
    bool update_flag = false, UP = true, RIGHT = true, UP_bul = true, RIGHT_bul = true, UP_bul2 = true, RIGHT_bul2 = true;
    int move_flag = 0, update_time = 0, move_count = 0, y_ball, x_ball, x_bul, y_bul, x_bul2, y_bul2;
    std::vector<std::vector<int>> field = make_field();
    int n = field.size(), m = field.at(0).size(), counter = 0, x, y, m2 = m / 2;
    x = m / 2; y = n / 2;
    field.at(y).at(x) = -1;

    print_field(field);
    Sleep(100);
    printf("Start to press spacekey.");
    while (true) {
        if (GetAsyncKeyState(VK_SPACE) & 0x8000) break;
    }
    system("cls");

    /*Music Start*/
    PlaySound(L"BGM/Discode_Paradise.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);

    y_ball = 5; x_ball = m2;
    y_bul = n - 2; x_bul = m2;
    x_bul2 = m2; y_bul2 = 7;
    field.at(y_ball).at(x_ball) = -2;
    field.at(y_bul).at(x_bul) = -3;
    field.at(y_bul2).at(x_bul2) = -3;
    field.at(1).at(m2) = 10;
    field.at(2).at(m2) = 50;
    field.at(3).at(m2) = 10;
    field.at(2).at(m2 - 1) = 10;
    field.at(2).at(m2 + 1) = 10;

    print_field(field);
    while (true) {
        /*自機の挙動*/
        Move_Player(field, x, y);

        /*発射*/
        rel_bullet(field, x, y);
        update_bullet_player(field);

        /*弾の挙動*/
        update_bullet(field, x_ball, y_ball, UP, RIGHT);
        update_bullet(field, x_bul, y_bul, UP_bul, RIGHT_bul);
        update_bullet(field, x_bul2, y_bul2, UP_bul2, RIGHT_bul2);

        //あたり判定
        if (field.at(y).at(x) != -1) { 
            field.clear();
            field.shrink_to_fit();
            return false; 
        }
        if (field.at(1).at(m2) == -1 || field.at(2).at(m2) == -1 || field.at(3).at(m2) == -1 || field.at(2).at(m2 - 1) == -1 || field.at(2).at(m2 + 1) == -1) { 
            field.clear();
            field.shrink_to_fit();
            return false; 
        }

        /*クリア判定*/
        if (field.at(1).at(m2) <= 0 && field.at(2).at(m2) <= 0 && field.at(3).at(m2) <= 0 && field.at(2).at(m2 - 1) <= 0 && field.at(2).at(m2 + 1) <= 0)break;

        /*場の表示*/
        print_field(field);

        /*およそ60fps*/
        Sleep(16.667);
    }
    field.clear();
    field.shrink_to_fit();
    return true;
}

/*ステージ2*/
bool stage_2() {
    /*初期化*/
    bool update_flag = false;
    int move_flag = 0, update_time = 0, move_count = 0;
    std::vector<std::vector<int>> field = make_field();
    int n = field.size(), m = field.at(0).size(), counter = 0, x, y, m2 = m / 2, n2 = n / 2;
    std::vector<int> y_bul = { n2, n2, n2, n2, n2, n2 ,n2, n2, n2, n2, n2, n2, n2 }, x_bul = {m2 + 1, m2 - 1, m2 + 1, m2 - 1, m2 + 2, m2 - 2, m2 + 2, m2 - 2, m2 + 3, m2 - 3, m2 + 3, m2 - 3, m2 + 5};
    std::vector<bool> rtmp = { true, false, false, true, true, false, false, true, true, false, false, true, false }, utmp = { true, false, false, true, true, false, false, true, true, false, false, true, false };
    bool RIGHT[13], UP[13];
    x = m2; y = n - 2;
    field.at(y).at(x) = -1;

    /*弾の動く方向の乱数化*/
    std::random_device seed_gen;
    std::mt19937 engine(seed_gen());
    std::shuffle(rtmp.begin(), rtmp.end(), engine);
    std::random_device seed_gen1;
    std::mt19937 engine1(seed_gen1());
    std::shuffle(utmp.begin(), utmp.end(), engine1);
    for (int i = 0; i < 13; ++i) {RIGHT[i] = rtmp.at(i); UP[i] = utmp.at(i);}

    print_field(field);
    Sleep(100);
    printf("Start to press spacekey.");
    while (true) {
        if (GetAsyncKeyState(VK_SPACE) & 0x8000) break;
    }
    system("cls");
    /*Music Start*/
    PlaySound(L"BGM/Moon_Falls.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
    
    for (int i = 0; i < 13; ++i) {
        field.at(y_bul.at(i)).at(x_bul.at(i)) = -3;
    }
    field.at(1).at(m2) = 100;
    field.at(2).at(m2) = 500;
    field.at(3).at(m2) = 100;
    field.at(2).at(m2 - 1) = 100;
    field.at(2).at(m2 + 1) = 100;

    print_field(field);
    while (true) {
        /*自機の挙動*/
        Move_Player(field, x, y);

        /*発射*/
        rel_bullet(field, x, y);
        update_bullet_player(field);

        /*弾の挙動*/
        for (int i = 0; i < 13; ++i) {
            update_bullet(field, x_bul.at(i), y_bul.at(i), UP[i], RIGHT[i]);
        }

        //あたり判定
        if (field.at(y).at(x) != -1) { 
            field.clear();
            field.shrink_to_fit();
            y_bul.clear();
            y_bul.shrink_to_fit();
            rtmp.clear();
            rtmp.shrink_to_fit();
            utmp.clear();
            utmp.shrink_to_fit();
            return false; 
        }
        if (field.at(1).at(m2) == -1 || field.at(2).at(m2) == -1 || field.at(3).at(m2) == -1 || field.at(2).at(m2 - 1) == -1 || field.at(2).at(m2 + 1) == -1) { 
            field.clear();
            field.shrink_to_fit();
            y_bul.clear();
            y_bul.shrink_to_fit();
            rtmp.clear();
            rtmp.shrink_to_fit();
            utmp.clear();
            utmp.shrink_to_fit();
            return false; 
        }

        /*クリア判定*/
        if (field.at(1).at(m2) <= 0 && field.at(2).at(m2) <= 0 && field.at(3).at(m2) <= 0 && field.at(2).at(m2 - 1) <= 0 && field.at(2).at(m2 + 1) <= 0)break;

        /*場の表示*/
        print_field(field);

        /*およそ60fps*/
        Sleep(16.667);
    }
    field.clear();
    field.shrink_to_fit();
    y_bul.clear();
    y_bul.shrink_to_fit();
    rtmp.clear();
    rtmp.shrink_to_fit();
    utmp.clear();
    utmp.shrink_to_fit();
    return true;
}

/*ステージ2*/
bool stage_3() {
    /*初期化*/
    bool update_flag = false;
    int move_flag = 0, update_time = 0, move_count = 0;
    std::vector<std::vector<int>> field = make_field();
    int n = field.size(), m = field.at(0).size(), counter = 0, x, y, m2 = m / 2, n2 = n / 2;
    std::vector<int> y_bul = { n2, n2, n2, n2, n2, n2 ,n2, n2, n2, n2, n2, n2, n2, n2, n2, n2, n2, n2, n2 ,n2, n2, n2, n2, n2, n2, n2 }, x_bul = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26};
    std::vector<bool> rtmp = { true, false, false, true, true, false, false, true, true, false, false, true, false, true, false, false, true, true, false, false, true, true, false, false, true, false }, utmp = { true, false, false, true, true, false, false, true, true, false, false, true, false, true, false, false, true, true, false, false, true, true, false, false, true, false };
    bool RIGHT[26], UP[26];
    x = m2; y = n - 2;
    field.at(y).at(x) = -1;

    /*弾の動く方向の乱数化*/
    std::random_device seed_gen;
    std::mt19937 engine(seed_gen());
    std::shuffle(rtmp.begin(), rtmp.end(), engine);
    std::random_device seed_gen1;
    std::mt19937 engine1(seed_gen1());
    std::shuffle(utmp.begin(), utmp.end(), engine1);
    for (int i = 0; i < 26; ++i) { RIGHT[i] = rtmp.at(i); UP[i] = utmp.at(i); }

    print_field(field);
    Sleep(100);
    printf("Start to press spacekey.");
    while (true) {
        if (GetAsyncKeyState(VK_SPACE) & 0x8000) break;
    }
    system("cls");
    PlaySound(L"BGM/old_cosmic.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);

    for (int i = 0; i < 26; ++i) {
        field.at(y_bul.at(i)).at(x_bul.at(i)) = -3;
    }
    field.at(1).at(m2) = 500;
    field.at(2).at(m2) = 1000;
    field.at(3).at(m2) = 500;
    field.at(2).at(m2 - 1) = 500;
    field.at(2).at(m2 + 1) = 500;

    print_field(field);
    while (true) {
        /*自機の挙動*/
        Move_Player(field, x, y);

        /*発射*/
        rel_bullet(field, x, y);
        update_bullet_player(field);

        /*弾の挙動*/
        for (int i = 0; i < 26; ++i) {
            update_bullet(field, x_bul.at(i), y_bul.at(i), UP[i], RIGHT[i]);
        }

        //あたり判定
        if (field.at(y).at(x) != -1) { 
            field.clear();
            field.shrink_to_fit();
            y_bul.clear();
            y_bul.shrink_to_fit();
            rtmp.clear();
            rtmp.shrink_to_fit();
            utmp.clear();
            utmp.shrink_to_fit();
            return false; 
        }
        if (field.at(1).at(m2) == -1 || field.at(2).at(m2) == -1 || field.at(3).at(m2) == -1 || field.at(2).at(m2 - 1) == -1 || field.at(2).at(m2 + 1) == -1) { 
            field.clear();
            field.shrink_to_fit();
            y_bul.clear();
            y_bul.shrink_to_fit();
            rtmp.clear();
            rtmp.shrink_to_fit();
            utmp.clear();
            utmp.shrink_to_fit();
            return false; 
        }

        /*クリア判定*/
        if (field.at(1).at(m2) <= 0 && field.at(2).at(m2) <= 0 && field.at(3).at(m2) <= 0 && field.at(2).at(m2 - 1) <= 0 && field.at(2).at(m2 + 1) <= 0)break;

        /*場の表示*/
        print_field(field);

        /*およそ60fps*/
        Sleep(16.667);
    }
    field.clear();
    field.shrink_to_fit();
    y_bul.clear();
    y_bul.shrink_to_fit();
    rtmp.clear();
    rtmp.shrink_to_fit();
    utmp.clear();
    utmp.shrink_to_fit();
    return true;
}

/*exステージ*/
bool stage_Ex() {
    /*初期化*/
    bool update_flag = false;
    int move_flag = 0, update_time = 0, move_count = 0;
    std::vector<std::vector<int>> field = make_field();
    int n = field.size(), m = field.at(0).size(), counter = 0, x, y, m2 = m / 2, n2 = n / 2;
    std::vector<int> y_bul = { n2, n2, n2, n2, n2, n2 ,n2, n2, n2, n2, n2, n2, n2, n2, n2, n2, n2, n2, n2 ,n2, n2, n2, n2, n2, n2, n2 }, x_bul = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26 };
    std::vector<bool> rtmp = { true, false, false, true, true, false, false, true, true, false, false, true, false, true, false, false, true, true, false, false, true, true, false, false, true, false }, utmp = { true, false, false, true, true, false, false, true, true, false, false, true, false, true, false, false, true, true, false, false, true, true, false, false, true, false };
    bool RIGHT[26], UP[26];
    x = m2; y = n - 2;
    field.at(y).at(x) = -1;

    /*弾の動く方向の乱数化*/
    std::random_device seed_gen;
    std::mt19937 engine(seed_gen());
    std::shuffle(rtmp.begin(), rtmp.end(), engine);
    std::random_device seed_gen1;
    std::mt19937 engine1(seed_gen1());
    std::shuffle(utmp.begin(), utmp.end(), engine1);
    for (int i = 0; i < 26; ++i) { RIGHT[i] = rtmp.at(i); UP[i] = utmp.at(i); }

    print_field(field);
    Sleep(100);
    printf("Start to press spacekey.");
    while (true) {
        if (GetAsyncKeyState(VK_SPACE) & 0x8000) break;
    }
    system("cls");
    
    for (int i = 0; i < 26; ++i) {
        field.at(y_bul.at(i)).at(x_bul.at(i)) = -3;
    }
    field.at(1).at(m2) = 500;
    field.at(2).at(m2) = 1000;
    field.at(2).at(m2 - 1) = 500;
    field.at(2).at(m2 + 1) = 500;
    field.at(3).at(m2) = 99999;
    field.at(3).at(m2 - 1) = 1000;
    field.at(3).at(m2 + 1) = 1000;
    field.at(3).at(m2 - 2) = 500;
    field.at(3).at(m2 + 2) = 500;
    field.at(4).at(m2) = 1000;
    field.at(4).at(m2 - 1) = 500;
    field.at(4).at(m2 + 1) = 500;
    field.at(5).at(m2) = 500;

    print_field(field);
    while (true) {
        /*自機の挙動*/
        Move_Player(field, x, y);

        /*発射*/
        rel_bullet(field, x, y);
        update_bullet_player(field);

        /*弾の挙動*/
        for (int i = 0; i < 26; ++i) {
            update_bullet(field, x_bul.at(i), y_bul.at(i), UP[i], RIGHT[i]);
        }

        //あたり判定
        if (field.at(y).at(x) != -1) { 
            field.clear();
            field.shrink_to_fit();
            y_bul.clear();
            y_bul.shrink_to_fit();
            rtmp.clear();
            rtmp.shrink_to_fit();
            utmp.clear();
            utmp.shrink_to_fit();
            return false; 
        }
        if (field.at(1).at(m2) == -1 || field.at(2).at(m2) == -1 || field.at(3).at(m2) == -1 || field.at(2).at(m2 - 1) == -1 || field.at(2).at(m2 + 1) == -1) {
            field.clear();
            field.shrink_to_fit();
            y_bul.clear();
            y_bul.shrink_to_fit();
            rtmp.clear();
            rtmp.shrink_to_fit();
            utmp.clear();
            utmp.shrink_to_fit();
            return false;
        }

        /*クリア判定*/
        if (field.at(1).at(m2) <= 0 && field.at(2).at(m2) <= 0 && field.at(3).at(m2) <= 0 && field.at(2).at(m2 - 1) <= 0 && field.at(2).at(m2 + 1) <= 0)break;

        /*場の表示*/
        print_field(field);

        /*およそ60fps*/
        Sleep(16.667);
    }
    field.clear();
    field.shrink_to_fit();
    y_bul.clear();
    y_bul.shrink_to_fit();
    rtmp.clear();
    rtmp.shrink_to_fit();
    utmp.clear();
    utmp.shrink_to_fit();
    return true;
}

/*ゲーム開始*/
bool Play_game() {
    bool life;
    life = stage_1();
    PlaySound(NULL, 0, 0);
    if (!life) return false;

    life = stage_2();
    PlaySound(NULL, 0, 0);
    if (!life) return false;


    life = stage_3();
    PlaySound(NULL, 0, 0);
    if (!life) return false;

    return true;
}

int main() {
    bool life = false;
    int game_state, retry_cursor = 0, __;

    while (true) {
        game_state = OPENING();
        if (game_state == -1) {
            __ = Music_Room();
        }
        else {
            break;
        }
        Sleep(16.667);
    }

    /*カーソルの削除*/
    constexpr CONSOLE_CURSOR_INFO cursor{ 1, FALSE };
    CONSOLE_CURSOR_INFO init;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &init);
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);

    Sleep(500);
    if (game_state == 0) {
        return 0;
    }
    if (game_state == 99) {
        PlaySound(L"BGM/Weekend.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
        while (true) {
            life = stage_Ex();
            system("cls");
            if (life) {
                SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &init);
                printf("Cleared!\n");
                return 0;
            }
        }
    }

    while (true) {
        life = Play_game();
        system("cls");
        if (life) {
            SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &init);
            printf("Cleared!\n");
            return 0;
        }
        printf("\nRetry?\n->Yes\n  No");
        while (true) {
            if ((GetAsyncKeyState(VK_UP) & 0x8000) || (GetAsyncKeyState(VK_DOWN) & 0x8000)) {
                ++retry_cursor;
                retry_cursor %= 2;
            }
            if (retry_cursor == 0) {
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 0, 0 });
                printf("\nRetry?\n->Yes\n  No");
                if (GetAsyncKeyState(VK_RETURN) & 0x8000) break;
            }
            else {
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 0, 0 });
                printf("\nRetry?\n  Yes\n->No");
                if (GetAsyncKeyState(VK_RETURN) & 0x8000) { SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &init); return 0; }
            }
            Sleep(100);
        }
        Sleep(16.667);
    }
    printf("Finish to press spacekey.");
    while (true) {
        if (GetAsyncKeyState(VK_SPACE) & 0x8000) break;
        Sleep(100);
    }
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &init);
    return 0;
}
