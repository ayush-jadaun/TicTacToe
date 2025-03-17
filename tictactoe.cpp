#include<bits/stdc++.h>
using namespace std;

const char X = 'X', O = 'O', E = ' ';
int n, win_cond;
stack<vector<vector<char>>> history; // For undo functionality
int p1_score = 0, p2_score = 0, draw_score = 0;

// Opening book for common moves (for 3x3 board)
unordered_map<string, int> opening_book;

// Function prototypes
void print(const vector<vector<char>>& b);
bool check_win(const vector<vector<char>>& b, char p);
bool full(const vector<vector<char>>& b);
void undo_move(vector<vector<char>>& b);
void save_game(const vector<vector<char>>& b, char current_player);
bool load_game(vector<vector<char>>& b, char& current_player);
void display_menu();
void player_move(vector<vector<char>>& b, char p);
void ai_move(vector<vector<char>>& b, char ai, int difficulty);
string board_to_string(const vector<vector<char>>& b);
void init_opening_book();
int minimax(vector<vector<char>>& b, char p, int depth, int max_depth, int alpha, int beta);
pair<int, int> find_best_move(vector<vector<char>>& b, char p, int max_depth);

// Initialize opening book
void init_opening_book() {
    // Only initialize for 3x3 standard board
    if (n != 3 || win_cond != 3) return;
    
    // First moves for X (center and corners are strong)
    opening_book["         "] = 4; // Center
    
    // Responses for O when X plays center
    opening_book["    X    "] = 0; // Top-left corner
    
    // Responses for X to counter O's moves
    opening_book["O   X    "] = 8; // Bottom-right corner
    opening_book["    X   O"] = 0; // Top-left corner
    opening_book["    XO   "] = 8; // Bottom-right corner
    opening_book["    X  O "] = 6; // Bottom-left corner
    
    // Block potential fork situations
    opening_book["O   X    X"] = 6; // Block potential fork
    opening_book["X   O   X "] = 7; // Block potential fork
}

// Convert board to string representation for opening book
string board_to_string(const vector<vector<char>>& b) {
    string result;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result += b[i][j];
        }
    }
    return result;
}

// Print the board dynamically
void print(const vector<vector<char>>& b) {
    cout << "  ";
    for (int j = 0; j < n; ++j) {
        cout << " " << j + 1 << "  ";
    }
    cout << "\n";
    
    for (int i = 0; i < n; ++i) {
        cout << i + 1 << " ";
        for (int j = 0; j < n; ++j) {
            cout << b[i][j];
            if (j < n - 1) cout << " | ";
        }
        cout << "\n";
        if (i < n - 1) cout << "  " << string(n * 4 - 1, '-') << "\n";
    }
    cout << "\n";
}

// Check for a win
bool check_win(const vector<vector<char>>& b, char p) {
    // Row and column check
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= n - win_cond; ++j) {
            bool row_win = true, col_win = true;
            for (int k = 0; k < win_cond; ++k) {
                if (b[i][j + k] != p) row_win = false;
                if (b[j + k][i] != p) col_win = false;
            }
            if (row_win || col_win) return true;
        }
    }
    // Diagonal check
    for (int i = 0; i <= n - win_cond; ++i) {
        for (int j = 0; j <= n - win_cond; ++j) {
            bool diag1 = true, diag2 = true;
            for (int k = 0; k < win_cond; ++k) {
                if (b[i + k][j + k] != p) diag1 = false;
                if (b[i + k][j + win_cond - k - 1] != p) diag2 = false;
            }
            if (diag1 || diag2) return true;
        }
    }
    return false;
}

// Check for a full board
bool full(const vector<vector<char>>& b) {
    for (auto& row : b)
        for (char c : row)
            if (c == E) return false;
    return true;
}

// Minimax algorithm with alpha-beta pruning and difficulty adjustment
int minimax(vector<vector<char>>& b, char p, int depth, int max_depth, int alpha, int beta) {
    if (check_win(b, X)) return 10 - depth;
    if (check_win(b, O)) return -10 + depth;
    if (full(b) || depth == max_depth) return 0;

    int best_score = (p == X) ? numeric_limits<int>::min() : numeric_limits<int>::max();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (b[i][j] == E) {
                b[i][j] = p;
                int score = minimax(b, (p == X) ? O : X, depth + 1, max_depth, alpha, beta);
                b[i][j] = E;
                
                if (p == X) {
                    best_score = max(best_score, score);
                    alpha = max(alpha, best_score);
                } else {
                    best_score = min(best_score, score);
                    beta = min(beta, best_score);
                }
                
                // Alpha-beta pruning
                if (beta <= alpha) break;
            }
        }
    }
    return best_score;
}

