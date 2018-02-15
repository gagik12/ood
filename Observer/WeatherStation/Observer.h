#pragma once

/*
Шаблонный интерфейс IObserver. Его должен реализовывать класс,
желающий получать уведомления от соответствующего IObservable
Параметром шаблона является тип аргумента,
передаваемого Наблюдателю в метод Update
*/
template <typename T>
class IObserver
{
public:
	virtual void Update(T const& data) = 0;
	virtual ~IObserver() = default;
};

/*
Шаблонный интерфейс IObservable. Позволяет подписаться и отписаться на оповещения, а также
инициировать рассылку уведомлений зарегистрированным наблюдателям.
*/
template <typename T>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<T> & observer, int priority) = 0;
	virtual void NotifyObservers() = 0;
	virtual void RemoveObserver(IObserver<T> & observer) = 0;
};

// Реализация интерфейса IObservable
template <class T>
class CObservable : public IObservable<T>
{
public:
	typedef IObserver<T> ObserverType;

	void RegisterObserver(ObserverType & observer, int priority) override
	{
		m_observersMap.insert(std::make_pair(priority, &observer));
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();
		auto copyObservers = m_observersMap;
		for (auto it = copyObservers.rbegin(); it != copyObservers.rend(); ++it)
		{
			auto observer = it->second;
			observer->Update(data);
		}
	}

	void RemoveObserver(ObserverType & observer) override
	{
		auto it = std::find_if(m_observersMap.begin(), m_observersMap.end(), [&](std::pair<int, ObserverType *> const& observerPair) {
			return observerPair.second == &observer;
		});

		if (it != m_observersMap.end())
		{
			m_observersMap.erase(it);
		}
	}

protected:
	// Классы-наследники должны перегрузить данный метод, 
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData()const = 0;

private:
	std::multimap<int, ObserverType *> m_observersMap;
};