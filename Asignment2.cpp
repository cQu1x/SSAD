#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
/**
 * @brief Abstract class Animal that describes behaviour of future animals. This class has pure virtual funtion attack,
 * that is going to be overrided in inherited classes
 * @param name Name of the animal
 * @param daysLived describes the age of the animal
 */
class Animal
{
private:
    const string name;
    int daysLived;

public:
    //Default, parameterized and copy constructors
    Animal() = default;

    Animal(const string name, int daysLived)
            : name(name), daysLived(daysLived) {}

    Animal(const Animal &other)
            : name(other.name), daysLived(other.daysLived) {}

    // Destructor
    virtual ~Animal() = default;

    int getDaysLived()
    {
        return daysLived;
    }

    string getName()
    {
        return name;
    }

    /**
     * @brief Method that returns information about animal, which is used for functions Talk and Create
     */
    void sayName()
    {
        cout << "My name is " << name << ", days lived: " << daysLived << endl;
    }

    virtual void attack(Animal &other) = 0;

    void setDaysLived(int newValue)
    {
        this->daysLived = newValue;
    }
    /**
     * @brief Method used to increase age of animals durind "Period" command for convenience
     */
    void incrementDaysLived()
    {
        this->daysLived++;
    }
};
/**
 * @brief Class Fish that virtually inherits Animal to avoid diamond problem. Has default and parameterized
 * constructors with initialization lists from parent class and  overrides "attack" function
 */
class Fish : public virtual Animal
{
public:
    Fish() : Animal() {}

    Fish(const string name, int daysLived)
            : Animal(name, daysLived) {}

    void attack(Animal &other) override
    {
        cout << "Fish is attacking" << endl;
    }
};
/**
 * @brief Class BetterFish that inherits Fish, has constructors with initialization lists
 * and since Fish inherits Animals also implements attack function
 */
class BetterFish : public Fish
{
public:
    BetterFish() : Fish() {}

    BetterFish(string name, int daysLived)
            : Animal(name, daysLived), Fish(name, daysLived) {}

    BetterFish(Fish &other)
            : Animal(other.getName(), other.getDaysLived()), Fish(other.getName(), other.getDaysLived()) {}

    void attack(Animal &other) override
    {
        cout << "BetterFish is attacking" << endl;
    }
};
/**
 * @brief Class Bird that virtually inherits Animal to avoid diamond problem. Has default and parameterized
 * constructors with initialization lists from parent class and  overrides "attack" function
 */
class Bird : public virtual Animal
{
public:
    Bird() : Animal() {}

    Bird(const string name, int daysLived)
            : Animal(name, daysLived) {}

    void attack(Animal &other) override
    {
        cout << "Bird is attacking" << endl;
    }
};
/**
 * @brief Class BetterBird that inherits Bird, has constructors with initialization lists
 * and since Fish inherits Animals also implements attack function
 */
class BetterBird : public Bird
{
public:
    BetterBird() : Bird() {}

    BetterBird(string name, int daysLived)
            : Animal(name, daysLived), Bird(name, daysLived) {}

    BetterBird(Bird &other)
            : Animal(other.getName(), other.getDaysLived()), Bird(other.getName(), other.getDaysLived()) {}

    void attack(Animal &other) override
    {
        cout << "BetterBird is attacking" << endl;
    }
};
/**
 * @brief Class Mouse that virtually inherits Animal to avoid diamond problem. Has default and parameterized
 * constructors with initialization lists from parent class and  overrides "attack" function
 */
class Mouse : public virtual Animal
{
public:
    Mouse() : Animal() {}

    Mouse(const string name, int daysLived)
            : Animal(name, daysLived) {}

    void attack(Animal &other) override
    {
        cout << "Mouse is attacking" << endl;
    }
};
/**
 * @brief Class BetterMouse that inherits Mouse, has constructors with initialization lists
 * and since Fish inherits Animals also implements attack function
 */
