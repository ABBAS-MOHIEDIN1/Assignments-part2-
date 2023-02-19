#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <fstream>


using namespace std;
int rows = 5, column = 9, zombie = 1;
int attack = 470;
int range = 2;
int attack_damge = 10;
int user_rows, user_column, user_zombie;
int health = 330;
void help();
int h;
int p;
int l;
void load_game(vector<vector<char>> &map, vector<int> &player_status);
void save_game(vector<vector<char>> &map, vector<int> &player_status);


void setting_screen(int &user_rows, int &user_column, int &user_zombie, vector<vector<char>> &map)
{

        
    srand(time(0));
    h = (rand() % 6 + 1) * 50;
    p = (rand() % 3 + 1) * 10;
    l = rand() % 4 + 1;
    while (true)
    {
        cout << "\t\t\t Default Game Setting" << endl;
        cout << "-----------------------------------" << endl;
        cout << "Board rows is 5" << endl;
        cout << "Board column is 5" << endl;
        cout << "Board zombie is 1" << endl;
        cout << "If you want to keep this setting press y. If not, press n. If you have a file, press o if you need help press h: ";
        char Choice;
        cin >> Choice;

        if (Choice == 'n')
        {
            cout << "Enter rows =>  :";
            cin >> user_rows;
            cout << endl;
            cout << "Enter column =>";
            cin >> user_column;
            cout << endl;
            cout << "+++++++++++++++++++++++++++++++++++++" << endl;
            cout << "Zombie setting" << endl;
            cout << "Enter the number of zombies => ";
            cin >> user_zombie;
            cout << endl;
            cout << "Setting updated" << endl;
            break;
        }
        else if (Choice == 'y')
        {
            user_rows = 5;
            user_column = 5;
            user_zombie = 1;
            map = vector<vector<char>>(user_rows, vector<char>(user_column, ' '));
            break;
        }
        else if (Choice == 'o')
        {
              vector<vector<char>> map;
            vector<int> player_status(3);
            load_game(map, player_status);
            user_rows = map.size();
            user_column = map[0].size();
            user_zombie = 0;
            for (int row = 0; row < user_rows; row++)
            {
                for (int col = 0; col < user_column; col++)
                {
                    if (map[row][col] == 'Z')
                    {
                        user_zombie++;
                    }
                }
            }
            break;
        }else if(Choice == 'h'){
            help();
            system("pause");
        }
        else
        {
            cout << "Invalid choice. Please try again." << endl;
        }
    }
}

void load_game(vector<vector<char>> &map, vector<int> &player_status)
{
    string filename;
    cout << "Enter filename to load game: ";
    cin >> filename;

    ifstream infile(filename);
    if (infile.is_open())
    {
        infile >> user_rows >> user_column >> user_zombie;
        map = vector<vector<char>>(user_rows, vector<char>(user_column, ' '));
        for (int i = 0; i < user_rows; i++)
        {
            for (int j = 0; j < user_column; j++)
            {
                map[i][j] = infile.get();
            }
            infile.ignore();
        }
        infile >> player_status[0] >> player_status[1] >> player_status[2];
        infile.close();
        cout << "Game loaded successfully!" << endl;
    }
    else
    {
        cout << "Unable to open file to load game." << endl;
    }
}

class Mars
{
private:
    vector<vector<char>> map_; // convention to put trailing underscore
    int dimX_, dimY_;
            // to indicate private data
    static int health_;
    static int zombie_health_;
    static int zombie_rang_;
    static int zombie_attack_;
    static  int attack_;
    static int rang_;          // to indicate private data
public:
    Mars(int dimX = user_rows, int dimY = user_column);
    void increaseHealth()
    {
        Mars::health_ += 20;
        cout << "Your health has increased to " << Mars::health_ << endl;
    }
    void init(int dimX, int dimY);
    void display() const;

    void middle_R()
    {
        int middleRow = dimY_ / 2;
        int middleCol = dimX_ / 2;
        map_[middleRow][middleCol] = 'R';
    }

