#include <iostream>
#include "Graph.h"

int main(int argc, char** argv)
{
	cout << "Graph:" << endl;
	auto graph = Graph("matrix.txt");

	// ����� �����
	auto keys = graph.getKeys();
	for (auto key : keys) {
		cout << key << " -> ";

		for (auto item : graph[key])
			cout << item << " ";

		cout << endl;
	}

	cout << endl;

	// ���������� ���������� ��������� ������
	int from = atoi(argv[1]);
	int to = atoi(argv[2]);
	int counter = 0;

	// ������������� � ����� ����������� ������ ������� ������ � ������� � ������
	cout << "DEEP_SEARCH path to " << to << " -> ";
	for (auto item : graph.deepSearch(from, to, counter))
		cout << item << " ";
	cout << " By " << counter << " steps" << endl << endl;

	counter = 0;

	cout << "WIDTH_SEARCH path to " << to << " -> ";
	for (auto item : graph.widthSearch(from, to, counter))
		cout << item << " ";
	cout << " By " << counter << " steps" << endl;

	return 0;
}
