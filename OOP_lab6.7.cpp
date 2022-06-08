#include <iostream>
using namespace std;
// інтерфейс, що описує функтори - унарні предикати
template<class T>
class Predicate
{
public:
	virtual bool operator () (T x) = 0;
};
template<class T>
class Zero : public Predicate<T>
{
public:
	virtual bool operator () (T x)
	{
		T zero = T();
		return x == zero;
	}
};
// реалізуємо інтерфейс функтором - перевірка, чи значення додатне
// працює лише для числових типів
template<class T>
class Positive : public Predicate<T>
{
public:
	virtual bool operator () (T x)
	{
		return x > 0;
	}
};
// реалізуємо інтерфейс функтором - перевірка, чи значення від'ємне
// працює лише для числових типів
template<class T>
class Negative : public Predicate<T>
{
public:
	virtual bool operator () (T x)
	{
		return x < 0;
	}
};

// реалізуємо інтерфейс функтором - перевірка, чи значення парне
// працює лише для цілих типів
template<class T>
class Even : public Predicate<T>
{
public:
	virtual bool operator () (T x)
	{
		return x % 2 == 0;
	}
};
// реалізуємо інтерфейс функтором - перевірка, чи значення не парне
// працює лише для цілих типів
template<class T>
class Odd : public Predicate<T>
{
public:
	virtual bool operator () (T x)
	{
		return x % 2 != 0;
	}
};
template<class T>
void duplicate(T* begin, T* end, T* to)
{
	for (T* from = begin; from < end; from++) // from - ітератор вхідного контейнера
	{ // вказує на поточний елемент
		*to = *from;
		to++;
		*to = *from;
		to++; // два рази скопіювали кожний елемент
	}
}


template<class T>
int duplicate_if(T* begin, T* end, T* to, Predicate<T>& p)
{
	int n = 0; // n - кількість елементів у результуючому контейнері
	for (T* from = begin; from < end; from++) // from - ітератор вхідного контейнера
	{ // вказує на поточний елемент
		*to = *from;
		to++; // скопіювали елемент
		n++;
		if (p(*from)) // якщо справджується умова предикату
		{
			*to = *from;
			to++; // то скопіювали цей елемент ще раз
			n++;
		}
	}
	return n;
}

int main()
{
	int a[5] = { 1, -2, 0, 4, -5 }; // вхідний контейнер
	int b[10], c[10], d[10]; // результуючі контейнери
	// (потрібно виділити достатньо пам'яті)
	for (int i = 0; i < 5; i++)
	{
		cout << a[i] << "   ";
	}
	cout << endl;
	duplicate(&a[2], &a[5], &b[0]); // продублювали всі елементи
	for (int i = 0; i < 10; i++)
		cout << b[i] << ' '; // вивели результат
	cout << endl << endl << endl << endl << endl;
	Predicate<int>* zero = new Zero<int>(); // функтор: "нульові елементи"
	int n = duplicate_if(&a[2], &a[5], &c[0], *zero); // продубювали нульові елементи
	for (int i = 0; i < n; i++)
		cout << c[i] << ' ';
	cout << endl;
	Predicate<int>* pos = new Positive<int>(); // функтор: "додатні елементи"
	int k = duplicate_if(&a[0], &a[5], &d[0], *pos); // продублювали додатні елементи
	for (int i = 0; i < k; i++)
		cout << d[i] << ' ';
	cout << endl;
	system("pause");
	return 0;
}