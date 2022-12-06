class Dice {
    private:
    int min1;
    int max1;
    
    public:
    Dice(int min1, int max1) {
        this->min1 = min1;
        this->max1 = max1;
    }
    
    int roll() {
        return min1 + rand()%(max1 - min1 + 1);
    }
};

class Snake {
    private:
    int start;
    int end;
    
    public:
    Snake(int start, int end) {
        this->start = start;
        this->end = end;
    }
    
    int getStart() {
        return start;
    }
    
    int getEnd() {
        return end;
    }
};

class Ladder {
    private:
    int start;
    int end;
    
    public:
    Ladder(int start, int end) {
        this->start = start;
        this->end = end;
    }
    
    int getStart() {
        return start;
    }
    
    int getEnd() {
        return end;
    }
};

class Player {
    private:
    string name;
    int pos;
    int rank;
    
    public:
    Player(string name) {
        this->name = name;
        this->pos = 0;
        this->rank = -1;
    }
    
    string getName() {
        return name;
    }
    
    void setPos(int pos) {
        this->pos = pos;
    }
    
    int getPos() {
        return pos;
    }
    
    void setRank(int rank) {
        this->rank = rank;
    }

    int getRank() {
        return rank;
    }
};

class Board {
    private:
    int start;
    int end;
    int size;
    
    public:
    Board(int size) {
        this->start = 1;
        this->end = size;
        this->size = size;
    }
    
    int getStart() {
        return start;
    }
    
    int getEnd() {
        return end;
    }
    
    int getSize() {
        return size;
    }
};

class Game {
    private:
    vector<Snake*> snakes;
    vector<Ladder*> ladders;
    queue<Player*> players;
    Board *board;
    Dice *dice;
    int numPlayers;
    
    int getFinalPos(int start) {
        for(auto &x : snakes) {
            if(x->getStart() == start) {
                return x->getEnd();
            }
        }
        for(auto &x : ladders) {
            if(x->getStart() == start) {
                return x->getEnd();
            }
        }
        return start;
    }
    
    void printBoard() {
        cout<<"SNAKES:\n";
        for(auto &x : snakes) {
            cout<<x->getStart()<<" "<<x->getEnd()<<"\n";
        }
        cout<<"\nLADDERS\n";
        for(auto &x : ladders) {
            cout<<x->getStart()<<" "<<x->getEnd()<<"\n";
        }
        cout<<"\n";
    }
    
    void initBoard() {
        unordered_set<int> starts, ends;
        for(auto &x : ladders) {
            while(1) {
                int start = board->getStart() + rand()%(board->getSize()-1);
                int end = start + 1 + rand()%(board->getSize()-start);
                if(starts.find(start) == starts.end()
                   && starts.find(end) == starts.end()
                   && ends.find(start) == ends.end()) {
                    starts.insert(start);
                    ends.insert(end);
                    x = new Ladder(start, end);
                    break;
                }
            }
        }
        for(auto &x : snakes) {
            while(1) {
                int start = board->getStart() + 1 + rand()%(board->getSize() - 1);
                int end = board->getStart() + rand()%(start-1);
                if(starts.find(start) == starts.end()
                   && starts.find(end) == starts.end()
                   && ends.find(start) == ends.end()) {
                    starts.insert(start);
                    ends.insert(end);
                    x = new Snake(start, end);
                    break;
                }
            }
        }
        printBoard();
    }
    
    public:
    Game(int numSnakes, int numLadders, int boardSize) {
        snakes = vector<Snake*>(numSnakes);
        ladders = vector<Ladder*>(numLadders);
        board = new Board(boardSize);
        dice = new Dice(1, 6);
        numPlayers = 0;
        initBoard();
    }
    
    void addPlayer(string name) {
        players.push(new Player(name));
        numPlayers++;
    }
    
    void play() {
        while(1) {
            Player *player = players.front();
            players.pop();
            int n = dice->roll();
            cout<<player->getName()<<"'s turn:\n";
            cout<<n<<" rolled\n";
            cout<<player->getPos();
            int newPos = player->getPos() + n;
            if(newPos < board->getSize()) {
                cout<<" -> "<<newPos;
                int newPos1 = getFinalPos(newPos);
                if(newPos != newPos1) {
                    cout<<" -> "<<newPos1;
                }
                player->setPos(newPos1);
                players.push(player);
            } else if(newPos == board->getSize()) {
                cout<<" -> "<<newPos;
                player->setPos(newPos);
                player->setRank(numPlayers - players.size());
                cout<<"\n"<<player->getName()<<" WON!!! RANK: "<<player->getRank()<<"\n";
            } else {
                players.push(player);
            }
            cout<<"\n\n";
            if(players.size() == 1) {
                break;
            }
        }
    }
    
};

int main() {
    srand((unsigned int)time(NULL));
    Game *game = new Game(10, 10, 100);
    
    game->addPlayer("A");
    game->addPlayer("B");
    game->addPlayer("C");
    
    game->play();
}
