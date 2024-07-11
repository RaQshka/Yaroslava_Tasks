#include <iostream>
#include <vector>

using namespace std;

// Функция для построения матрицы смежности из списка рёбер
vector<vector<int>> buildAdjacencyMatrix(int n, vector<pair<int, int>>& edges) {
    vector<vector<int>> adjMatrix(n, vector<int>(n, 0));  // Инициализация матрицы смежности нулями

    // Заполнение матрицы смежности на основе списка рёбер
    for (pair<int, int>& edge : edges) {
        adjMatrix[edge.first][edge.second] = 1;  // Установка связи между вершинами
        adjMatrix[edge.second][edge.first] = 1;  // Граф неориентированный, связь двусторонняя
    }
    return adjMatrix;
}

// Функция для проверки, является ли множество вершин независимым
bool isIndependentSet(const vector<vector<int>>& adjMatrix, const vector<int>& subset) {
    int n = adjMatrix.size();

    // Проверка, нет ли смежных вершин в подмножестве
    for (int i = 0; i < n; ++i) {
        if (subset[i]) {  // Если вершина включена в подмножество
            for (int j = i + 1; j < n; ++j) {
                if (subset[j] && adjMatrix[i][j] == 1) {  // Если вершина j также включена и смежна с i
                    return false;  // Не является независимым множеством
                }
            }
        }
    }

    return true;  // Независимое множество
}

// Функция для поиска максимального независимого множества
vector<int> findMaximumIndependentSet(vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<int> bestSet(n, 0);  // Лучшее найденное независимое множество
    int maxSize = 0;  // Начальный максимальный размер - ноль

    // Перебор всех возможных подмножеств вершин
    for (int i = 1; i < (1 << n); ++i) {
        vector<int> subset(n, 0);  // Создание подмножества
        int count = 0;

        for (int j = 0; j < n; ++j) {
            if (i & (1 << j)) {
                subset[j] = 1;  // Добавление вершины в подмножество
                count++;
            }
        }

        if (isIndependentSet(adjMatrix, subset)) {  // Проверка, является ли подмножество независимым
            if (count > maxSize) {  // Обновление наибольшего независимого множества
                maxSize = count;
                bestSet = subset;
            }
        }
    }

    // Создание списка вершин на основе лучшего найденного подмножества
    vector<int> result;
    for (int i = 0; i < n; ++i) {
        if (bestSet[i]) {
            result.push_back(i);
        }
    }

    return result;
}

// Функция для ввода готовой матрицы смежности
vector<vector<int>> inputAdjacencyMatrix(int n) {
    vector<vector<int>> adjMatrix(n, vector<int>(n));

    cout << "Введите матрицу смежности (" << n << " x " << n << "):\n";

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> adjMatrix[i][j];  // Ввод значений матрицы смежности
        }
    }
    return adjMatrix;
}

int main() {
    // Ввод данных
    setlocale(0, "");
    int n, m, choice;  // Переменные для количества вершин, рёбер и выбора способа ввода

    cout << "Выберите способ ввода графа:\n";
    cout << "1. Ввести список рёбер\n";
    cout << "2. Ввести матрицу смежности\n";
    cin >> choice;

    vector<vector<int>> adjMatrix;  // Матрица смежности

    // Обработка выбора способа ввода
    if (choice == 1) {
        cout << "Введите количество вершин и рёбер: ";
        cin >> n >> m;
        vector<pair<int, int>> edges(m);
        cout << "Введите рёбра (пары вершин):\n";
        for (int i = 0; i < m; ++i) {
            cin >> edges[i].first >> edges[i].second;  // Ввод рёбер
        }
        adjMatrix = buildAdjacencyMatrix(n, edges);  // Построение матрицы смежности
    }
    else if (choice == 2) {
        cout << "Введите количество вершин: ";
        cin >> n;
        adjMatrix = inputAdjacencyMatrix(n);  // Ввод матрицы смежности
    }
    else {
        cout << "Некорректный выбор.\n";
        return 1;  // Завершение программы с кодом ошибки
    }
    // Построение матрицы смежности
    cout << "\nМатрица смежности: \n";
    for (int i = 0; i < adjMatrix.size(); i++) {
        for (int j = 0; j < adjMatrix[i].size(); j++) {
            cout << adjMatrix[i][j] << "\t";  // Вывод матрицы смежности
        }
        cout << endl;
    }

    // Поиск максимального независимого множества
    vector<int> maxIndependentSet = findMaximumIndependentSet(adjMatrix);

    // Вывод результата
    cout << "Максимальное независимое множество вершин графа:\n";
    for (int vertex : maxIndependentSet) {
        cout << vertex << " ";  // Вывод вершин максимального независимого множества
    }
    cout << "\nЧисло внешней устойчивости графа: " << maxIndependentSet.size() << endl;  // Вывод размера независимого множества

    return 0;
}
/********************************************************************/
/*5 7
0 1
1 2
0 3
3 4
3 1
4 1
4 2
*/