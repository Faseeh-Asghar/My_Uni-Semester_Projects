#include <iostream>
#include <conio.h>  
#include <windows.h>
#include <cstdlib>   
#include <ctime>    
#include<string>
#include <cctype>


using namespace std;



// Constants
const int MAP_WIDTH = 25;
const int MAP_HEIGHT = 25;
const char ASTEROID = 35;
const char BULLET = '|';
const char EMPTY_SPACE = ' ';
const int SPACESHIP_WIDTH = 3;
const char enemy = 69;
const char star = 42;
const char crate = 'C';
const char enemy_bullet = '-';
const int max_num_of_high_scores = 100;
const int boss_bullet = '0';
string highscore_names[max_num_of_high_scores];




// Globals
char gameMap[MAP_HEIGHT][MAP_WIDTH];
int spaceshipX = MAP_WIDTH / 2 - 1; // Center the position horizontally
int spaceshipY = MAP_HEIGHT - 2;   // position in the last row
int score = 0, lives = 3;
bool gameRunning = true;
int crate_count = 0;
int Espeed = 0;
int level = 1;
int enemyDestroy=0;
int bossX = MAP_WIDTH / 2 - 1;
int bossY = MAP_HEIGHT / 2 - 2;
int bossHealth = 100;



// Function Prototypes
void MAIN_GAME();
void initializeMap();
void drawMap();
void placeSpaceShip(int x, int y);
void moveSpaceship(char input);
void clearSpaceShip(int x, int y);
void shootBullet();
void moveBullets();
void generateAsteroids();
void moveAsteroids();
void clearScreen();
void gameOver();
void generate_enemy();
void moveenemy();
void enemyBullets();
void enemyBulletMovement();
void generate_stars();
void move_stars();
void generate_crates();
void move_crates();
void placeBoss(int x, int y);
void bossMovement();
void clearBoss(int x, int y);
bool enemyMovingRight = true;
void hideCursor();
void bossBullet();
void bossBulletMovement();
void exitGame();
void gameCompleted();






