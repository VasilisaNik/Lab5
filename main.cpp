#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "PatternTemplates.h"
#include <vector>
#include <list>

using namespace std;

enum class GameRating : int
{
    Second,
    Fifty_second,
    Hundredth,
    Unknown
};

enum class GameRazmer : int
{
    Malo,
    Mnogo,
    Ochen_mnogo,
    Unknown
};

class Game
{
private:
    GameRating Rating;

protected:


public:
    bool GameIsFree;
    string Genre;
    GameRazmer Razmer;

   Game(GameRating rating, GameRazmer razmer) : Rating(rating), Razmer(razmer), GameIsFree(false), Genre("")
   {
   }

    virtual ~Game(); // Деструктор

    bool IsFree() const { return GameIsFree; }

    GameRazmer GetRazmer() const { return Razmer; }

    GameRating GetRating() const { return Rating; }

    virtual void Instal() = 0;
    virtual void Play() = 0;
    virtual void Start() = 0;
};


// Реализация деструктора
Game::~Game()
{
    cout << "Deleting the game..." << endl;
}

class HonkaiStarRail : public Game
{
public:
    HonkaiStarRail();
    ~HonkaiStarRail();

    double GetRazmer() const;

    void Instal();
    void Play();
    void Start();
};

// Реализация конструктора
HonkaiStarRail::HonkaiStarRail() : Game(GameRating::Fifty_second, GameRazmer::Mnogo)
{
    GameIsFree = true; // Инициализация FruitIsGood через присваивание
    //Razmer = 24;

    cout << "Creating Honkai: Star Rail..." << endl;
}

// Реализация деструктора
HonkaiStarRail::~HonkaiStarRail()
{
    cout << "Deleting Honkai: Star Rail..." << endl;
}

/*double HonkaiStarRail::GetRazmer() const
{
    // Дополнительный функционал, которого не было в родительском классе
    cout << "Honkai: Star Rail size on PC: " << Game::GetRazmer() << endl;

    // Вызываем реализацию из родительского класса
    return Game::GetRazmer();
}*/

void HonkaiStarRail::Instal()
{
    cout << "Instal the Honkai: Star Rail..." << endl;
}

void HonkaiStarRail::Play()
{
    cout << "Play the Honkai: Star Rail..." << endl;
}

void HonkaiStarRail::Start()
{
    cout << "Start the Honkai: Star Rail..." << endl;
}


class GenshinImpact : public Game
{
public:
    GenshinImpact();
    ~GenshinImpact();

    void Instal();
    void Start();
    void Play();
};

GenshinImpact::GenshinImpact() : Game(GameRating::Second, GameRazmer::Ochen_mnogo)
{
    Genre = "Role-playing";
    GameIsFree = true;
    //Razmer = 45.0;

    cout << "Creating Genshin Impact..." << endl;
}

GenshinImpact::~GenshinImpact()
{
    cout << "Deleting Genshin Impact..." << endl;
}

void GenshinImpact::Instal()
{
    cout << "Instal the Genshin Impact..." << endl;
}

void GenshinImpact::Play()
{
    cout << "Play the Genshin Impact..." << endl;
}

void GenshinImpact::Start()
{
    cout << "Start the Genshin Impact..." << endl;
}



class WutheringWaves : public Game
{
public:
    WutheringWaves();
    ~WutheringWaves();

    double GetRazmer() const;

    void Instal();
    void Play();
    void Start();
};

WutheringWaves::WutheringWaves() : Game(GameRating::Hundredth, GameRazmer::Malo)
{
    GameIsFree = true;
    //Razmer = 26.0;
    Genre = "Role-playing";

    cout << "Creating Wuthering Waves" << endl;
}

WutheringWaves::~WutheringWaves()
{
    cout << "Deleting Wuthering Waves..." << endl;
}

/*double WutheringWaves::GetRazmer() const
{
    cout << "Wuthering Waves size on PC: " << Game::GetRazmer() << endl;

    return Game::GetRazmer();
}*/

void WutheringWaves::Instal()
{
    cout << "Instal the Wuthering Waves" << endl;
}

void WutheringWaves::Play()
{
    cout << "Play the Wuthering Waves" << endl;
}

void WutheringWaves::Start()
{
    cout << "Start the Wuthering Waves..." << endl;
}

// Реализация паттерна "Фабричный метод" для создания фруктов

enum class GameType : int
{
    GenshinImpact = 1,
    HonkaiStarRail = 2,
    WutheringWaves = 3,

    Undefined = 0 // На всякий случай
};


Game *CreateGame(GameType type)
{
    Game *newGame = nullptr;

    if(type == GameType::GenshinImpact)
    {
        newGame = new GenshinImpact;
    }
    else if(type == GameType::HonkaiStarRail)
    {
        newGame = new HonkaiStarRail;
    }
    else if(type == GameType::WutheringWaves)
    {
        newGame = new WutheringWaves;
    }

    return newGame;
}


// Декоратор итератора для выделения фруктов по цвету
class GameRatingDecorator : public IteratorDecorator<class Game*>
{
private:
    GameRating TargetRating;

public:
    GameRatingDecorator(Iterator<Game*> *it, GameRating rating)
    : IteratorDecorator<Game*>(it), TargetRating(rating) {}

