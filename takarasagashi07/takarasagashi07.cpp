#include <stdio.h> // 標準入出力ライブラリのインクルード

// 定数定義
#define TREASURE_COUNT 10    // 宝物の数（未使用だが仕様に合わせて定義）
#define MAX_TRIES     20     // 最大試行回数
#define GRID_SIZE     10     // 盤面のサイズ

// プロトタイプ宣言
int is_valid_position(int col, int row); // 入力座標の妥当性判定関数のプロトタイプ
int is_treasure_found(int input_col, int input_row, int treasure_col, int treasure_row); // 宝物発見判定関数のプロトタイプ
void show_board_or_error(int valid, int input_col, int input_row); // 盤面表示またはエラー表示関数のプロトタイプ
void show_result_message(int found); // 判定結果表示関数のプロトタイプ
int is_game_end(int tries, int found); // ゲーム終了判定関数のプロトタイプ
void show_end_message(int found); // 終了メッセージ表示関数のプロトタイプ

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

// 関数2: 入力座標と宝物座標の一致判定
int is_treasure_found(int input_col, int input_row, int treasure_col, int treasure_row) {
    return (input_col == treasure_col && input_row == treasure_row); // 座標が一致すれば1
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

// 関数5: 20回か一致判定でゲーム終了判定
int is_game_end(int tries, int found) {
    return (tries >= MAX_TRIES || found); // 最大回数または発見で終了
}

// 関数6: 一致判定結果に応じて"COMPLETE" "GAMEOVER"表示
void show_end_message(int found) {
    if (found) { // 宝物を発見した場合
        printf("COMPLETE\n"); // 完了メッセージ
    }
    else {
        printf("GAMEOVER\n"); // ゲームオーバーメッセージ
    }
}

int main() {
    int input_col, input_row; // プレイヤーが入力する列・行
    int treasure_col = 7, treasure_row = 4; // 宝物の位置（列・行）
    int found = 0; // 宝物発見フラグ
    int tries = 0; // 試行回数カウンタ

    while (!is_game_end(tries, found)) { // ゲーム終了条件を満たすまで繰り返す
        printf("[%d回目] 座標を入力してください。\n", tries + 1); // 試行回数を表示
        printf("列 = "); // 列入力を促す
        scanf_s("%d", &input_col); // 列番号の入力
        printf("行 = "); // 行入力を促す
        scanf_s("%d", &input_row); // 行番号の入力

        int valid = is_valid_position(input_col, input_row); // 入力値の妥当性を判定
        found = is_treasure_found(input_col, input_row, treasure_col, treasure_row); // 宝物発見判定

        show_board_or_error(valid, input_col, input_row); // 盤面またはエラー表示

        if (valid) { // 妥当な入力の場合
            show_result_message(found); // 判定結果を表示
        }

        if (found || !valid) { // 宝物発見またはエラー時
            if (found) break; // 宝物発見時はループを抜ける
        }

        tries++; // 試行回数をインクリメント
    }

    show_end_message(found); // ゲーム終了メッセージを表示

    return 0; // プログラム終了
}
