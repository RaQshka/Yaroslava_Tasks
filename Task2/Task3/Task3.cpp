#include <iostream>    // Для работы с вводом и выводом
#include <vector>      // Для работы с динамическими массивами (векторами)
#include <algorithm>   // Для использования алгоритмов STL
#include <bitset>      // Для работы с битовыми наборами

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

// Функция для проверки, покрывает ли множество вершин все вершины графа
bool isCover(const vector<vector<int>>& adjMatrix, const bitset<32>& subset) {
    int n = adjMatrix.size();
    vector<bool> covered(n, false);  // Вектор для отслеживания покрытых вершин

    // Проверка, какие вершины покрыты множеством
    for (int i = 0; i < n; ++i) {
        if (subset[i]) {  // Если вершина включена в подмножество
            for (int j = 0; j < n; ++j) {
                if (adjMatrix[i][j] == 1) {
                    covered[j] = true;  // Вершина j покрыта
                }
            }
        }
    }

    // Проверка, все ли вершины графа покрыты
    return all_of(covered.begin(), covered.end(), [](bool v) { return v; });
}

// Функция для поиска минимального покрытия вершин
vector<int> findMinimumVertexCover(vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<int> bestSet;  // Лучшее найденное покрытие
    int minSize = n + 1;  // Начальная минимальная размерность (больше, чем возможно)

    // Перебор всех возможных подмножеств вершин
    for (int i = 1; i < (1 << n); ++i) {
        bitset<32> subset(i);  // Создание битового набора для подмножества
        if (isCover(adjMatrix, subset)) {  // Проверка, является ли подмножество покрытием
            int setSize = subset.count();  // Размер текущего подмножества
            if (setSize < minSize) {  // Обновление наименьшего покрытия
                minSize = setSize;
                bestSet.clear();
                for (int j = 0; j < n; ++j) {
                    if (subset[j]) {
                        bestSet.push_back(j);  // Добавление вершины в минимальное покрытие
                    }
                }
            }
        }
    }

    return bestSet;
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

    // Поиск минимального покрытия вершин
    vector<int> minCover = findMinimumVertexCover(adjMatrix);

    // Вывод результата
    cout << "Минимальное множество вершин, покрывающее все вершины графа:\n";
    for (int vertex : minCover) {
        cout << vertex << " ";  // Вывод вершин минимального покрытия
    }
    cout << "\nЧисло внешней устойчивости графа: " << minCover.size() << endl;  // Вывод размера покрытия

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