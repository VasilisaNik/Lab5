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


// Реализация паттерна "Стратегия"

enum class PlayingMannerEnum : int
{
  Phone,
  PC,
  PS,

  None
};


class PlayingStrategy
{
public:
  virtual ~PlayingStrategy() {}
  virtual void Play() = 0;
};


class PhonePlayingStrategy : public PlayingStrategy
{
  void Play() { cout << "Have fun playing on phone..."; }
};

class PCPlayingStrategy : public PlayingStrategy
{
  void Play() { cout << "Have fun playing on PC..."; }
};

class PSPlayingStrategy : public PlayingStrategy
{
  void Play() { cout << "Have fun playing on PS..."; }
};


// Фабричный метод для создания стратегий
PlayingStrategy *CreatePlayingStrategy(PlayingMannerEnum playingManner)
{
  switch(playingManner)
  {
    case PlayingMannerEnum::Phone: return new PhonePlayingStrategy;
    case PlayingMannerEnum::PC: return new PCPlayingStrategy;
    case PlayingMannerEnum::PS: return new PSPlayingStrategy;
    default: return nullptr;
  }
}


class Game
{
private:
    GameRating Rating;

    PlayingStrategy *PlayingManner;

    void DoPlayUsingStrategy()
    {
      if(PlayingManner == nullptr)
      {
        // Способ съедания не задан, ничего не делаем
        cout << "Nothing";
        return;
      }
      else
      {
        // Съесть заданным способом
        PlayingManner->Play();
      }
    }

    void DetectFreeOrNot()
    {
      if(IsFree())
      {
          cout << "Free";
      }
      else
      {
          cout << "No Free";
      }
    }

protected:


public:
    bool GameIsFree;
    string Genre;
    GameRazmer Razmer;

   Game(GameRating rating, GameRazmer razmer) : Rating(rating), Razmer(razmer), GameIsFree(false), Genre(""), PlayingManner(nullptr)
   {
   }

    virtual ~Game() // Деструктор
    {
      if(PlayingManner != nullptr) delete PlayingManner;
    }

    bool IsFree() const { return GameIsFree; }

    GameRazmer GetRazmer() const { return Razmer; }

    GameRating GetRating() const { return Rating; }

    virtual void PrintType() = 0;

    virtual void Buy() = 0;

    void Play()
    {
        // 1. Вывести название игры
        PrintType();
        cout << " : ";

        // 2. Определить, бесплатная игра или нет
        DetectFreeOrNot();
        cout << " : ";

        // 2.1 Купить игру
        Buy();
        cout << " : ";

        // 3. Если хороший, съесть с использованием выбранной стратегии
        DoPlayUsingStrategy();

        // 4. Конец алгоритма
        cout << endl;
    }

    void SetPlayingManner(PlayingStrategy *playingManner) { PlayingManner = playingManner; }

};


class HonkaiStarRail : public Game
{
public:
    HonkaiStarRail();
    ~HonkaiStarRail();

    double GetRazmer() const;

    void Play();

    void PrintType() { cout << "HonkaiStarRail"; }
    void Buy() { cout << "Buying a game in the Play Market"; }
};

// Реализация конструктора
HonkaiStarRail::HonkaiStarRail() : Game(GameRating::Fifty_second, GameRazmer::Mnogo)
{
    GameIsFree = true; // Инициализация FruitIsGood через присваивание

    // Определить стратегию съедания по умолчанию для яблока (вариант 1)
    SetPlayingManner(CreatePlayingStrategy(PlayingMannerEnum::Phone));
}

HonkaiStarRail::~HonkaiStarRail()
{
    cout << "Deleting Honkai: Star Rail..." << endl;
}

void HonkaiStarRail::Play()
{
    cout << "Play the Honkai: Star Rail..." << endl;
}


class GenshinImpact : public Game
{
public:
    GenshinImpact();
    ~GenshinImpact();

    void Play();

    void PrintType() { cout << "GenshinImpact"; }
    void Buy() { cout << "Buying a game in the Play Station Store"; }

};

GenshinImpact::GenshinImpact() : Game(GameRating::Second, GameRazmer::Ochen_mnogo)
{
    Genre = "Role-playing";
    GameIsFree = true;

    SetPlayingManner(CreatePlayingStrategy(PlayingMannerEnum::PS));
}

GenshinImpact::~GenshinImpact()
{
    cout << "Deleting Genshin Impact..." << endl;
}



void GenshinImpact::Play()
{
    cout << "Play the Genshin Impact..." << endl;
}


class WutheringWaves : public Game
{
public:
    WutheringWaves();
    ~WutheringWaves();

    double GetRazmer() const;

    void Play();

    void PrintType() { cout << "WutheringWaves"; }
    void Buy() { cout << "Buying a game in the Steam"; }
};


WutheringWaves::WutheringWaves() : Game(GameRating::Hundredth, GameRazmer::Malo)
{
    GameIsFree = true;

    SetPlayingManner(CreatePlayingStrategy(PlayingMannerEnum::PC));
}

WutheringWaves::~WutheringWaves()
{
    cout << "Deleting Wuthering Waves..." << endl;
}


void WutheringWaves::Play()
{
    cout << "Play the Wuthering Waves" << endl;
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
    PlayAll(freeIt);
    delete freeIt;

    wcout << endl << L"Скачиваем во все игры с рейтингом 52:" << endl;
    Iterator<Game*> *fifIt = new GameRatingDecorator(gameArray.GetIterator(), GameRating::Fifty_second);
    PlayAll(fifIt);
    delete fifIt;

    wcout << endl << L"Играем во все бесплатные игры с рейтингом 52:" << endl;
    Iterator<Game*> *freeFifIt =
        new GameFreeDecorator(new GameRatingDecorator(gameArray.GetIterator(), GameRating::Fifty_second), true);
    PlayAll(freeFifIt);
    delete freeFifIt;

    wcout << endl << L"Запускаем все очень большие игры:" << endl;
    Iterator<Game*> *ochenIt = new GameRazmerDecorator(gameArray.GetIterator(), GameRazmer::Ochen_mnogo);
    PlayAll(ochenIt);
    delete ochenIt;

    // Демонстрация работы адаптера
    wcout << endl << L"Устанавливаем все бесплатные игры с рейтингом 100 с помощью adapted iterator (другой контейнер):" << endl;
    Iterator<Game*> *adaptedIt = new ConstIteratorAdapter<std::list<Game*>, Game*>(&gameVector);
    Iterator<Game*> *adaptedHunIt = new GameFreeDecorator(new GameRatingDecorator(adaptedIt, GameRating::Hundredth), true);
    PlayAll(adaptedHunIt);
    delete adaptedHunIt;


}