void UI() {
    int option;
    cout << "===========================================================";
    cout << endl;
    cout << "        SPACE RANGERS : ALIEN INVASION ";
    cout << endl;
    cout << "===========================================================";
    cout << endl;
    cout << endl;
    cout << "          welcome commander are you ready to save " << endl;;
    cout << "              the galaxy from alien threats?               " << endl;
    cout << endl;
    cout << endl;
    cout << "       1) Play game" << endl;
    cout << "       2) Instructions    " << endl;
    cout << "       3) High scores    " << endl;
    cout << "       4) Exit" << endl;
    cout << endl;
    cout << " Select option (1-4)" << endl;
    while (true) {
        cin >> option;
        if (cin.fail()) {
            cout << "Select option 1-4 only" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else {
            break;
        }
    }
    switch (option)
    {
    case 1:
        system("cls");
        MAIN_GAME();
        break;
    case 2:
        system("cls");
        cout << "=======================================================================";
        cout << endl;
        cout << "                  INSTRUCTIONS " << endl;
        cout << endl;
        cout << "=======================================================================";
        cout << endl;
        cout << " 1. Use the arrow keys to move the spaceship. " << endl;
        cout << " 2. Press spacebar for shooting bullets " << endl;
        cout << " 3. Press 'J' to jump over obstacles temporarily." << endl;
        cout << " 4. Press 'B' to boost speed for a short duration. " << endl;
        cout << " 5. Avoid asteroids and enemy ships to survive." << endl;
        cout << " 6. Collect stars for points and power-ups. " << endl;
        cout << endl << endl;
        cout << "    Your mission is to destroy alien ships,\n dodge hazars, and save the galaxy!";
        cout << endl << endl;
        cout << "========================================================================" << endl;

        cout << "Press backspace to go back or ESC to exit the game." << endl;

        cout << "========================================================================";
        cout << endl;
        while (true) {
            if (_kbhit()) {
                char input = _getch();
                if (input == 8) {
                    system("cls");
                    UI();
                }
                else if (input == 27) {
                    break;
                }
            }
        }
        exitGame();
        break;

    case 3:
        cout << " HIGHSCORE" << endl;
        cout << "Press backspace to go back or ESC to exit the game." << endl;


        while (true) {
            if (_kbhit()) {
                char input = _getch();
                if (input == 8) {             // backspace ascii value  
                    system("cls");
                    UI();
                }
                else if (input == 27) {       // ecs ascii character
                    break;
                }
            }
        }
        exitGame();
        break;
    case 4:
        exitGame();
        break;
    default:
        system("cls");
        cout << "select option 1-4 only" << endl;
        UI();
        break;
    }
}




void MAIN_GAME() {

    srand(time(0));  // dfferent random number generator
    initializeMap();
    int levelInitialize = 0;
    bool isPaused = false; 
    while (gameRunning) {
        clearScreen();
        if (isPaused) {
            cout << "===== GAME PAUSED =====" << endl;
            cout << "Press 'y' to continue or 'n' to quit to the main menu." << endl;

            while (true) {
                if (_kbhit()) {
                    char input = _getch();
                    if (input == 'y') {
                        isPaused = false; // Resume game
                        system("cls");
                        break;
                    }
                    else if (input == 'n') {
                        system("cls");
                        UI(); // Go back to the main menu
                        return;
                    }
                }
            }
        }
        else {
            cout << "================================" << endl;
            cout << "        Game Started\n";
            cout << "================================" << endl;
            if (level == 1 || level == 2) {
                cout << "Score: " << score << " | Lives: " << lives << " | Crate count: " << crate_count << " | Enemyship Destroy: " << enemyDestroy << " | Level: " << level << endl;
            }
            else if (level == 3 || level == 4) {
                cout << "Score: " << score << " | Lives: " << lives << " | Boss Health " << bossHealth << " | Level: " << level << endl;
            }
            
            
            drawMap();

            // Handle input
            if (_kbhit()) {
                char input = _getch();
                if (input == 'q') {
                    gameRunning = false;  // Quit game
                }
                else if (input == ' ') {
                    shootBullet();  // Shoot bullet
                }
                else if (input == 27) {  // 'ESC' key to pause
                    isPaused = true; 
                }
                else {
                    moveSpaceship(input); // Move spaceship
                }
            }


            if (level == 1 || level == 2 ) {
                moveBullets();
                moveAsteroids();
                generateAsteroids();
                generate_enemy();
                moveenemy();
                enemyBullets();
                enemyBulletMovement();
                generate_stars();
                move_stars();
                generate_crates();
                move_crates();
            }
            else if (level == 3) {
                if (levelInitialize == 0) {
                    levelInitialize++;
                    initializeMap();
                }
                moveBullets();
                bossMovement();
                bossBullet();
                bossBulletMovement();
            }
            else if (level == 4) {
                moveBullets();
                bossMovement();
                bossBullet();
                bossBulletMovement();
            }
        }
    }
    if (bossHealth > 0) {
        gameOver();
    }
    else {
        gameCompleted();
    }
}





void initializeMap() {
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            if (i == 0 || i == MAP_HEIGHT - 1 || j == 0 || j == MAP_WIDTH - 1) {
                gameMap[i][j] = '='; // Border
            }
            else {
                gameMap[i][j] = EMPTY_SPACE;
            }
        }
    }
    placeSpaceShip(spaceshipX, spaceshipY);
    if (level == 3) {
        placeBoss(bossX, bossY);
    }
}



void placeBoss(int x, int y) {
    gameMap[y][x] = '(';
    gameMap[y][x + 3] = ')';
    gameMap[y][x + 1] = '^';
    gameMap[y][x + 2] = '^';
}

void clearBoss(int x, int y) {
    gameMap[y][x] = EMPTY_SPACE;
    gameMap[y][x + 3] = EMPTY_SPACE;
    gameMap[y][x + 1] = EMPTY_SPACE;
    gameMap[y][x + 2] = EMPTY_SPACE;
}


void bossMovement() {
    static int speed = 0;
    speed++;
    if (level == 4) {
        speed+=2;
    }
    if (speed > 10) {
        speed = 0;
        clearBoss(bossX, bossY);
        if (bossX > 2 && bossY == MAP_HEIGHT / 2 - 2) {
            bossX--;
        }
        else if (bossX == 2 && bossY>2) {
            bossY--;
        }
        else if (bossX<MAP_WIDTH-5 && bossY==2) {
            bossX++;
        }
        else if (bossX == MAP_WIDTH - 5 && bossY < MAP_HEIGHT / 2 - 2) {
            bossY++;
        }
        placeBoss(bossX, bossY);
    }
}



