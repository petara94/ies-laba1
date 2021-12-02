#pragma once
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

/// <summary>
/// Класс графа с методами поиска путей между вершинами
/// </summary>
class Graph {
private:
	map<int, vector<int>> graph;

public:
	Graph();
	/// <summary>
	/// загружает граф из матрицы смежности в файле
	/// </summary>
	/// <param name="filepath">файл с матрицой смежности</param>
	Graph(string filepath);
	virtual ~Graph();

	/// <summary>
	/// Поиск в ширину
	/// </summary>
	/// <param name="from">Начальная вершина</param>
	/// <param name="to">Целевая вершина</param>
	/// <returns>Путь от начальной к целевой вершине</returns>
	vector<int> widthSearch(int from, int to, int& counter);

	/// <summary>
	/// Поиск в глубину
	/// </summary>
	/// <param name="from">Начальная вершина</param>
	/// <param name="to">Целевая вершина</param>
	/// <returns>Путь от начальной к целевой вершине</returns>
	vector<int> deepSearch(int from, int toSearch, int& counter);

	/// <summary>
	/// Получить список вершин
	/// </summary>
	/// <returns>Список вершин</returns>
	vector<int> getKeys();

	/// <summary>
	/// Добавляет элементы в граф соединяя их
	/// </summary>
	/// <param name="from">Вершина, от которой исходит связь</param>
	/// <param name="to">Вершина, к которой приходит связь</param>
	void addPair(int from, int to);

	vector<int>& operator[](int& arg);
};

/// <summary>
/// структура для удобства 
/// </summary>
struct mypair
{
	/// <summary>
	/// значение пары
	/// </summary>
	int value;

	/// <summary>
	/// индекс родителя в очереди
	/// </summary>
	int parent;

	mypair(int v, int p) {
		value = v;
		parent = p;
	}
};