// Find best move using minimax with alpha-beta pruning
pair<int, int> find_best_move(vector<vector<char>>& b, char p, int max_depth) {
    int best_score = (p == X) ? numeric_limits<int>::min() : numeric_limits<int>::max();
    pair<int, int> best_move = {-1, -1};
    
    // Check opening book first
    if (n == 3 && win_cond == 3) {
        string board_str = board_to_string(b);
        if (opening_book.find(board_str) != opening_book.end()) {
            int move = opening_book[board_str];
            return {move / n, move % n};
        }
    }
    
    // If not in opening book, use minimax with alpha-beta pruning
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (b[i][j] == E) {
                b[i][j] = p;
                int score = minimax(b, (p == X) ? O : X, 0, max_depth, 
                                   numeric_limits<int>::min(), numeric_limits<int>::max());
                b[i][j] = E;
                
                if ((p == X && score > best_score) || (p == O && score < best_score)) {
                    best_score = score;
                    best_move = {i, j};
                }
            }
        }
    }
    return best_move;
}

// Undo last move
void undo_move(vector<vector<char>>& b) {
    if (history.size() > 1) { // Keep at least the initial state
        history.pop(); // Remove current state
        b = history.top(); // Go back to previous state
        cout << "Move undone!\n";
    } else {
        cout << "No moves to undo!\n";
    }
}

// Save the current game state
void save_game(const vector<vector<char>>& b, char current_player) {
    ofstream file("tictactoe_save.txt");
    if (!file) {
        cout << "Error: Could not create save file.\n";
        return;
    }
    
    // Save board size and win condition
    file << n << " " << win_cond << "\n";
    
    // Save current player
    file << current_player << "\n";
    
    // Save scores
    file << p1_score << " " << p2_score << " " << draw_score << "\n";
    
    // Save board state
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            file << (b[i][j] == E ? '_' : b[i][j]);
        }
        file << "\n";
    }
    
    file.close();
    cout << "Game saved successfully!\n";
}

// Load a saved game
bool load_game(vector<vector<char>>& b, char& current_player) {
    ifstream file("tictactoe_save.txt");
    if (!file) {
        cout << "Error: Save file not found.\n";
        return false;
    }
    
    int saved_n, saved_win_cond;
    file >> saved_n >> saved_win_cond;
    
    if (saved_n != n || saved_win_cond != win_cond) {
        cout << "Warning: Saved game has different board size or win condition.\n";
        cout << "Loaded game will use: " << saved_n << "x" << saved_n << " board with " << saved_win_cond << "-in-a-row win condition.\n";
        n = saved_n;
        win_cond = saved_win_cond;
        b.resize(n, vector<char>(n, E));
    }
    
    file >> current_player;
    file >> p1_score >> p2_score >> draw_score;
    
    // Clear history and create new initial state
    while (!history.empty()) history.pop();
    
    string line;
    getline(file, line); // Skip newline
    
    for (int i = 0; i < n; ++i) {
        getline(file, line);
        for (int j = 0; j < n && j < line.length(); ++j) {
            b[i][j] = (line[j] == '_') ? E : line[j];
        }
    }
    
    // Add current state to history
    history.push(b);
    
    file.close();
    cout << "Game loaded successfully!\n";
    return true;
}

// Player move
void player_move(vector<vector<char>>& b, char p) {
    while (true) {
        int r, c;
        cout << "Player " << p << ", enter row and column (e.g., 1 2): ";
        
        if (!(cin >> r >> c)) {
            // Clear input errors
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter numbers.\n";
            continue;
        }
        
        // Check for special commands
        if (r == -1) {
            if (c == 1) { // Undo
                undo_move(b);
                continue;
            } else if (c == 2) { // Save game
                save_game(b, p);
                continue;
            } else if (c == 3) { // Load game
                load_game(b, p);
                return; // Exit the function as the current player might have changed
            }
        }
        
        --r; --c; // Convert to 0-indexed
        if (r >= 0 && r < n && c >= 0 && c < n && b[r][c] == E) {
            b[r][c] = p;
            history.push(b); // Save state for undo
            break;
        }
        cout << "Invalid move! Try again.\n";
    }
}