void bossBullet() {
    static int speed = 0;
    speed++;
    if (level == 4) {
        speed+=2;
    }
    // Fire bullets at a regular interval (adjust 500 as needed for gameplay balance)
    if (speed >= 250) {
        speed = 0;
               if (gameMap[bossY + 1][bossX + 1] == EMPTY_SPACE) {
                    gameMap[bossY + 1][bossX + 1] = boss_bullet; // Fire from left gun
                }
    }
}




void bossBulletMovement() {
    static int speed = 0;
    speed++;
    if (level == 4) {
        speed+=2;
    }
    if (speed >= 10) {
        speed = 0;

        for (int i = MAP_HEIGHT - 2; i > 0; i--) { // Start from the bottom to avoid overwriting during movement
            for (int j = 1; j < MAP_WIDTH - 1; j++) { // Exclude borders
                if (gameMap[i][j] == boss_bullet) { // If the current cell contains a boss bullet
                    // Check if the next position is empty
                    if (gameMap[i + 1][j] == EMPTY_SPACE) {
                        gameMap[i + 1][j] = boss_bullet;  // Move the bullet down
                        gameMap[i][j] = EMPTY_SPACE;  // Clear the old position
                    }
                    // Check if the bullet hits the player (represented by '^', '<', or '>')
                    else if (gameMap[i + 1][j] == '^' || gameMap[i + 1][j] == '<' || gameMap[i + 1][j] == '>') {
                        gameMap[i][j] = EMPTY_SPACE;  // Remove the bullet
                        lives--;  // Decrease player lives
                        if (lives <= 0) {
                            gameRunning = false;  // End the game if lives reach 0
                        }
                    }
                    // Remove the bullet if it hits anything else (e.g., obstacles, walls)
                    else {
                        gameMap[i][j] = EMPTY_SPACE;
                    }
                }
            }
        }
    }
}








// Place the spaceship at a specific position
void placeSpaceShip(int x, int y) {
    gameMap[y][x] = 60;
    gameMap[y][x + 1] = 94;
    gameMap[y][x + 2] = 62;
}




// Clear the spaceship from its current position
void clearSpaceShip(int x, int y) {
    gameMap[y][x] = EMPTY_SPACE;
    gameMap[y][x + 1] = EMPTY_SPACE;
    gameMap[y][x + 2] = EMPTY_SPACE;
}




void moveSpaceship(char input) {
    clearSpaceShip(spaceshipX, spaceshipY); // Clear the spaceship current position

    if (tolower(input) == 'a' && spaceshipX > 1) spaceshipX--;  // Move left
    else if (tolower(input) == 'd' && spaceshipX < MAP_WIDTH - 4) spaceshipX++;  // Move right
    else if (tolower(input) == 'w' && spaceshipY > MAP_HEIGHT - 10) {
        spaceshipY--;
    }
    else if (tolower(input) == 's' && spaceshipY < MAP_HEIGHT - 2) {
        spaceshipY++;
    }
    else if (tolower(input) == 'j' && spaceshipY > MAP_HEIGHT - 7) {
        spaceshipY -= 3;
    }
    placeSpaceShip(spaceshipX, spaceshipY); // Place spaceship at the new position
}




// Draw the game map
void drawMap() {
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            cout << gameMap[i][j];
        }
        cout << endl;
    }
}





// Clear the console screen
void clearScreen() {
    COORD coord = { 0, 0 };
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, coord);
}




// hide the cursor and removing flickering
void hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}







// Shoot a bullet
void shootBullet() {
    if (spaceshipY > 0 && gameMap[spaceshipY - 1][spaceshipX + 1] == EMPTY_SPACE) {
        gameMap[spaceshipY - 1][spaceshipX + 1] = BULLET; // Shoot from the center of the spaceship
    }
}