class BetterMouse : public Mouse
{
public:
    BetterMouse() : Mouse() {}

    BetterMouse(string name, int daysLived)
            : Animal(name, daysLived), Mouse(name, daysLived) {}

    BetterMouse(Mouse &other)
            : Animal(other.getName(), other.getDaysLived()), Mouse(other.getName(), other.getDaysLived()) {}

    void attack(Animal &other) override
    {
        cout << "BetterMouse is attacking" << endl;
    }
};
/**
 * @brief class Monster inherits all better types since it only can be got by applying substance on better animal.
 * Hence, has constructors with initialization lists from better type classes and parent class Animal
 */
class Monster : public BetterFish, public BetterBird, public BetterMouse
{
public:
    Monster(string name)
            : Animal(name, 1), BetterFish(name, 1), BetterBird(name, 1), BetterMouse(name, 1) {}

    Monster(Animal &animal)
            : Animal(animal)
    {
        setDaysLived(1);
    }

    void attack(Animal &other) override
    {
        cout << "Monster is attacking" << endl;
    }
};
/**
 * @brief Abstract wrapper class that is used to create a vector of all containers and create functions that can applied
 * to all child container classes
 */
class GeneralContainer
{
public:
    virtual void addAnimal(Animal *animal) = 0;
    virtual vector<Animal *> getAnimals() = 0;
    virtual void deleteDeadAnimals() = 0;
    virtual void talk(int index) = 0;
    virtual bool findAnimal(int index) = 0;
    virtual void attack(int pos1, int pos2) = 0;
    virtual void sortContainer() = 0;
};
/**
 * @brief Class that used to generalize all containers methods, but since the class parametric, its properties
 * prohibit creation of vector of Ucontainer type and some functions will also require a parameter. It can be avoided by
 * creating one more class - GeneralContainer.
 * In Ucontainer there implementations of virtual functions of GeneralContainer that are inherited by Cage, Aquarim and
 * freedom
 * @tparam T in this case describes any type of animal
 */
template <typename T>
class UContainer : public GeneralContainer
{
public:
    vector<T *> animals;

    void addAnimal(Animal *animal) override
    {
        T *anim = dynamic_cast<T *>(animal);
        animals.push_back(anim);
    }
/**
 * @return Since any container has a collection of animals this method returns the vector of animals to work with
 */
    vector<Animal *> getAnimals() override
    {
        vector<Animal *> result;
        for (auto anml : animals)
        {
            result.push_back(anml);
        }
        return result;
    }
/**
 * @brief Sorting based on lambda function that prioritizes age of animal and then lexicographic order
 */
    void sortContainer() override
    {
        sort(animals.begin(), animals.end(), [](Animal *a, Animal *b) {
            if (a->getDaysLived() != b->getDaysLived())
                return a->getDaysLived() < b->getDaysLived();
            return a->getName() < b->getName();
        });
    }
/**
 * @brief Function that is used to clear containers from animals, whose age exceeds 10 and from monsters that have
 * lived one day
 */
    void deleteDeadAnimals() override
    {
        int i = 0;
        while (i < animals.size())
        {
            if (animals[i]->getDaysLived() > 10 || (dynamic_cast<Monster *>(animals[i]) != nullptr))
            {
                cout << animals[i]->getName() << " has died of old days" << endl;
                delete animals[i];
                animals.erase(animals.begin() + i);
            }
            else
            {
                i++;
            }
        }
    }
/**
 * @brief function that evokes sayName function in case Animal is found the container
 * @param index - the index of animal in container
 */
    void talk(int index) override
    {
        if (animals.size() < index + 1)
        {
            cout << "Animal not found" << endl;
        }
        else
        {
            animals[index]->sayName();
        }
    }
/**
 * @brief Function that check the existence of animal in container
 * @param index The index of animal to be found
 * @return True if animal was found and false if not
 */
    bool findAnimal(int index) override
    {
        if (animals.size() < index + 1)
        {
            cout << "Animal not found" << endl;
            return false;
        }
        else
        {
            return true;
        }
    }
    /**
     * Function that deletes animal on index pos2 by removing all pointers to it
     * @param pos1 index of attacker
     * @param pos2 index of victim
     */
    void attack(int pos1, int pos2) override
    {
        delete animals[pos2];
        animals.erase(animals.begin() + pos2);
    }
};
// Below there are classes for all containers that inherit abstract and Ucontainer class.
// Since they use the implementation of methods from parent class, they do not require any special methods have
// only constructors. Also Template specification for Aquarium<Bird> and Cage<Fish> prohibit the creation of such objects.
template <typename T>
class Cage : public UContainer<T>
{
public:
    Cage() = default;
};

