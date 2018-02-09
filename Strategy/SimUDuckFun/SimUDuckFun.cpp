#include "stdafx.h"

using namespace std;

typedef std::function<void()> FlyBehaviorFun;
typedef std::function<void()> DanceBehaviorFun;
typedef std::function<void()> QuackBehaviorFun;

namespace DanceBehavior
{
	const DanceBehaviorFun WALTZ_DANCE = []() {
		cout << "Dancing waltz" << endl;
	};
	const DanceBehaviorFun MINUET_DANCE = []() {
		cout << "Dancing minuet" << endl;
	};
	const DanceBehaviorFun NO_DANCE = []() {
		cout << "Men don't dance" << endl;
	};
}

namespace QuackBehavior
{
	const QuackBehaviorFun SQUEAK = []() {
		cout << "Squeak!!!" << endl;
	};
	const QuackBehaviorFun QUACK = []() {
		cout << "Quack Quack!!!" << endl;
	};
	const QuackBehaviorFun MUTE_QUACK = []() {
	};
}

namespace FlyBehavior
{
	const FlyBehaviorFun FLY_NO_WAY = []() {
	};

	FlyBehaviorFun FlyWithWings()
	{
		return [flyCounter = 0]() mutable
		{
			++(flyCounter);
			cout << "I'm flying with wings! Flight counts: " << flyCounter << endl;
		};
	}

	FlyBehaviorFun FlyWithRocketEngine()
	{
		return[flyCounter = 0]() mutable
		{
			++(flyCounter);
			cout << "I'm flying with rocket engine! Flight counts: " << flyCounter << endl;
		};
	}
}

class Duck
{
public:
	Duck(FlyBehaviorFun const& flyBehavior,
		QuackBehaviorFun const& quackBehavior,
		DanceBehaviorFun const& danceBehavior)
		: m_quackBehavior(quackBehavior)
		, m_danceBehavior(danceBehavior)
	{
		SetFlyBehavior(flyBehavior);
	}
	virtual ~Duck() = default;
	void Quack() const
	{
		m_quackBehavior();
	}
	void Swim()
	{
		cout << "I'm swimming" << endl;
	}
	void Fly()
	{
		m_flyBehavior();
	}
	void Dance()
	{
		m_danceBehavior();
	}
	void SetFlyBehavior(FlyBehaviorFun const& flyBehavior)
	{
		m_flyBehavior = flyBehavior;
	}

	virtual void Display() const = 0;
private:
	FlyBehaviorFun m_flyBehavior;
	QuackBehaviorFun m_quackBehavior;
	DanceBehaviorFun m_danceBehavior;
};

class MallardDuck : public Duck
{
public:
	MallardDuck()
		: Duck(FlyBehavior::FlyWithWings(),
			QuackBehavior::QUACK,
			DanceBehavior::WALTZ_DANCE)
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
		: Duck(FlyBehavior::FlyWithWings(),
			QuackBehavior::QUACK,
			DanceBehavior::MINUET_DANCE)
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
		: Duck(FlyBehavior::FLY_NO_WAY,
			QuackBehavior::MUTE_QUACK,
			DanceBehavior::NO_DANCE)
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
		: Duck(FlyBehavior::FLY_NO_WAY,
			QuackBehavior::SQUEAK,
			DanceBehavior::NO_DANCE)
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
		: Duck(FlyBehavior::FLY_NO_WAY,
			QuackBehavior::QUACK,
			DanceBehavior::NO_DANCE)
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

	modelDuck.SetFlyBehavior(FlyBehavior::FlyWithRocketEngine());
	PlayWithDuck(modelDuck);
	PlayWithDuck(modelDuck);

	modelDuck.SetFlyBehavior(FlyBehavior::FLY_NO_WAY);
	PlayWithDuck(modelDuck);
}