void moveBullets() {
    for (int i = 1; i < MAP_HEIGHT; i++) { // Start from row 1 to avoid boundary issues
        for (int j = 0; j < MAP_WIDTH; j++) {
            if (gameMap[i][j] == BULLET) {
                // Check if the bullet is going to move outside the map (top boundary)
                if (i - 1 >= 0 && gameMap[i - 1][j] == EMPTY_SPACE) {
                    gameMap[i - 1][j] = BULLET;  // Move the bullet up
                    gameMap[i][j] = EMPTY_SPACE; // Clear the previous position
                }
                else if (i - 1 >= 0 && gameMap[i - 1][j] != EMPTY_SPACE) {
                    // If the bullet hits something (asteroid, enemy, or boundary), remove it
                    if (gameMap[i - 1][j] == ASTEROID) {
                        // Bullet hits an asteroid
                        gameMap[i - 1][j] = EMPTY_SPACE; // Destroy the asteroid
                    }
                    if (gameMap[i - 1][j] == crate)
                    {
                        gameMap[i - 1][j] = EMPTY_SPACE;
                        if (crate_count < 5) {
                            crate_count++;
                        }
                        if (lives < 3) {
                            if (crate_count % 5 == 0) {
                                lives++;
                                crate_count = 0;
                            }
                        }
                    }
                    else if (gameMap[i - 1][j] == enemy) {
                        // Bullet hits an enemy ship
                        gameMap[i - 1][j] = EMPTY_SPACE; // Destroy the enemy ship
                        score += 50;                     // Increase score for destroying enemy
                        enemyDestroy++;
                        if (enemyDestroy >= 10) {
                            if (level == 1) {
                                level++;
                            }
                        }
                        if (enemyDestroy >= 25) {
                            if (level == 2) {
                                level++;
                            }
                        }
                    }
                    else if (gameMap[i - 1][j] == '(' || gameMap[i - 1][j] == '^' || gameMap[i - 1][j] == '^' || gameMap[i - 1][j] == ')'  ) {
                        bossHealth--;
                        if (bossHealth <= 10) {
                            if (level == 3) {
                                level++;
                            }
                        }
                        score += 100;
                        if (bossHealth <= 0) {
                            gameRunning = false;
                        }
                    }
                    gameMap[i][j] = EMPTY_SPACE;         // Destroy the bullet
                }
            }
        }
    }
}






// Generate random asteroids in the first 4 rows
void generateAsteroids() {
    int asteroidCount = 0;
    // Count existing asteroids
    for (int i = 1; i < MAP_HEIGHT - 1; i++) {
        for (int j = 1; j < MAP_WIDTH - 1; j++) {
            if (gameMap[i][j] == ASTEROID) {
                asteroidCount++;
            }
        }
    }
    // Add new asteroids only if less than 5 exist
    while (asteroidCount < 3) {
        int randomRow = rand() % 2 + 1; // Random row between 1 and 4
        int randomCol = rand() % (MAP_WIDTH - 2) + 1; // Random column within bounds

        if (gameMap[randomRow][randomCol] == EMPTY_SPACE) {
            gameMap[randomRow][randomCol] = ASTEROID;
            asteroidCount++;
        }
    }
}





void moveAsteroids() {
    static int speed = 0;
    speed++;
    if (level == 2) {
        speed++;
    }
    if (speed >= 10) {
        speed = 0;
        for (int i = MAP_HEIGHT - 2; i >= 0; i--) { // Start from the second-last row
            for (int j = 1; j < MAP_WIDTH - 1; j++) { // Exclude borders
                if (gameMap[i][j] == ASTEROID) {
                    // Check for collision with spaceship
                    if (i + 1 == spaceshipY && (j >= spaceshipX && j <= spaceshipX + 2)) {
                        // Collision with the spaceship
                        gameMap[i][j] = EMPTY_SPACE;
                        lives--; // Decrease lives
                        Sleep(1000);
                        if (lives <= 0) {
                            gameRunning = false;
                        }
                    }
                    // Move the asteroid downward if no collisions occur
                    else if (gameMap[i + 1][j] == EMPTY_SPACE) {
                        gameMap[i + 1][j] = ASTEROID;
                        gameMap[i][j] = EMPTY_SPACE;
                    }
                    // Remove the asteroid if it reaches the bottom
                    else if (i + 1 == MAP_HEIGHT - 1) {
                        gameMap[i][j] = EMPTY_SPACE;
                    }
                }
            }
        }
    }
}







