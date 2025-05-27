#include <stdio.h> // 標準入出力ライブラリのインクルード

// プロトタイプ宣言
void print_board(int input_col, int input_row);
int is_valid_position(int col, int row);
int check_get_treasure(int input_col, int input_row);
void show_board_or_error(int valid, int input_col, int input_row);
void show_result_message(int found);

// 定数定義
#define TRE_COUNT 10    // 宝物の数
#define MAX_TRIES 20    // 最大試行回数
#define GRID_SIZE 10    // 盤面のサイズ

// 宝物の座標
int tre_x[TRE_COUNT] = {5, 3, 0, 5, 1, 2, 4, 0, 3, 2};
int tre_y[TRE_COUNT] = {8, 9, 5, 9, 7, 8, 6, 1, 7, 5};
// 取得判定フラグ
int get_comp[TRE_COUNT] = {0};

// 盤面を表示する関数
void print_board(int input_col, int input_row) {
    printf("   "); // 列番号の前のスペースを表示
    for (int col = 0; col < GRID_SIZE; col++) { // 列番号を0から9まで表示
        printf("%2d", col); // 列番号を2桁で表示
    }
    printf("\n"); // 列番号表示後に改行
    for (int row = 0; row < GRID_SIZE; row++) { // 各行を表示
        printf("%2d ", row); // 行番号を2桁で表示
        for (int col = 0; col < GRID_SIZE; col++) { // 各列を表示
            if (col == input_col && row == input_row) { // 入力座標と一致する場合
                printf("■ "); // プレイヤーの入力位置を強調表示
            }
            else {
                printf("□ "); // それ以外は通常のマスを表示
            }
        }
        printf("\n"); // 行の終わりで改行
    }
}

// 関数1: 入力座標の妥当性判定
int is_valid_position(int col, int row) {
    return (col >= 0 && col < GRID_SIZE && row >= 0 && row < GRID_SIZE); // 0以上9以下なら妥当
}

// 関数2: 宝物発見判定（未取得の宝物のみ）
int check_get_treasure(int input_col, int input_row) {
    for (int i = 0; i < TRE_COUNT; i++) {
        if (!get_comp[i] && input_col == tre_x[i] && input_row == tre_y[i]) {
            get_comp[i] = 1; // 取得済みにする
            return 1;
        }
    }
    return 0;
}

// 関数3: 受理なら盤面表示、NGならエラーメッセージ表示
void show_board_or_error(int valid, int input_col, int input_row) {
    if (valid) { // 妥当な入力なら
        print_board(input_col, input_row); // 盤面を表示
    }
    else {
        printf("エラー：範囲外の入力です。\n"); // エラーメッセージを表示
    }
}

// 関数4: 一致判定結果に応じて「はずれ」「あたり」表示
void show_result_message(int found) {
    if (found) { // 宝物を発見した場合
        printf("あたり！\n"); // 当たりメッセージ
    }
    else {
        printf("はずれ。\n"); // 外れメッセージ
    }
}

int main() {
    int input_col, input_row; // プレイヤーが入力する列・行
    int tries = 0; // 試行回数カウンタ
    int score = 0; // スコア（発見した宝物の数）

    while (tries < MAX_TRIES && score < TRE_COUNT) { // 最大試行回数または全宝物発見で終了
        printf("[%d回目] 座標を入力してください。\n", tries + 1); // 試行回数を表示
        printf("列 = "); // 列入力を促す
        scanf_s("%d", &input_col); // 列番号の入力
        printf("行 = "); // 行入力を促す
        scanf_s("%d", &input_row); // 行番号の入力

        int valid = is_valid_position(input_col, input_row); // 入力値の妥当性を判定
        int get_treasure = 0; // 宝物発見フラグ
        if (valid) { // 妥当な入力の場合
            get_treasure = check_get_treasure(input_col, input_row); // 宝物発見判定
            if (get_treasure) { // 宝物を発見した場合
                score++; // スコアをインクリメント
            }
        }

        show_board_or_error(valid, input_col, input_row); // 盤面またはエラー表示

        if (valid) { // 妥当な入力の場合
            show_result_message(get_treasure); // 判定結果を表示
        }

        tries++; // 試行回数をインクリメント
    }

    printf("スコア: %d\n", score); // 最終スコアを表示

    return 0; // プログラム終了
}