    void add_random_z()
    {
        for (int i = 0; i < user_zombie; i++)
        {
            int x = rand() % dimX_;
            int y = rand() % dimY_;
            map_[y][x] = 'Z';
        }
    }
void attackZombie(int row, int col) {
    bool hit = false;
    int maxDamage = 0;
    int maxDamageIndex = -1;
    for (int i = 1; i <= range; i++) {
        // Check for zombies in the attack range
        if (row + i < dimY_ && map_[row + i][col] == 'Z') {
            // If a zombie is found, attempt to attack it
            hit = true;
            int damage = rand() % attack + 1;
            if (damage > maxDamage) {
                maxDamage = damage;
                maxDamageIndex = row + i;
            }
        }
    }

    if (hit) {
        // Attack the zombie with the highest damage in range
        map_[maxDamageIndex][col] = ' ';
        health -= attack_damge;
        if (health < 1) {
            map_[row][col] = ' ';
        }
    }

    if (map_[row][col] == 'A') {
        // Remove the attacker if its health is less than 1
        if (health < 1) {
            map_[row][col] = ' ';
        }
    } else {
        // Remove the zombie if its health is less than 1
        if (rand() % l + 1 > h) {
            map_[row][col] = ' ';
        }
    }
}




    void moveZombies(vector<vector<char>> &map, int dimX, int dimY)
    {
        for (int row = 0; row < dimY; row++)
        {
            for (int col = 0; col < dimX; col++)
            {
                if (map[row][col] == 'Z')
                {
                    int move = rand() % 4; // Randomly choose direction to move
                    if (move == 0)         // Move up
                    {
                        if (row - 1 >= 0 && map[row - 1][col] == ' ')
                        {
                            map[row][col] = ' ';
                            map[row - 1][col] = 'Z';
                        }
                        
                    }
                    else if (move == 1) // Move down
                    {
                        if (row + 1 < dimY && map[row + 1][col] == ' ')
                        {
                            map[row][col] = ' ';
                            map[row + 1][col] = 'Z';
                        }
                    }
                    else if (move == 2) // Move left
                    {
                        if (col - 1 >= 0 && map[row][col - 1] == ' ')
                        {
                            map[row][col] = ' ';
                            map[row][col - 1] = 'Z';
                        }
                    }
                    else // Move right
                    {
                        if (col + 1 < dimX && map[row][col + 1] == ' ')
                        {
                            map[row][col] = ' ';
                            map[row][col + 1] = 'Z';
                        }
                    }
                }
            }
        }
    }
void save_game(vector<vector<char>> &map, vector<int> &player_status)
{
    string filename;
    cout << "Enter filename to save game: ";
    cin >> filename;

    ofstream outfile(filename);
    if (outfile.is_open())
    {
        outfile << map.size() << " " << map[0].size() << " " << user_zombie << endl;
        for (int i = 0; i < map.size(); i++)
        {
            for (int j = 0; j < map[0].size(); j++)
            {
                outfile << map[i][j];
            }
            outfile << endl;
        }
        outfile << player_status[0] << " " << player_status[1] << " " << player_status[2] << endl;
        for (int i = 0; i < map.size(); i++)
        {
            for (int j = 0; j < map[0].size(); j++)
            {
                if (map[i][j] == 'P')
                {
                    outfile << i << " " << j << endl;
                }
                else if (map[i][j] == 'Z')
                {
                    outfile << i << " " << j << endl;
                }
            }
        }
        outfile.close();
        cout << "Game saved successfully!" << endl;
    }
    else
    {
        cout << "Unable to open file to save game." << endl;
    }
}