void generate_enemy() {
    int enemy_count = 0;
    // Count existing enemies
    for (int i = 1; i < MAP_HEIGHT - 1; i++) {
        for (int j = 1; j < MAP_WIDTH - 1; j++) {
            if (gameMap[i][j] == enemy) {
                enemy_count++;
            }
        }
    }
    // Add new enemies only if less than 2 exist
    if (level == 1) {
        while (enemy_count < 2) {
            int randomRow = rand() % 4 + 1; // Random row between 1 and 4
            int randomCol = rand() % (MAP_WIDTH - 2) + 1; // Random column within bounds

            if (gameMap[randomRow][randomCol] == EMPTY_SPACE) {
                gameMap[randomRow][randomCol] = enemy;
                enemy_count++;
            }
        }
    }
    else if (level == 2) {
        while (enemy_count < 4) {
            int randomRow = rand() % 4 + 1; // Random row between 1 and 4
            int randomCol = rand() % (MAP_WIDTH - 2) + 1; // Random column within bounds

            if (gameMap[randomRow][randomCol] == EMPTY_SPACE) {
                gameMap[randomRow][randomCol] = enemy;
                enemy_count++;
            }
        }

    }

}




void moveenemy() {
    static int speed = 0;
    speed++;
    if (level == 2) {
        speed++;
    }
    if (speed >= 10) {  // Move enemies after every 10 iterations
        speed = 0;

        // Check direction and reverse if boundary is reached
        if (enemyMovingRight) {
            for (int i = 1; i < MAP_HEIGHT - 1; i++) {
                if (gameMap[i][MAP_WIDTH - 2] == enemy) {
                    enemyMovingRight = false; // Reverse direction
                    break;
                }
            }
        }
        else {
            for (int i = 1; i < MAP_HEIGHT - 1; i++) {
                if (gameMap[i][1] == enemy) {
                    enemyMovingRight = true; // Reverse direction
                    break;
                }
            }
        }
        // Move enemies
        for (int i = MAP_HEIGHT - 2; i > 0; i--) { // Process bottom-up to avoid overwriting
            for (int j = (enemyMovingRight ? MAP_WIDTH - 2 : 1);
                enemyMovingRight ? j > 0 : j < MAP_WIDTH - 1;
                j += (enemyMovingRight ? -1 : 1)) {
                if (gameMap[i][j] == enemy) {
                    int newJ = enemyMovingRight ? j + 1 : j - 1;
                    if (gameMap[i][newJ] == EMPTY_SPACE) {
                        gameMap[i][newJ] = enemy; // Move enemy
                        gameMap[i][j] = EMPTY_SPACE; // Clear previous position
                    }
                }
            }
        }
    }
}





void enemyBullets() {
    static int speed = 0;
    speed++;

    // Fire bullets at a regular interval (adjust 500 as needed for gameplay balance)
    if (speed >= 250) {
        speed = 0;
        for (int i = 0; i < MAP_HEIGHT - 2; i++) {
            for (int j = 1; j < MAP_WIDTH - 1; j++) { // Exclude the border
                if (gameMap[i][j] == enemy) { // Check if the current cell contains an enemy
                    if (gameMap[i + 1][j] == EMPTY_SPACE) { // Ensure the space below is empty
                        gameMap[i + 1][j] = enemy_bullet; // Place the bullet
                    }
                }
            }
        }
    }
}



void enemyBulletMovement() {
    static int speed = 0;
    speed++;
    if (level == 2) {
        speed++;
    }
    if (speed >= 10) {
        speed = 0;
        for (int i = MAP_HEIGHT - 2; i >= 0; i--) { // Start from the bottom to avoid overwriting bullets
            for (int j = 1; j < MAP_WIDTH - 1; j++) { // Exclude borders
                if (gameMap[i][j] == enemy_bullet) { // If the current cell contains an enemy bullet
                    // Check if the next position is empty
                    if (gameMap[i + 1][j] == EMPTY_SPACE) {
                        gameMap[i + 1][j] = enemy_bullet; // Move the bullet down
                        gameMap[i][j] = EMPTY_SPACE; // Clear the old position
                    }
                    // Check if the bullet collides with the spaceship
                    else if (gameMap[i + 1][j] == '^' || gameMap[i + 1][j] == '<' || gameMap[i + 1][j] == '>') {
                        gameMap[i][j] = EMPTY_SPACE; // Remove the bullet
                        lives--; // Decrease the player's lives
                        if (lives <= 0) {
                            gameRunning = false; // End the game if lives are depleted
                        }
                    }
                    // Remove bullets that hit other obstacles (optional, depending on game design)
                    else {
                        gameMap[i][j] = EMPTY_SPACE;
                    }
                }
            }
        }
    }
}




/// Generate random stars in the first 4 rows