template <typename T>
class Aquarium : public UContainer<T>
{
public:
    Aquarium() = default;
};

template <>
class Cage<Fish> : public UContainer<Fish>
{
public:
    Cage() = delete;
};

template <>
class Aquarium<Bird> : public UContainer<Bird>
{
public:
    Aquarium() = delete;
};

template <typename A>
class Freedom : public UContainer<A>
{
public:
    Freedom() = default;

    void addAnimal(Animal *animal) override
    {
        this->animals.push_back(animal);
    }
};
//Global declaration of containes to have access to them in all fuctions. It is required becase of the logic of code.
Cage<Bird> birdsCage;
Cage<BetterBird> betBirdsCage;
Cage<Mouse> miceCage;
Cage<BetterMouse> betMiceCage;
Aquarium<Fish> fishAquarium;
Aquarium<BetterFish> betFishAquarium;
Aquarium<Mouse> miceAquarium;
Aquarium<BetterMouse> betMiceAquarium;
Freedom<Animal> freedom;
vector<GeneralContainer *> containers;

/**
 * Function that creates a new animal.
 * @param words string, read from input
 * @brief Such function covers all cases of input, considering its correctness and creates a corresponding animal
 * in respectful container according to input. It also sorts the container to provide correct results in future
 */
void create(vector<string> &words)
{
    if (words.size() == 6 && words[4] == "Cage")
    {
        int days = stoi(words[5]);
        if (words[1] == "B")
        {
            Bird *bird = new Bird(words[2], days);
            birdsCage.addAnimal(bird);
            bird->sayName();
            birdsCage.sortContainer();
        }
        else if (words[1] == "M")
        {
            Mouse *mouse = new Mouse(words[2], days);
            miceCage.addAnimal(mouse);
            mouse->sayName();
            miceCage.sortContainer();
        }
        else if (words[1] == "BB")
        {
            BetterBird *betBird = new BetterBird(words[2], days);
            betBirdsCage.addAnimal(betBird);
            betBird->sayName();
            betBirdsCage.sortContainer();
        }
        else if (words[1] == "BM")
        {
            BetterMouse *betMouse = new BetterMouse(words[2], days);
            betMiceCage.addAnimal(betMouse);
            betMouse->sayName();
            betMiceCage.sortContainer();
        }
    }
    else if (words.size() == 6 && words[4] == "Aquarium")
    {
        int days = stoi(words[5]);
        if (words[1] == "F")
        {
            Fish *fish = new Fish(words[2], days);
            fishAquarium.addAnimal(fish);
            fish->sayName();
            fishAquarium.sortContainer();
        }
        else if (words[1] == "M")
        {
            Mouse *mouse = new Mouse(words[2], days);
            miceAquarium.addAnimal(mouse);
            mouse->sayName();
            miceAquarium.sortContainer();
        }
        else if (words[1] == "BF")
        {
            BetterFish *betFish = new BetterFish(words[2], days);
            betFishAquarium.addAnimal(betFish);
            betFish->sayName();
            betFishAquarium.sortContainer();
        }
        else if (words[1] == "BM")
        {
            BetterMouse *betMouse = new BetterMouse(words[2], days);
            betMiceAquarium.addAnimal(betMouse);
            betMouse->sayName();
            betMiceAquarium.sortContainer();
        }
    }
    else if (words.size() == 6 && words[4] == "Freedom")
    {
        int days = stoi(words[5]);
        if (words[1] == "B")
        {
            Bird *bird = new Bird(words[2], days);
            freedom.addAnimal(bird);
            bird->sayName();
            freedom.sortContainer();
        }
        else if (words[1] == "F")
        {
            Fish *fish = new Fish(words[2], days);
            freedom.addAnimal(fish);
            fish->sayName();
            freedom.sortContainer();
        }
        else if (words[1] == "M")
        {
            Mouse *mouse = new Mouse(words[2], days);
            freedom.addAnimal(mouse);
            mouse->sayName();
            freedom.sortContainer();
        }
        else if (words[1] == "BB")
        {
            BetterBird *betBird = new BetterBird(words[2], days);
            freedom.addAnimal(betBird);
            betBird->sayName();
            freedom.sortContainer();
        }
        else if (words[1] == "BF")
        {
            BetterFish *betFish = new BetterFish(words[2], days);
            freedom.addAnimal(betFish);
            betFish->sayName();
            freedom.sortContainer();
        }
        else if (words[1] == "BM")
        {
            BetterMouse *betMouse = new BetterMouse(words[2], days);
            freedom.addAnimal(betMouse);
            betMouse->sayName();
            freedom.sortContainer();
        }
    }
    else if (words.size() == 5 && words[3] == "Freedom")
    {
        int days = stoi(words[4]);
        Bird *freean = new Bird(words[1], days);
        freean->sayName();
        freedom.addAnimal(freean);
        freedom.sortContainer();
    }
}
/**
 * @brief Fuction that goes though all existing animals and increases their age by one. Also deletes dead animals.
 * @param containers Global vector of all existing containers
 */
