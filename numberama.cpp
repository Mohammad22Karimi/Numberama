#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>

using namespace std;

struct Player
{
    char name[50];
    char password[50];
    int score;
};

void displayBoard(char **board, int size)
{
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            cout << board[i][j] << ' ';
        }
        cout << endl;
    }
}

bool checkPairs(char **board, int size)
{
    // بررسی تمامی خانه‌های جدول
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if ((board[i][j] != '0') && (board[i][j] != '*'))
            {
                // بررسی جفت در سمت راست
                if ((j < size - 1) && ((board[i][j] - '0' + board[i][j + 1] - '0' == 10) || (board[i][j] == board[i][j + 1])))
                {
                    return true;
                }
                // بررسی جفت در سمت پایین
                if ((i < size - 1) && ((board[i][j] - '0' + board[i + 1][j] - '0' == 10) || (board[i][j] == board[i + 1][j])))
                {
                    return true;
                }
            }
        }
    }
    return false; // هیچ جفتی پیدا نشد
}

bool betweenNumber(char **board, int row1, int col1, int row2, int col2, int size)
{
    if (row1 == row2)
    {
        if (col1 > col2)
        {
            if (col2 == col1 - 1)
            {
                return true;
            }
            else if ((board[row2][col2 + 1] == '0') || (board[row2][col2 + 1] == '*'))
            {
                for (int i = col2 + 1; i < col1; i++)
                {
                    if ((board[row2][i] == '0') || (board[row2][i] == '*'))
                    {
                        continue;
                    }
                    else
                        return false;
                }
                if (board[row1][col1] == board[row2][col2] || (board[row1][col1] - '0' + board[row2][col2] - '0') == 10)
                {
                    return true;
                }
            }
        }
        else if (col1 < col2)
        {
            if (col2 - 1 == col1)
            {
                return true;
            }
            else if ((board[row1][col1 + 1] == '0') || (board[row1][col1 + 1] == '*'))
            {
                for (int i = col1 + 1; i < col2; i++)
                {
                    if ((board[row1][i] == '0') || (board[row1][i] == '*'))
                    {
                        continue;
                    }
                    else
                        return false;
                }
                if (board[row1][col1] == board[row2][col2] || (board[row1][col1] - '0' + board[row2][col2] - '0') == 10)
                {
                    return true;
                }
            }
        }
    }
    if (col1 == col2)
    {
        if (row1 > row2)
        {
            if (row1 - 1 == row2)
            {
                return true;
            }
            else if ((board[row2 + 1][col2] == '0') || (board[row2 + 1][col2] == '*'))
            {
                for (int i = row2 + 1; i < row1; i++)
                {
                    if ((board[i][col2] == '0') || (board[i][col2] == '*'))
                    {
                        continue;
                    }
                    else
                        return false;
                }
                if (board[row1][col1] == board[row2][col2] || (board[row1][col1] - '0' + board[row2][col2] - '0') == 10)
                {
                    return true;
                }
            }
        }
        else if (row1 < row2)
        {
            if (row1 == row2 - 1)
            {
                return true;
            }
            else if ((board[row1 + 1][col1] == '0') || (board[row1 + 1][col1] == '*'))
            {
                for (int i = row1 + 1; i < row2; i++)
                {
                    if ((board[i][col1] == '0') || (board[i][col1] == '*'))
                    {
                        continue;
                    }
                    else
                        return false;
                }
                if (board[row1][col1] == board[row2][col2] || (board[row1][col1] - '0' + board[row2][col2] - '0') == 10)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

void sort(char **board, int &randRow, int &randCol, int size, int &row1, int &col1, int &row2, int &col2, Player &player)
{
    char temp;
    // row1 , col1 که برابر سطر و ستون ستاره اند
    // ستاره با کناری های سطر انتخاب شده باشد
    if (((row2 == randRow) && (col2 == randCol + 1)) || ((row2 == randRow) && (col2 == randCol - 1)))
    {
        // ستاره را به اخر سطر منتقل میکنیم
        temp = board[randRow][randCol];
        board[randRow][randCol] = board[randRow][size - 1];
        board[randRow][size - 1] = temp;

        // سطر را سورت میکنیم
        for (int i = 0; i < size - 2; i++)
        {
            for (int j = 0; j < size - 2 - i; j++)
            {
                if (board[randRow][j] > board[randRow][j + 1])
                {
                    temp = board[randRow][j + 1];
                    board[randRow][j + 1] = board[randRow][j];
                    board[randRow][j] = temp;
                }
            }
        }
        // ستاره به صفر تبدیل میشود تا حذف شده در نظر گرفته شود
        board[randRow][size - 1] = '0';

        // جفت های متناظر را باهم حذف میکنیم و برای هر کدام از جفت ها یک امتیاز لحاظ میشود
        for (int k = 0; k < size - 2; k++)
        {
            if (board[randRow][k] == board[randRow][k + 1])
            {
                board[randRow][k] = '0';
                board[randRow][k + 1] = '0';
                player.score += 1;
            }
        }
    }
    // ستاره با کناری های ستون انتخاب شده باشد
    else if (((row2 == randRow + 1) && (col2 == randCol)) || ((row2 == randRow - 1) && (col2 == randCol)))
    {
        // ستاره را به اخر ستون منتقل میکنیم
        temp = board[randRow][randCol];
        board[randRow][randCol] = board[size - 1][randCol];
        board[size - 1][randCol] = temp;

        // سورت ستون
        for (int i = 0; i < size - 2; i++)
        {
            for (int j = 0; j < size - 2 - i; j++)
            {
                if (board[j][randCol] > board[j + 1][randCol])
                {
                    temp = board[j + 1][randCol];
                    board[j + 1][randCol] = board[j][randCol];
                    board[j][randCol] = temp;
                }
            }
        }
        // ستاره به صفر تبدیل میشود تا حذف شده در نظر گرفته شود
        board[size - 1][randCol] = '0';
        // جفت های متناظر را باهم حذف میکنیم و برای هر کدام از جفت ها یک امتیاز لحاظ میشود
        for (int k = 0; k < size - 2; k++)
        {
            if (board[k][randCol] == board[k + 1][randCol])
            {
                board[k][randCol] = '0';
                board[k + 1][randCol] = '0';
                player.score += 1;
            }
        }
    }
}

void playerMove(char **board, Player &currentPlayer, int size, int &randRow, int &randCol)
{
    int row1, col1, row2, col2;

    cout << "Enter the row and column of the first number:";
    cin >> row1 >> col1;

    cout << "Enter the row and column of the second number:";
    cin >> row2 >> col2;
    int b = 0;
    // برای اینکه اگر ستاره را با همسایگی در سطر انتخاب کرد
    if (((row1 == randRow) && (col1 == randCol)) && (((row2 == randRow) && (col2 == randCol + 1)) || ((row2 == randRow) && (col2 == randCol - 1))))
    {
        cout << "you chose the * character. and u want sort the Row.\n";
        sort(board, randRow, randCol, size, row1, col1, row2, col2, currentPlayer);
        //  currentPlayer.score+=1;
        b = 1;
    }
    // برای اینکه اگر ستاره را با همسایگی در ستون انتخاب کرد
    if (((row1 == randRow) && (col1 == randCol)) && (((row2 == randRow + 1) && (col2 == randCol)) || ((row2 == randRow - 1) && (col2 == randCol))))
    {
        cout << "you chose the * character. and u want sort the Col.\n";
        sort(board, randRow, randCol, size, row1, col1, row2, col2, currentPlayer);
        //  currentPlayer.score+=1;
        b = 2;
    }

    if (betweenNumber(board, row1, col1, row2, col2, size))
    {
        if ((board[row1][col1] - '0' + board[row2][col2] - '0' == 10) || (board[row1][col1] == board[row2][col2]))
        {
            currentPlayer.score += 1;

            // Remove the selected numbers
            board[row1][col1] = '0';
            board[row2][col2] = '0';

            // نمایش صفحه پس از حذف اعداد
            displayBoard(board, size);
        }
        else if (((row1 == randRow) && (col1 == randCol)))
        {
            //  cout << "you chose the *.";
        }

        else
            cout << "invalid!\n";
    }
    else if (((row1 == randRow) && (col1 == randCol)))
    {
        // cout << "you chose the *.";
    }
    else
        cout << "invalid!\n";
    // برای اینکه اگر کاربر دوباره این سطر و ستون را انتخاب کرد(ممکنه اعدادی که سورت میشن جای این خونه را بگیرند) سطر یا ستون کاراکتر ستاره به اخر منتقل بشه(حکم حذف شده داشته باشه)
    if (b == 1)
    {
        randCol = size - 1;
    }
    else if (b == 2)
    {
        randRow = size - 1;
    }
}

void deleteDynamic(char **board, int size)
{
    for (int i = 0; i < size; ++i)
    {
        delete[] board[i];
    }
    delete[] board;
}

void savePlayerData(Player *players, int numPlayers)
{
    ofstream outFile("players.txt"); // فایل را برای نوشتن باز میکنیم
    if (!outFile)
    {
        cerr << "Error opening file for writing." << endl;
        return;
    }

    for (int i = 0; i < numPlayers; ++i)
    { // آپدیت کردن داده ها. اگر بازیکنی به لیست اضافه شده اون رو توی فایل ذخیره کنه
        outFile << players[i].name << ' ' << players[i].password << ' ' << players[i].score << endl;
    }

    outFile.close();
}

void loadPlayerData(Player *players, int &numPlayers)
{
    ifstream inFile("players.txt"); // فایل را برای خواندن باز میکنیم
    if (!inFile)
    {
        cerr << "Error opening file for reading." << endl;
        return;
    }

    numPlayers = 0;
    // بر این اساس تعداد بازیکن ها را را آپدیت میکنیم
    Player player; // یک ساختار موقت برای خوندن داده ها از فایل
    while (inFile >> player.name >> player.password >> player.score)
    {
        players[numPlayers++] = player; // کپی کردن داده های فایل در players
    }

    inFile.close();
}

void swapPlayers(Player &a, Player &b)
{
    Player temp = a;
    a = b;
    b = temp;
}

void bubbleSortPlayers(Player *players, int numPlayers)
{ // بابل سورت برای مرتب کردن داده های فایل
    for (int i = 0; i < numPlayers - 1; ++i)
    {
        for (int j = 0; j < numPlayers - i - 1; ++j)
        {
            if (players[j].score < players[j + 1].score ||
                (players[j].score == players[j + 1].score && strcmp(players[j].name, players[j + 1].name) > 0))
            {
                swapPlayers(players[j], players[j + 1]);
            }
        }
    }
}

int findPlayerIndex(Player *players, int numPlayers, Player &currentPlayer)
{
    for (int i = 0; i < numPlayers; i++)
    {
        if (strcmp(players[i].name, currentPlayer.name) == 0 &&
            strcmp(players[i].password, currentPlayer.password) == 0)
        {
            return i;
        }
    }
    return -1;
}

int main()
{

    int size;
    cout << "Enter the size of the board (an integer):";
    cin >> size;

    srand(time(0));

    char **board = new char *[size];
    for (int i = 0; i < size; ++i)
    {
        board[i] = new char[size];
        for (int j = 0; j < size; ++j)
        {
            // تا زمانی که مقدار تصادفی صفر باشد، تلاش کنید مقدار جدید به دست آورید
            while (true)
            {
                char randomValue = rand() % 10 + '0';
                if (randomValue != '0')
                {
                    board[i][j] = randomValue;
                    break;
                }
            }
        }
    }
    // جایگذین کردن یکی از خانه ها با *
    int randRow = rand() % size;
    int randCol = rand() % size;
    board[0][0] = '2';
    board[0][1] = '2';
    board[randRow][randCol] = '*';

    int MAX_PLAYERS = 100;
    Player players[MAX_PLAYERS];
    int numPlayers; // برای تعداد بازیکن

    loadPlayerData(players, numPlayers);

    Player currentPlayer;
    cout << "Enter your name:";
    cin >> currentPlayer.name;
    cout << "Enter your password:";
    cin >> currentPlayer.password;
    currentPlayer.score = 0;

    bool continuePlaying = true;
    while (continuePlaying)
    {
        if (!checkPairs(board, size))
        {
            cout << "\nU win! Your score is ---> " << currentPlayer.score << endl
                 << endl;

            // برسی اینکه بازیکن فعلی قبلا ثبت نام کرده یا ن. اگر کرده بود نمره بیشتر را برایش لحاظ میکنیم
            int playerIndex = findPlayerIndex(players, numPlayers, currentPlayer);
            if (playerIndex != -1)
            {
                // بازیکن پیدا شده و امتیازشو آپدیت کنیم
                if (players[playerIndex].score > currentPlayer.score)
                    players[playerIndex].score = players[playerIndex].score;
                else
                    players[playerIndex].score = currentPlayer.score;
            }
            else
            {
                // بازیکن پیدا نشده پس یه بازیکن اضافه میکنیم
                players[numPlayers++] = currentPlayer;
            }

            bubbleSortPlayers(players, numPlayers);

            for (int i = 0; i < numPlayers; ++i)
            {
                cout << players[i].name << " >>>> " << players[i].score << endl;
                cout << "--------------------------\n";
            }

            savePlayerData(players, numPlayers);

            // حذف حافظه داینامیک
            deleteDynamic(board, size);
            return 0;
        }
        displayBoard(board, size);
        playerMove(board, currentPlayer, size, randRow, randCol);

        cout << "Your current score:" << currentPlayer.score << endl;
    }

    return 0;
}
