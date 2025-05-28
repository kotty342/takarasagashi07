#include <stdio.h> // 標準入出力ライブラリのインクルード

// 定数定義
constexpr auto MAX_TRIES = 20;     // 最大試行回数
constexpr auto GRID_SIZE = 10;     // 盤面のサイズ
constexpr auto TRE_COUNT = 10;     // 宝物の数

// 宝物の座標
const int tre_x[TRE_COUNT] = {5, 3, 0, 5, 1, 2, 4, 0, 3, 2};
const int tre_y[TRE_COUNT] = {8, 9, 5, 9, 7, 8, 6, 1, 7, 5};

// 取得済み判定用フラグ
int get_comp[TRE_COUNT] = {0};

// プロトタイプ宣言
int is_valid_position(int x, int y); // 入力座標の妥当性判定関数のプロトタイプ
int check_get_treasure(int input_x, int input_y, const int tre_x[], const int tre_y[], int get_comp[]); // 宝物取得判定関数のプロトタイプ
void show_board_or_error(int input_error, int input_x, int input_y); // 盤面表示またはエラー表示関数のプロトタイプ
void show_result_message(int get_treasure); // 判定結果表示関数のプロトタイプ
int is_game_end(int game_count, int score); // ゲーム終了判定関数のプロトタイプ
void show_score(int score); // スコア表示関数のプロトタイプ

int main() {
    int input_x = 0, input_y = 0; // プレイヤーが入力する列・行
    int score = 0; // スコア
    int game_count = 0; // 試行回数

    while (!is_game_end(game_count, score)) { // ゲーム終了条件を満たすまで繰り返す
        printf("[%d回目] 座標を入力してください。\n", game_count + 1); // 試行回数を表示
        printf("列 = ");
        scanf_s("%d", &input_x);
        printf("行 = ");
        scanf_s("%d", &input_y);

        int input_error = is_valid_position(input_x, input_y); // 入力値の妥当性を判定
        int get_treasure = 0;

        if (input_error) { // 妥当な入力の場合
            // 宝物判定
            get_treasure = check_get_treasure(input_x, input_y, tre_x, tre_y, get_comp);
            if (get_treasure) {
                score++; // スコアを加算
            }
        }

        show_board_or_error(input_error, input_x, input_y); // 盤面またはエラー表示

        show_result_message(get_treasure); // 判定結果を表示

        game_count++;
    }

    show_score(score); // スコアを表示

    return 0;
}

// 関数1: 入力座標の妥当性判定
int is_valid_position(int x, int y) {
    if (x < 0 || x >= GRID_SIZE) {
        return 0;
    }
    if (y < 0 || y >= GRID_SIZE) {
        return 0;
    }
    return 1;
}

// 関数2: 宝物取得判定（未取得のみスコア加算）
int check_get_treasure(int input_x, int input_y, const int tre_x[], const int tre_y[], int get_comp[]) {
    for (int i = 0; i < TRE_COUNT; i++) {
        if (input_x == tre_x[i] && input_y == tre_y[i]) {
            if (get_comp[i] == 0) { // 未取得の場合
                get_comp[i] = 1; // 取得済みに設定
                return 1; // 新規取得
            } else {
                return 0; // 既取得
            }
        }
    }
    return 0;
}

// 関数3: エラーフラグに応じて盤面表示またはエラーメッセージを表示
// エラー時はエラーメッセージのみ表示
void show_board_or_error(int input_error, int input_x, int input_y) {
    if (input_error) {
        // 盤面を表示
        printf("   ");
        for (int col = 0; col < GRID_SIZE; col++) {
            printf("%2d", col);
        }
        printf("\n");
        for (int row = 0; row < GRID_SIZE; row++) {
            printf("%2d ", row);
            for (int col = 0; col < GRID_SIZE; col++) {
                if (col == input_x && row == input_y) {
                    printf("■ ");
                }
                else {
                    printf("□ ");
                }
            }
            printf("\n");
        }
    }
    else {
        printf("エラー：範囲外の入力です。(0から%dの間で入力してください)\n", GRID_SIZE - 1); // エラーメッセージのみ表示
    }
}

// 関数4: 一致判定結果に応じて「はずれ」「あたり」表示
void show_result_message(int get_treasure) {
    if (get_treasure) { // 宝物を発見した場合
        printf("あたり！\n"); // 当たりメッセージ
    }
    else {
        printf("はずれ。\n"); // 外れメッセージ
    }
}

// 関数5: ゲーム終了判定
int is_game_end(int game_count, int score) {
    if (game_count >= MAX_TRIES) {
        return 1;
    }
    if (score >= TRE_COUNT) {
        return 1;
    }
    return 0;
}

// 関数6: スコア表示
void show_score(int score) {
    printf("スコア: %d\n", score);
}