void period(vector<GeneralContainer *> containers)
{
    for (auto container : containers)
    {
        for (auto animal : container->getAnimals())
        {
            animal->incrementDaysLived();
        }
        container->deleteDeadAnimals();
        container->sortContainer();
    }
}
/**
 * @brief Function used to make an array out of input string. It takes each symbol and in case of meeting space symbol
 * adds word to output array
 * @param inpstr Input string
 * @return - Returns array split by spaces
 */
vector<string> split(string &inpstr)
{
    string word;
    vector<string> words;

    for (char c : inpstr)
    {
        if (c == ' ')
        {
            words.push_back(word);
            word = "";
        }
        else
        {
            word += c;
        }
    }

    if (!word.empty())
    {
        words.push_back(word);
    }

    return words;
}
/**
 * @brief Function that checks the existence of a attacker and a victim, then invokes attack function from Animal class
 * and outputs corresponding message
 * @param words Split input string
 */
void attack(vector<string> &words)
{
    if (words[1] == "Cage")
    {
        int pos1 = stoi(words[3]);
        int pos2 = stoi(words[4]);

        if (words[2] == "B")
        {
            if (birdsCage.findAnimal(pos1) && birdsCage.findAnimal(pos2))
            {
                birdsCage.attack(pos1, pos2);
                birdsCage.sortContainer();
                cout << "Bird is attacking" << endl;
            }
        }
        else if (words[2] == "M")
        {
            if (miceCage.findAnimal(pos1) && miceCage.findAnimal(pos2))
            {
                miceCage.attack(pos1, pos2);
                miceCage.sortContainer();
                cout << "Mouse is attacking" << endl;
            }
        }
        else if (words[2] == "BB")
        {
            if (betBirdsCage.findAnimal(pos1) && betBirdsCage.findAnimal(pos2))
            {
                betBirdsCage.attack(pos1, pos2);
                betBirdsCage.sortContainer();
                cout << "BetterBird is attacking" << endl;
            }
        }
        else if (words[2] == "BM")
        {
            if (betMiceCage.findAnimal(pos1) && betMiceCage.findAnimal(pos2))
            {
                betMiceCage.attack(pos1, pos2);
                betMiceCage.sortContainer();
                cout << "BetterMouse is attacking" << endl;
            }
        }
    }
    else if (words[1] == "Aquarium")
    {
        int pos1 = stoi(words[3]);
        int pos2 = stoi(words[4]);

        if (words[2] == "F")
        {
            if (fishAquarium.findAnimal(pos1) && fishAquarium.findAnimal(pos2))
            {
                fishAquarium.attack(pos1, pos2);
                fishAquarium.sortContainer();
                cout << "Fish is attacking" << endl;
            }
        }
        else if (words[2] == "M")
        {
            if (miceAquarium.findAnimal(pos1) && miceAquarium.findAnimal(pos2))
            {
                miceAquarium.attack(pos1, pos2);
                miceAquarium.sortContainer();
                cout << "Mouse is attacking" << endl;
            }
        }
        else if (words[2] == "BF")
        {
            if (betFishAquarium.findAnimal(pos1) && betFishAquarium.findAnimal(pos2))
            {
                betFishAquarium.attack(pos1, pos2);
                betFishAquarium.sortContainer();
                cout << "BetterFish is attacking" << endl;
            }
        }
        else if (words[2] == "BM")
        {
            if (betMiceAquarium.findAnimal(pos1) && betMiceAquarium.findAnimal(pos2))
            {
                betMiceAquarium.attack(pos1, pos2);
                betMiceAquarium.sortContainer();
                cout << "BetterMouse is attacking" << endl;
            }
        }
    }
    else if (words[1] == "Freedom")
    {
        cout << "Animals cannot attack in Freedom" << endl;
    }
}