    void First()
    {
        It->First();
        while(!It->IsDone() && It->GetCurrent()->GetRating() != TargetRating)
        {
            It->Next();
        }
    }

    void Next()
    {
        do
        {
            It->Next();

        } while(!It->IsDone() && It->GetCurrent()->GetRating() != TargetRating);
    }
};

// Декоратор итератора для выделения бесплатных или платных игр
class GameFreeDecorator : public IteratorDecorator<class Game*>
{
private:
    bool TargetFree;

public:
    GameFreeDecorator(Iterator<Game*> *it, bool isFree)
    : IteratorDecorator<Game*>(it), TargetFree(isFree) {}

    void First()
    {
        It->First();
        while(!It->IsDone() && It->GetCurrent()->IsFree() != TargetFree)
        {
            It->Next();
        }
    }

    void Next()
    {
        do
        {
            It->Next();

        } while(!It->IsDone() && It->GetCurrent()->IsFree() != TargetFree);
    }
};

// Декоратор итератора для выделения игр по размеру
class GameRazmerDecorator : public IteratorDecorator<class Game*>
{
private:
    GameRazmer TargetRazmer;

public:
    GameRazmerDecorator(Iterator<Game*> *it, GameRazmer razmer)
    : IteratorDecorator<Game*>(it), TargetRazmer(razmer) {}

    void First()
    {
        It->First();
        while(!It->IsDone() && It->GetCurrent()->GetRazmer() != TargetRazmer)
        {
            It->Next();
        }
    }

    void Next()
    {
        do
        {
            It->Next();

        } while(!It->IsDone() && It->GetCurrent()->GetRazmer() != TargetRazmer);
    }
};


void PlayAll(Iterator<Game*> *it)
{
    for(it->First(); !it->IsDone(); it->Next())
    {
        Game *currentGame = it->GetCurrent();
        currentGame->Play();
    }
}

void InstallAll(Iterator<Game*> *it)
{
    for(it->First(); !it->IsDone(); it->Next())
    {
        Game *currentGame = it->GetCurrent();
        currentGame->Instal();
    }
}

void StartAll(Iterator<Game*> *it)
{
    for(it->First(); !it->IsDone(); it->Next())
    {
        Game *currentGame = it->GetCurrent();
        currentGame->Start();
    }
}

int main()
{
    setlocale(LC_ALL, "RUS");

    size_t N = 7;

    // Массив
    ArrayClass<Game*> gameArray;
    for(size_t i=0; i<N; i++)
    {
        int game_num = rand()%3+1; // Число от 1 до 3 (случайный фрукт)
        GameType game_type = static_cast<GameType>(game_num);
        Game *newGame = CreateGame(game_type);
        gameArray.Add(newGame);
    }

    wcout << L"Размер массива игр: " << gameArray.Size() << endl << endl;

    // Связанный список фруктов (для демонстрации адаптера)
    list<Game*> gameVector;
    for(size_t i=0; i<N; i++)
    {
        int game_num = rand()%3+1;
        GameType game_type = static_cast<GameType>(game_num);
        Game *newGame = CreateGame(game_type);
        gameVector.push_back(newGame);
    }

    wcout << L"Размер списка игр: " << gameVector.size() << endl;

    // Обход всех элементов при помощи итератора
    wcout << endl << L"Играем во всё с помощью итератора:" << endl;
    Iterator<Game*> *allIt = gameArray.GetIterator();
    PlayAll(allIt);
    delete allIt;

    wcout << endl << L"Запускаем все бесплатные игры с помощью итератора:" << endl;
    Iterator<Game*> *freeIt = new GameFreeDecorator(gameArray.GetIterator(), true);
    StartAll(freeIt);
    delete freeIt;

    wcout << endl << L"Скачиваем во все игры с рейтингом 52:" << endl;
    Iterator<Game*> *fifIt = new GameRatingDecorator(gameArray.GetIterator(), GameRating::Fifty_second);
    InstallAll(fifIt);
    delete fifIt;

    wcout << endl << L"Играем во все бесплатные игры с рейтингом 52:" << endl;
    Iterator<Game*> *freeFifIt =
        new GameFreeDecorator(new GameRatingDecorator(gameArray.GetIterator(), GameRating::Fifty_second), true);
    PlayAll(freeFifIt);
    delete freeFifIt;

    wcout << endl << L"Запускаем все очень большие игры:" << endl;
    Iterator<Game*> *ochenIt = new GameRazmerDecorator(gameArray.GetIterator(), GameRazmer::Ochen_mnogo);
    StartAll(ochenIt);
    delete ochenIt;

    // Демонстрация работы адаптера
    wcout << endl << L"Устанавливаем все бесплатные игры с рейтингом 100 с помощью adapted iterator (другой контейнер):" << endl;
    Iterator<Game*> *adaptedIt = new ConstIteratorAdapter<std::list<Game*>, Game*>(&gameVector);
    Iterator<Game*> *adaptedHunIt = new GameFreeDecorator(new GameRatingDecorator(adaptedIt, GameRating::Hundredth), true);
    InstallAll(adaptedHunIt);
    delete adaptedHunIt;


}