// AI move
void ai_move(vector<vector<char>>& b, char ai, int difficulty) {
    cout << "AI is thinking...\n";
    
    if (difficulty == 1) {
        // Easy: Random move
        vector<pair<int, int>> empty;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (b[i][j] == E) empty.push_back({i, j});
        
        if (!empty.empty()) {
            pair<int, int> move = empty[rand() % empty.size()];
            b[move.first][move.second] = ai;
            history.push(b);
        }
    } else {
        // Medium (2) or Hard (3)
        int max_depth = (difficulty == 2) ? 3 : 9;
        pair<int, int> move = find_best_move(b, ai, max_depth);
        if (move.first != -1) {
            b[move.first][move.second] = ai;
            history.push(b);
        }
    }
}

// Display menu
void display_menu() {
    cout << "MENU:\n";
    cout << "During your turn, you can:\n";
    cout << "- Enter row and column to make a move (e.g., 1 2)\n";
    cout << "- Enter -1 1 to undo your last move\n";
    cout << "- Enter -1 2 to save the game\n";
    cout << "- Enter -1 3 to load a saved game\n";
}

// Play a single game
bool play_game(vector<vector<char>>& b, int mode, int difficulty) {
    char cur = X;
    bool game_over = false;
    
    while (!game_over) {
        print(b);
        cout << "Current score: X: " << p1_score << " | O: " << p2_score << " | Draws: " << draw_score << "\n";

        if (mode == 1) {
            if (cur == X) player_move(b, X);
            else ai_move(b, O, difficulty);
        } else {
            player_move(b, cur);
        }

        if (check_win(b, cur)) {
            print(b);
            cout << "Player " << cur << " wins!\n";
            if (cur == X) ++p1_score;
            else ++p2_score;
            game_over = true;
        } else if (full(b)) {
            print(b);
            cout << "It's a draw!\n";
            ++draw_score;
            game_over = true;
        } else {
            cur = (cur == X) ? O : X;
        }
    }

    cout << "Final Scores:\nPlayer X: " << p1_score << "\nPlayer O: " << p2_score << "\nDraws: " << draw_score << "\n";
    
    cout << "Would you like to play again? (y/n): ";
    char play_again;
    cin >> play_again;
    
    return (play_again == 'y' || play_again == 'Y');
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    cout << "Welcome to Enhanced Tic-Tac-Toe!\n";
    
    cout << "Enter board size (e.g., 3 for 3x3): ";
    while (!(cin >> n) || n <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input! Please enter a positive number: ";
    }
    
    cout << "Enter win condition (e.g., 3 for 3-in-a-row): ";
    while (!(cin >> win_cond) || win_cond <= 0 || win_cond > n) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input! Please enter a number between 1 and " << n << ": ";
    }

    vector<vector<char>> b(n, vector<char>(n, E));
    history.push(b); // Save initial state

    // Initialize opening book for standard 3x3 game
    init_opening_book();

    int mode, difficulty = 0;
    cout << "Mode:\n1. Single Player\n2. Multiplayer\nChoose: ";
    while (!(cin >> mode) || (mode != 1 && mode != 2)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input! Please enter 1 or 2: ";
    }

    if (mode == 1) {
        cout << "Difficulty:\n1. Easy\n2. Medium\n3. Hard\nChoose: ";
        while (!(cin >> difficulty) || difficulty < 1 || difficulty > 3) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number between 1 and 3: ";
        }
    }

    display_menu();
    
    bool play_again = true;
    while (play_again) {
        // Clear the board and history for a new game
        b = vector<vector<char>>(n, vector<char>(n, E));
        while (!history.empty()) history.pop();
        history.push(b);
        
        play_again = play_game(b, mode, difficulty);
        
        if (play_again) {
            cout << "\nStarting a new game...\n";
        }
    }
    
    cout << "Thanks for playing!\n";
    return 0;
}