/**
 * @brief Upgrades all common types to better types and all better types to monster. In case of common types halves
 * days lived and moves it to corresponding better type container, in case of better types kills all animals in its
 * container, makes it monster and moves it to freedom. To do so function creates new animal, adds it to required
 * container and an deletes old one.
 * @param words Split input string
 */
void applySubstance(vector<string> &words)
{
    if (words[1] == "Cage")
    {
        int index = stoi(words[3]);

        if (words[2] == "B")
        {
            if (birdsCage.findAnimal(index))
            {
                int days = (birdsCage.animals[index]->getDaysLived() + 1) / 2;
                BetterBird *betBird = new BetterBird(birdsCage.animals[index]->getName(), days);
                betBirdsCage.addAnimal(betBird);
                betBirdsCage.sortContainer();
                delete birdsCage.animals[index];
                birdsCage.animals.erase(birdsCage.animals.begin() + index);
                birdsCage.sortContainer();
            }
        }
        else if (words[2] == "M")
        {
            if (miceCage.findAnimal(index))
            {
                int days = (miceCage.animals[index]->getDaysLived() + 1) / 2;
                BetterMouse *betMouse = new BetterMouse(miceCage.animals[index]->getName(), days);
                betMiceCage.addAnimal(betMouse);
                betMiceCage.sortContainer();
                delete miceCage.animals[index];
                miceCage.animals.erase(miceCage.animals.begin() + index);
                miceCage.sortContainer();
            }
        }
        else if (words[2] == "BB")
        {
            if (betBirdsCage.findAnimal(index))
            {
                Monster *monster = new Monster(betBirdsCage.animals[index]->getName());
                freedom.addAnimal(monster);
                freedom.sortContainer();
                for (auto bird : betBirdsCage.animals)
                {
                    delete bird;
                }
                betBirdsCage.animals.clear();
            }
        }
        else if (words[2] == "BM")
        {
            if (betMiceCage.findAnimal(index))
            {
                Monster *monster = new Monster(betMiceCage.animals[index]->getName());
                freedom.addAnimal(monster);
                freedom.sortContainer();
                for (auto mouse : betMiceCage.animals)
                {
                    delete mouse;
                }
                betMiceCage.animals.clear();
            }
        }
    }
    else if (words[1] == "Aquarium")
    {
        int index = stoi(words[3]);

        if (words[2] == "F")
        {
            if (fishAquarium.findAnimal(index))
            {
                int days = (fishAquarium.animals[index]->getDaysLived() + 1) / 2;
                BetterFish *betFish = new BetterFish(fishAquarium.animals[index]->getName(), days);
                betFishAquarium.addAnimal(betFish);
                betFishAquarium.sortContainer();
                delete fishAquarium.animals[index];
                fishAquarium.animals.erase(fishAquarium.animals.begin() + index);
                fishAquarium.sortContainer();
            }
        }
        else if (words[2] == "M")
        {
            if (miceAquarium.findAnimal(index))
            {
                int days = (miceAquarium.animals[index]->getDaysLived() + 1) / 2;
                BetterMouse *betMouse = new BetterMouse(miceAquarium.animals[index]->getName(), days);
                betMiceAquarium.addAnimal(betMouse);
                betMiceAquarium.sortContainer();
                delete miceAquarium.animals[index];
                miceAquarium.animals.erase(miceAquarium.animals.begin() + index);
                miceAquarium.sortContainer();
            }
        }
        else if (words[2] == "BF")
        {
            if (betFishAquarium.findAnimal(index))
            {
                Monster *monster = new Monster(betFishAquarium.animals[index]->getName());
                freedom.addAnimal(monster);
                freedom.sortContainer();
                for (auto fish : betFishAquarium.animals)
                {
                    delete fish;
                }
                betFishAquarium.animals.clear();
            }
        }
        else if (words[2] == "BM")
        {
            if (betMiceAquarium.findAnimal(index))
            {
                Monster *monster = new Monster(betMiceAquarium.animals[index]->getName());
                freedom.addAnimal(monster);
                freedom.sortContainer();
                for (auto mouse : betMiceAquarium.animals)
                {
                    delete mouse;
                }
                betMiceAquarium.animals.clear();
            }
        }
    }
    else if (words[1] == "Freedom")
    {
        cout << "Substance cannot be applied in freedom" << endl;
    }
}
/**
 * @brief Removes substance from better types and moves such animals to corresponding common type container
 * @param words Split input string
 */