void generate_stars() {
    int star_count = 0;

    // Count existing asteroids
    for (int i = 1; i < MAP_HEIGHT - 1; i++) {
        for (int j = 1; j < MAP_WIDTH - 1; j++) {
            if (gameMap[i][j] == star) {
                star_count++;
            }
        }
    }

    // Add new powerups only if less than 1 exist
    while (star_count < 1) {
        int randomRow = rand() % 2 + 1; // Random row between 1 and 4
        int randomCol = rand() % (MAP_WIDTH - 2) + 1; // Random column within bounds

        if (gameMap[randomRow][randomCol] == EMPTY_SPACE) {
            gameMap[randomRow][randomCol] = star;
            star_count++;
        }
    }
}

// Move stars  downward
void move_stars() {
    static int speed = 0;
    speed++;
    if (level == 2) {
        speed += 3;
    }
    if (speed >= 10) {
        speed = 0;
        for (int i = MAP_HEIGHT - 2; i >= 0; i--) { // Start from the second-last row
            for (int j = 1; j < MAP_WIDTH - 1; j++) { // Exclude borders
                if (gameMap[i][j] == star) {
                    if (gameMap[i + 1][j] == EMPTY_SPACE) {
                        gameMap[i + 1][j] = star; // Move star down
                        gameMap[i][j] = EMPTY_SPACE; // Clear previous position
                    }
                    else if (i + 1 == spaceshipY && (j >= spaceshipX && j <= spaceshipX + 2)) {
                        // Collision with the spaceship
                        gameMap[i][j] = EMPTY_SPACE;
                        score += 20; // Increase score
                    }
                    else if (i + 1 == MAP_HEIGHT - 1) {
                        // Star reaches the bottom
                        gameMap[i][j] = EMPTY_SPACE; // Clear the star
                    }
                }
            }
        }
    }
}




void generate_crates() {
    int con_crate_count = 0;
    // Count existing crates
    for (int i = 1; i < MAP_HEIGHT - 1; i++) {
        for (int j = 1; j < MAP_WIDTH - 1; j++) {
            if (gameMap[i][j] == crate) {
                con_crate_count++;
            }
        }
    }
    // Add new crates only if less than 1 exist
    while (con_crate_count < 1) {
        int randomRow = rand() % 2 + 1;
        int randomCol = rand() % (MAP_WIDTH - 2) + 1; // Random column within bounds

        if (gameMap[randomRow][randomCol] == EMPTY_SPACE) {
            gameMap[randomRow][randomCol] = crate;
            con_crate_count++;
        }
    }
}




void move_crates() {
    static int speed = 0;
    speed++;
    if (level == 2) {
        speed++;
    }
    if (speed >= 10) {
        speed = 0;
        for (int i = MAP_HEIGHT - 2; i >= 0; i--) { // Start from the second-last row
            for (int j = 1; j < MAP_WIDTH - 1; j++) { // Exclude borders
                if (gameMap[i][j] == crate) {
                    if (gameMap[i + 1][j] == EMPTY_SPACE) {
                        gameMap[i + 1][j] = crate; // Move crate down
                        gameMap[i][j] = EMPTY_SPACE; // Clear previous position
                    }
                    // Handle collision with the spaceship
                    else if (i + 1 == spaceshipY && (j >= spaceshipX && j <= spaceshipX + 2)) {
                        gameMap[i][j] = EMPTY_SPACE;
                        lives--; // Decrease lives
                        if (lives <= 0) {
                            gameRunning = false;
                        }
                    }
                    // Clear crate if it reaches the bottom
                    else if (i + 1 == MAP_HEIGHT - 1) {
                        gameMap[i][j] = EMPTY_SPACE; // Clear the crate
                    }
                }
            }
        }
    }
}






// End the game and display the final score
void gameOver() {
    system("cls");
    cout << "Game Over! Your final score is: " << score << endl;
    cout << "Thanks for playing!" << endl;
    UI();
}


void gameCompleted() {
    system("cls");
    cout << "============================================\n";
    cout << endl << endl;
    cout << "            Congratulations!\n";
    cout << "          All Levels Complted\n";
    cout << "         Your final Score is: " << score << endl;
    cout << "=============================================\n";
    Sleep(5000);
}




void exitGame() {
    cout << "Thanks for playing!" << endl;
}



int main() {

    hideCursor();
    UI();
    system("pause");

    return 0;
}