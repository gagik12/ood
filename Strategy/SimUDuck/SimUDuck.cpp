#include "stdafx.h"

using namespace std;

struct IFlyBehavior
{
	virtual ~IFlyBehavior() {};
	virtual void Fly() = 0;
protected:
	int m_flyCounter = 0;
};

class FlyWithWings : public IFlyBehavior
{
public:
	void Fly() override
	{
		++m_flyCounter;
		cout << "I'm flying with wings! Flight counts: " << m_flyCounter << endl;
	}
};
class FlyWithRocketEngine : public IFlyBehavior
{
public:
	void Fly() override
	{
		++m_flyCounter;
		cout << "I'm flying with rocket engine! Flight counts: " << m_flyCounter << endl;
	}
};

class FlyNoWay : public IFlyBehavior
{
public:
	void Fly() override {}
};

struct IDanceBehavior
{
	virtual ~IDanceBehavior() = default;
	virtual void Dance() = 0;
};
class WaltzDanceBehavior : public IDanceBehavior
{
public:
	void Dance() override
	{
		cout << "Dancing waltz" << endl;
	}
};

class MinuetDanceBehavior : public IDanceBehavior
{
public:
	void Dance() override
	{
		cout << "Dancing minuet" << endl;
	}
};

class NoDanceBehavior : public IDanceBehavior
{
public:
	void Dance() override
	{
		cout << "Men don't dance" << endl;
	}
};

struct IQuackBehavior
{
	virtual ~IQuackBehavior() {};
	virtual void Quack() = 0;
};

class QuackBehavior : public IQuackBehavior
{
public:
	void Quack() override
	{
		cout << "Quack Quack!!!" << endl;
	}
};
class SqueakBehavior : public IQuackBehavior
{
public:
	void Quack() override
	{
		cout << "Squeak!!!" << endl;
	}
};

class MuteQuackBehavior : public IQuackBehavior
{
public:
	void Quack() override {}
};

class Duck
{
public:
	Duck(unique_ptr<IFlyBehavior>&& flyBehavior,
		unique_ptr<IQuackBehavior>&& quackBehavior,
		unique_ptr<IDanceBehavior>&& danceBehavior)
		: m_quackBehavior(move(quackBehavior))
		, m_danceBehavior(move(danceBehavior))
	{
		assert(m_quackBehavior);
		SetFlyBehavior(move(flyBehavior));
	}
	virtual ~Duck() = default;
	void Quack() const
	{
		m_quackBehavior->Quack();
	}
	void Swim()
	{
		cout << "I'm swimming" << endl;
	}
	void Fly()
	{
		m_flyBehavior->Fly();
	}
	void Dance()
	{
		m_danceBehavior->Dance();
	}
	void SetFlyBehavior(unique_ptr<IFlyBehavior>&& flyBehavior)
	{
		assert(flyBehavior);
		m_flyBehavior = move(flyBehavior);
	}

	virtual void Display() const = 0;
private:
	unique_ptr<IFlyBehavior> m_flyBehavior;
	unique_ptr<IQuackBehavior> m_quackBehavior;
	unique_ptr<IDanceBehavior> m_danceBehavior;
};

class MallardDuck : public Duck
{
public:
	MallardDuck()
		: Duck(make_unique<FlyWithWings>(),
			make_unique<QuackBehavior>(),
			make_unique<WaltzDanceBehavior>())
	{
	}

	void Display() const override
	{
		cout << "I'm mallard duck" << endl;
	}
};

class RedheadDuck : public Duck
{
public:
	RedheadDuck()
		: Duck(make_unique<FlyWithWings>(),
			make_unique<QuackBehavior>(),
			make_unique<MinuetDanceBehavior>())
	{
	}
	void Display() const override
	{
		cout << "I'm redhead duck" << endl;
	}
};

class DeckoyDuck : public Duck
{
public:
	DeckoyDuck()
		: Duck(make_unique<FlyNoWay>(),
			make_unique<MuteQuackBehavior>(),
			make_unique<NoDanceBehavior>())
	{
	}
	void Display() const override
	{
		cout << "I'm deckoy duck" << endl;
	}
};

class RubberDuck : public Duck
{
public:
	RubberDuck()
		: Duck(make_unique<FlyNoWay>(),
			make_unique<SqueakBehavior>(),
			make_unique<NoDanceBehavior>())
	{
	}
	void Display() const override
	{
		cout << "I'm rubber duck" << endl;
	}
};

class ModelDuck : public Duck
{
public:
	ModelDuck()
		: Duck(make_unique<FlyNoWay>(),
			make_unique<QuackBehavior>(),
			make_unique<NoDanceBehavior>())
	{
	}
	void Display() const override
	{
		cout << "I'm model duck" << endl;
	}
};

void DrawDuck(Duck const& duck)
{
	duck.Display();
}

void PlayWithDuck(Duck& duck)
{
	DrawDuck(duck);
	duck.Quack();
	duck.Fly();
	duck.Dance();
	cout << endl;
}

void main()
{
	MallardDuck mallarDuck;
	PlayWithDuck(mallarDuck);

	RedheadDuck redheadDuck;
	PlayWithDuck(redheadDuck);

	RubberDuck rubberDuck;
	PlayWithDuck(rubberDuck);

	DeckoyDuck deckoyDuck;
	PlayWithDuck(deckoyDuck);

	ModelDuck modelDuck;
	PlayWithDuck(modelDuck);

	modelDuck.SetFlyBehavior(make_unique<FlyWithRocketEngine>());
	PlayWithDuck(modelDuck);
	PlayWithDuck(modelDuck);

	modelDuck.SetFlyBehavior(make_unique<FlyNoWay>());
	PlayWithDuck(modelDuck);
}