void removeSubstance(vector<string> &words)
{
    if (words[1] == "Cage")
    {
        int index = stoi(words[3]);

        if (words[2] == "B")
        {
            if (birdsCage.findAnimal(index))
            {
                cout << "Invalid substance removal" << endl;
            }
        }
        else if (words[2] == "M")
        {
            if (miceCage.findAnimal(index))
            {
                cout << "Invalid substance removal" << endl;
            }
        }
        else if (words[2] == "BB")
        {
            if (betBirdsCage.findAnimal(index))
            {
                int days = (betBirdsCage.animals[index]->getDaysLived()) * 2;
                Bird *bird = new Bird(betBirdsCage.animals[index]->getName(), days);
                delete betBirdsCage.animals[index];
                betBirdsCage.animals.erase(betBirdsCage.animals.begin() + index);
                birdsCage.addAnimal(bird);
                birdsCage.sortContainer();
                betBirdsCage.sortContainer();
            }
        }
        else if (words[2] == "BM")
        {
            if (betMiceCage.findAnimal(index))
            {
                int days = (betMiceCage.animals[index]->getDaysLived()) * 2;
                Mouse *mouse = new Mouse(betMiceCage.animals[index]->getName(), days);
                delete betMiceCage.animals[index];
                betMiceCage.animals.erase(betMiceCage.animals.begin() + index);
                miceCage.addAnimal(mouse);
                miceCage.sortContainer();
                betMiceCage.sortContainer();
            }
        }
    }
    else if (words[1] == "Aquarium")
    {
        int index = stoi(words[3]);

        if (words[2] == "F")
        {
            if (fishAquarium.findAnimal(index))
            {
                cout << "Invalid substance removal" << endl;
            }
        }
        else if (words[2] == "M")
        {
            if (miceAquarium.findAnimal(index))
            {
                cout << "Invalid substance removal" << endl;
            }
        }
        else if (words[2] == "BF")
        {
            if (betFishAquarium.findAnimal(index))
            {
                int days = (betFishAquarium.animals[index]->getDaysLived()) * 2;
                Fish *fish = new Fish(betFishAquarium.animals[index]->getName(), days);
                delete betFishAquarium.animals[index];
                betFishAquarium.animals.erase(betFishAquarium.animals.begin() + index);
                fishAquarium.addAnimal(fish);
                fishAquarium.sortContainer();
                betFishAquarium.sortContainer();
            }
        }
        else if (words[2] == "BM")
        {
            if (betMiceAquarium.findAnimal(index))
            {
                int days = (betMiceAquarium.animals[index]->getDaysLived()) * 2;
                Mouse *mouse = new Mouse(betMiceAquarium.animals[index]->getName(), days);
                delete betMiceAquarium.animals[index];
                betMiceAquarium.animals.erase(betMiceAquarium.animals.begin() + index);
                miceAquarium.addAnimal(mouse);
                miceAquarium.sortContainer();
                betMiceAquarium.sortContainer();
            }
        }
    }
    else if (words[1] == "Freedom")
    {
        cout << "Substance cannot be removed in freedom" << endl;
    }
}
/**
 * @brief Invokes talk method for corresponding type of animal according to the input
 * @param words Split input string
 */
