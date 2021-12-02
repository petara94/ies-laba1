#include "Graph.h"

Graph::Graph()
{
	graph = map<int, vector<int>>();
}

Graph::Graph(string filepath) :Graph() {
	ifstream file(filepath.c_str());

	if (file.bad()) {
		cout << "Matrix file not found";
		exit(404);
	}

	int size;
	file >> size;
	int node_level = 0;
	int current_node = 0;
	while (!file.eof()) {
		if (current_node == size) {
			current_node = 0;
			node_level++;
		}
		int node_flag;
		file >> node_flag;
		if (node_flag)
			addPair(node_level, current_node);
		current_node++;
	}

	file.close();
}

Graph::~Graph()
{
}

vector<int> Graph::widthSearch(int from, int to, int& counter)
{
	// Выходной массив
	auto res = vector<int>();

	// Очередь вершин для прохождения алгоритмом широкого поиска
	auto deq = vector<mypair>();

	// Добавление исзодной точки
	deq.push_back(mypair(from, -1));

	// индекс цикла
	int node_i = 0;

	// Флаг - найдена ли целевая вершина
	bool is_found = false;

	// Алкгоритм поиска
	for (; node_i != deq.size(); ++node_i) {
		// Если вершина не целевая
		if (deq.at(node_i).value != to) {
			auto childs = graph[deq.at(node_i).value];

			// Добавть в конец потомков если их нет в очереди
			for (auto&& child : childs) {
				if (find_if(deq.begin(), deq.end(), [&](mypair arg) {
					return child == arg.value;
					}) == deq.end())
					deq.push_back(mypair(child, node_i));
			}
		}
		// Найдена целевая вершина
		else {
			is_found = true;
			break;
		}
	}

	counter = node_i;

	// Если нет пути то вернуть пустой массив
	if (!is_found)
		return res;


	// Построение пути
	res.push_back(deq.at(node_i).value);
	while (deq.at(node_i).parent >= 0) {
		res.insert(res.begin(), deq.at(deq.at(node_i).parent).value);
		node_i = deq.at(node_i).parent;
	}

	return res;
}

vector<int> Graph::deepSearch(int from, int to, int& counter)
{
	++counter;
	auto res = vector<int>();

	auto nodes = graph[from];

	// Если исходная вершина пуста - вернуть пустой массив
	if (nodes.size() == 0)
		return res;

	// Если среди потомков есть целевая вершина то вернуть массив 2-ух элементов
	if (find(nodes.begin(), nodes.end(), to) != nodes.end())
	{
		res.push_back(from);
		res.push_back(to);
		return res;
	}

	// Рекурсивный алгоритм поиска в глубину
	for (auto node : nodes) {

		// Найти путь от потомка до целевой вершины
		auto tmp = deepSearch(node, to, counter);

		// Среди потомков потомка нет целевой вершины
		if (tmp.size() == 0)
			continue;
		// Целевая вершина найдена. Компоновка и возврат выходного массива
		else {
			res.push_back(from);
			res.insert(res.end(), tmp.begin(), tmp.end());
			return res;
		}
	}

	// Ничего не нашел
	return res;
}

vector<int> Graph::getKeys()
{
	auto res = vector<int>();

	for (auto it : graph)
		res.push_back(it.first);

	return res;
}

void Graph::addPair(int from, int to)
{
	graph[from].push_back(to);
}

vector<int>& Graph::operator[](int& arg)
{
	return graph[arg];
}