    void move_R()
    {

        Mars f;
        int middleRow = dimY_ / 2;
        int middleCol = dimX_ / 2;
        map_[middleRow][middleCol] = 'A';
        int currRow = middleRow;
        int currCol = middleCol;

        while (true)
        {
            display();
            cout << "Move R up (w), down (s), left (a), right (d)  or (h) for help : ";
            char direction;
            cin >> direction;
            switch (direction)
            {
            case 'w':
                if (currRow - 1 >= 0 && map_[currRow - 1][currCol] != 'r' && map_[currRow - 1][currCol] != 'A')
                {
                    // Move up
                    if (map_[currRow - 1][currCol] == 'Z')
                    {
                        map_[currRow - 1][currCol] = ' ';
                        health -= attack_damge;
                        cout << "You attacked a zombie and inflicted " << attack_damge << " points of damage." << endl;
                    }
                    if (currRow - 1 >= 0 && map_[currRow - 1][currCol] == '^')
                    {
                        map_[currRow][currCol] = ' ';
                        currRow--;
                        map_[currRow][currCol] = 'A';
                    }
                    if (currRow - 1 >= 0 && map_[currRow - 1][currCol] == 'h')
                    {
                        increaseHealth();
                        cout << "your have +20 health" << endl;
                    }
                    map_[currRow][currCol] = ' ';
                    currRow--;
                    map_[currRow][currCol] = 'A';
                    attackZombie(currRow,currCol);
                    system("pause");
                }
                else
                {
                    cout << "Invalid move. Try again." << endl;
                }
                break;

            case 's':
                if (currRow + 1 < dimY_ && map_[currRow + 1][currCol] != 'r' && map_[currRow + 1][currCol] != 'A')
                {
                    // Move down
                    if (map_[currRow + 1][currCol] == 'Z')
                    {
                        map_[currRow + 1][currCol] = ' ';
                        health -= attack_damge;
                        cout << "You attacked a zombie and inflicted " << attack_damge << " points of damage." << endl;
                    }
                    if (currRow + 1 < dimY_ && map_[currRow + 1][currCol] == 'v')
                    {
                        map_[currRow][currCol] = ' ';
                        currRow++;
                        map_[currRow][currCol] = 'A';
                    }
                    if (currRow + 1 >= 0 && map_[currRow + 1][currCol] == 'h')
                    {
                        increaseHealth();
                        cout << "your have +20 health" << endl;

                    }

                    map_[currRow][currCol] = ' ';
                    currRow++;
                    map_[currRow][currCol] = 'A';
                    attackZombie(currRow,currCol);
                    system("pause");
                }
                else
                {
                    cout << "Invalid move. Try again." << endl;
                }
                break;

            case 'a':
                if (currCol - 1 >= 0 && map_[currRow][currCol - 1] != 'r' && map_[currRow][currCol - 1] != 'A')
                {
                    // Move left
                    if (map_[currRow][currCol - 1] == 'Z')
                    {
                        map_[currRow][currCol - 1] = ' ';
                        health -= attack_damge;
                        cout << "You attacked a zombie and inflicted " << attack_damge << " points of damage." << endl;
                    }
                    if (currCol - 1 >= 0 && map_[currRow][currCol - 1] == '<')
                    {
                        map_[currRow][currCol] = ' ';
                        currCol--;
                        map_[currRow][currCol] = 'A';
                    }
                    if (currRow - 1 >= 0 && map_[currRow][currCol - 1] == 'h')
                    {
                        increaseHealth();
                        cout << "your have +20 health" << endl;

                    }

                    map_[currRow][currCol] = ' ';
                    currCol--;
                    map_[currRow][currCol] = 'A';
                    attackZombie(currRow,currCol);
                    system("pause");
                }
                else
                {
                    cout << "Invalid move. Try again." << endl;
                }
                moveZombies(map_, dimX_, dimY_);
                system("cls");
                break;
            case 'd':
                if (currCol + 1 < dimX_ && map_[currRow][currCol + 1] != 'r' && map_[currRow][currCol + 1] != 'A')
                {
                    if (map_[currRow][currCol + 1] == 'Z')
                    {
                        map_[currRow][currCol + 1] = ' ';
                        health -= attack_damge;
                        cout << "You attacked a zombie and inflicted " << attack_damge << " points of damage." << endl;
                    }
                    if (currCol + 1 < dimX_ && map_[currRow][currCol + 1] == '>')
                    {
                        map_[currRow][currCol] = ' ';
                        currCol++;
                        map_[currRow][currCol] = 'A';
                    }
                    if (currRow + 1 >= 0 && map_[currRow][currCol + 1] == 'h')
                    {
                        increaseHealth();
                        cout << "your have +20 health" << endl;
                    }
                    map_[currRow][currCol] = ' ';
                    currCol++;
                    map_[currRow][currCol] = 'A';
                    attackZombie(currRow,currCol);
                    system("pause");
                }
                break;
                moveZombies(map_, dimX_, dimY_);
                system("cls");
                break;
            case 'q':
                return;

            case 'h':
            {
                help();
            }
            case 'k':
            {
                vector<int> player_status(::user_zombie);
                

                save_game(map_,player_status);
                break;
            }
            }
        }
    }
};
int Mars::health_ = 100;
int Mars::zombie_health_ = 100;
int Mars::zombie_attack_ = 10;
int Mars::zombie_rang_ = 3;
int Mars::attack_ = 30 ;
int Mars::rang_ = 4;