void talk(vector<string> &words)
{
    if (words.size() == 4 && words[1] == "Cage")
    {
        int index = stoi(words[3]);

        if (words[2] == "B")
        {
            birdsCage.talk(index);
        }
        else if (words[2] == "M")
        {
            miceCage.talk(index);
        }
        else if (words[2] == "BB")
        {
            betBirdsCage.talk(index);
        }
        else if (words[2] == "BM")
        {
            betMiceCage.talk(index);
        }
    }
    else if (words.size() == 4 && words[1] == "Aquarium")
    {
        int index = stoi(words[3]);

        if (words[2] == "F")
        {
            fishAquarium.talk(index);
        }
        else if (words[2] == "M")
        {
            miceAquarium.talk(index);
        }
        else if (words[2] == "BF")
        {
            betFishAquarium.talk(index);
        }
        else if (words[2] == "BM")
        {
            betMiceAquarium.talk(index);
        }
    }
    else if (words.size() == 4 && words[1] == "Freedom")
    {
        int index = stoi(words[2]);
        freedom.talk(index);
    }
    else if (words.size() == 3 && words[1] == "Freedom")
    {
        int index = stoi(words[2]);
        freedom.talk(index);
    }
}

int main()
{
    //Merging the global container vector
    containers.push_back(&birdsCage);
    containers.push_back(&betBirdsCage);
    containers.push_back(&miceCage);
    containers.push_back(&betMiceCage);
    containers.push_back(&fishAquarium);
    containers.push_back(&betFishAquarium);
    containers.push_back(&miceAquarium);
    containers.push_back(&betMiceAquarium);
    containers.push_back(&freedom);

    int n;
    cin >> n;
    cin.ignore();
    //Invoking corresponding functions according to input
    for (int i = 0; i < n; i++)
    {
        string input;
        getline(cin, input);
        vector<string> words = split(input);

        if (words[0] == "CREATE")
        {
            create(words);
        }
        else if (words[0] == "APPLY_SUBSTANCE")
        {
            applySubstance(words);
        }
        else if (words[0] == "REMOVE_SUBSTANCE")
        {
            removeSubstance(words);
        }
        else if (words[0] == "ATTACK")
        {
            attack(words);
        }
        else if (words[0] == "TALK")
        {
            talk(words);
        }
        else if (words[0] == "PERIOD")
        {
            period(containers);
        }
    }
    return 0;
}