#ifndef PATTERNTEMPLATES_H_INCLUDED
#define PATTERNTEMPLATES_H_INCLUDED
#include <vector>
#include <iostream>
#include <list>

using namespace std;

const size_t MaxSize = 50;

template<typename T>
class Iterator
{
protected:
    Iterator() {}
public:
    virtual ~Iterator() {}
    virtual void First() = 0;
    virtual void Next() = 0;
    virtual bool IsDone() const = 0;
    virtual T GetCurrent() const = 0;
};


template<typename T>
class ArrayIterator : public Iterator<T>
{
private:
    const T *ArrayContainer;
    size_t Pos;
    size_t Size; // Размер массива
public:
    ArrayIterator(T *container, size_t size) : ArrayContainer(container), Pos(0), Size(size) {}
    void First() override {Pos = 0;}
    void Next() override {Pos++; }
    bool IsDone() const  override {return (Pos >= Size); }
    T GetCurrent() const override {return ArrayContainer[Pos]; }
};


template<typename T>
class VectorIterator : public Iterator<T>
{
private:
    const T *VectorContainer;
    size_t Pos;
    size_t Size;
public:
    VectorIterator(T *container, size_t size) : VectorContainer(container), Pos(0), Size(size) {}
    void First() override {Pos = 0;}
    void Next() override {Pos++; }
    bool IsDone() const  override {return (Pos >= Size); }
    T GetCurrent() const override {return VectorContainer[Pos]; }
};

template <typename T>
class ArrayClass
{
private:
    T Items[MaxSize];
    size_t ArraySize;
public:
    void Add(T newObject) { Items[ArraySize++] = newObject; }
    size_t Size() const { return ArraySize; }
    T operator[](size_t index) const { return Items[index]; }
    T GetElement(size_t index) const { return Items[index]; }
    // Получить итератор для обхода контейнера
    class Iterator<T> *GetIterator()
    {
        return new ArrayIterator<T>(Items, ArraySize);
    };

    ArrayClass() : ArraySize(0) {}
};


template <typename T>
class VectorClass
{
private:
    vector<T> Items;
public:
    size_t Size() const { return Items.size(); }
    void Push(T newObject) {Items.push_back(newObject);}
    T First() {return Items.front();}
    T Back() {return Items.back();}
    T operator[](size_t index) const { return Items[index]; }
    T GetElement(size_t index) const {return Items[index];}
    class Iterator<T> *GetIterator()
    {
        return new VectorIterator<T>(Items, Items.size());
    };

};

// Декоратор для итератора
template<typename T>
class IteratorDecorator : public Iterator<T>
{
protected:
    Iterator<T> *It;

public:
    IteratorDecorator(Iterator<T> *it) : It(it) {}
    virtual ~IteratorDecorator() { delete It; }
    virtual void First() { It->First(); }
    virtual void Next() { It->Next(); }
    virtual bool IsDone() const { return It->IsDone(); }
    virtual T GetCurrent() const { return It->GetCurrent(); }
};

// Адаптер для контейнерных классов STL
template<typename ContainerType, typename ItemType>
class ConstIteratorAdapter : public Iterator<ItemType>
{
protected:
    ContainerType *Container;
    typename ContainerType::const_iterator It;

public:
    ConstIteratorAdapter(ContainerType *container)
    : Container(container)
    {
        It = Container->begin();
    }

    virtual ~ConstIteratorAdapter() {}
    virtual void First() { It = Container->begin(); }
    virtual void Next() { It++; }
    virtual bool IsDone() const { return (It == Container->end()); }
    virtual ItemType GetCurrent() const { return *It; }
};

#endif // PATTERNTEMPLATES_H_INCLUDED