Mars::Mars(int dimX, int dimY)
{
    init(dimX, dimY);
}
void Mars::init(int dimX, int dimY)
{
    dimX_ = dimX;
    dimY_ = dimY;
    char objects[] = {' ', 'h', 'r', ' ', '^', ' ', 'p', ' ', 'v', '>', ' ', '<', ' '};
    int noOfObjects = 12; // number of objects in the objects array
    // create dynamic 2D array using vector
    map_.resize(dimY_); // create empty rows
    for (int i = 0; i < dimY_; ++i)

    {
        map_[i].resize(dimX_); // resize each row
    }
    // put random characters into the vector array
    for (int i = 0; i < dimY_; ++i)
    {
        for (int j = 0; j < dimX_; ++j)
        {
            int objNo = rand() % noOfObjects;
            map_[i][j] = objects[objNo];
            //
        }
    }
}

void Mars::display() const
{
    // comment this out during testing
    // system("cls"); // OR system("clear"); for Linux / MacOS
    cout << " --__--__--__--__--__--__--__--_" << endl;
    cout << " = Alien Vs Zombie=" << endl;
    cout << " __--__--__--__--__--__--__--__-" << endl;
    // for each row
    for (int i = 0; i < dimY_; ++i)
    {
        // display upper border of the row
        cout << " ";
        for (int j = 0; j < dimX_; ++j)
        {
            cout << "+-"
                 << "+-"
                 << "+-";
        }
        cout << "+" << endl;
        // display row number
        cout << setw(2) << (dimY_ - i);
        // display cell content and border of each column
        for (int j = 0; j < dimX_; ++j)
        {
            cout << " "
                 << " | " << map_[i][j];
        }
        cout << "|" << endl;
    }
    // display lower border of the last row
    cout << " ";
    for (int j = 0; j < dimX_; ++j)
    {
        cout << "+-"
             << "+-"
             << "+-";
    }
    cout << "+" << endl;
    // display column number
    cout << "  ";
    for (int j = 0; j < dimX_; ++j)
    {
        int digit = (j + 1) / 10;
        cout << "  ";
        if (digit == 0)
            cout << "  ";
        else
            cout << digit;
    }
    cout << endl;
    cout << " ";
    for (int j = 0; j < dimX_; ++j)
    {
        cout << " " << (j + 1) % 10;
    }

    cout << endl
         << endl;
    cout << "-> Alien  :  Life : " << Mars::health_ <<  "   " <<"  Attack " << Mars::attack_ <<  "   "<<"range" << Mars::rang_ << "\n";

   
        for(int i = 0 ; i < ::user_zombie ; i++){

        cout << "-> zombie" << i + 1 << " :  Life : " << h << "   "<<"  Attack :" << p  << "   " <<"range : " << l << "\n";
    }
}

void test1_1()
{
    Mars mars;

    mars.middle_R();
    mars.add_random_z();
    mars.move_R();
    mars.display();
}

int main()
{

    int setting;
    vector<vector<char>> map;

    setting_screen(user_rows, user_column, user_zombie, map);

    srand(1);
    test1_1();

    return 0;
}

void help()
{
    cout << "+++++++++++++++HELP++++++++++++++++" << endl;
    cout << "1. w - Move Up" << endl;
    cout << "2. s - Move Down" << endl;
    cout << "3. a - Move Lift" << endl;
    cout << "4. d - Move right" << endl;
    cout << "5. arrow - chang the direction for an arrow" << endl;
    cout << "6. h - Display help commands" << endl;
    cout << "7. k - save the game" << endl;
    cout << "8. o - to load the game" << endl;
    cout << "9. q - for quit the game " << endl;
    cout << "+++++++++++++++HELP++++++++++++++++" << endl;
}