//Археолог нашел N артефактов.Известны веса(сi) и ценности(di) артефактов.Нужно
//выбрать такое подмножество найденных вещей, чтобы суммарный их вес не превысил Z кг, а их
//общая ценность оказалась максимальной.Известно, что решение единственно.Укажите поряд
//ковые номера вещей, которые нужно взять.Исходный данные находятся в текстовом файле, в
//первой строке указаны N и Z, а во второй строке значения весов(в кг), в третьей - ценность
//находок.Вывести так же суммарный вес и общую ценность результата.

//FIX_ME: Исправлены отступы с табуцляции на 2 пробела

#include <iostream>
#include <vector>

//FIX_ME: Отсутствуют нужные заголовки для используемых сущностей
#include <algorithm>
#include <fstream>
#include <string>
#include <utility>

//FIX_ME: Добавлена структура, которая хранит номер, вес и ценность предмета
struct Artifact {
  int weight;
  int value;
  int original_index;
};

//FIX_ME: Функция не сохраняла исходные индексы, т.к. работала с 2 вектроами
//Удалена, т.к. для работы сортировать не нужно
//void insert_sort(std::vector<int>& w, std::vector<int>& p) {
//   for (int i = 1; i < w.size(); i++) {
//        int temp = i;
//        while (temp - 1 >= 0 && w[temp] < w[temp - 1]) {
//            std::swap(w[temp], w[temp - 1]);
//            std::swap(p[temp], p[temp - 1]);
//            temp--;
//        }
//        
//    }
//}

//FIX_ME: Функция возвращала только ценность
//Использовались короткие имена параметров
//int backpack(int W, std::vector<int>& wt, std::vector<int>& val, int n) {
//
//    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(W + 1));
//    // Заполнение таблицы
//    for (int i = 0; i <= n; i++) {
//        for (int w = 0; w <= W; w++) {
//            if (i == 0 || w == 0)
//                dp[i][w] = 0; // нет предметов или вес рюкзака равен 0
//            else if (wt[i - 1] <= w)
//                // Выбор между включением и исключением текущего предмета
//                dp[i][w] = std::max(val[i - 1] + dp[i - 1][w - wt[i - 1]], dp[i - 1][w]);
//            else
//                // Текущий предмет не вмещается в рюкзак
//                dp[i][w] = dp[i - 1][w];
//        }
//    }
//    return dp[n][W];
//}
std::pair<int, std::vector<int>> Knapsack(
  int capacity,
  const std::vector<Artifact>& artifacts) {
  const int n = static_cast<int>(artifacts.size());

  std::vector<std::vector<int>> dp(n + 1, std::vector<int>(capacity + 1, 0));

  for (int i = 1; i <= n; ++i) {
    for (int w = 0; w <= capacity; ++w) {
      dp[i][w] = dp[i - 1][w];
      if (artifacts[i - 1].weight <= w) {
        const int with_item = artifacts[i - 1].value +
          dp[i - 1][w - artifacts[i - 1].weight];
        if (with_item > dp[i][w]) {
          dp[i][w] = with_item;
        }
      }
    }
  }

  std::vector<int> chosen_indices;
  int w = capacity;
  for (int i = n; i > 0; --i) {
    if (dp[i][w] != dp[i - 1][w]) {
      chosen_indices.push_back(artifacts[i - 1].original_index);
      w -= artifacts[i - 1].weight;
    }
  }

  std::reverse(chosen_indices.begin(), chosen_indices.end());

  return { dp[n][capacity], chosen_indices };
}

//FIX_ME: Данные должны читаться из файла. Добалена проверка на успешность чтения
bool ReadFromFile(const std::string& filename,
  int& n,
  int& capacity,
  std::vector<Artifact>& artifacts) {
  std::ifstream input(filename);
  if (!input.is_open()) {
    return false;
  }

  if (!(input >> n >> capacity) || n <= 0 || capacity <= 0) {
    return false;
  }

  std::vector<int> weights(n);
  std::vector<int> values(n);

  for (int i = 0; i < n; ++i) {
    if (!(input >> weights[i])) {
      return false;
    }
  }
  for (int i = 0; i < n; ++i) {
    if (!(input >> values[i])) {
      return false;
    }
  }

  artifacts.resize(n);
  for (int i = 0; i < n; ++i) {
    artifacts[i] = { weights[i], values[i], i + 1 };
  }
  return true;
}

int main()
{
  setlocale(LC_ALL, "ru");

  //FIX_ME: Данные должны читаться из файла
  //int n, W;
  //
  //do {
  //  std::cout << "Введите объем рюкзака >=0 ";
  //  std::cin >> W;
  //} while (W <= 0);
  //
  //do {
  //  std::cout << "Введите кол-во артефактов >=0 ";
  //  std::cin >> n;
  //} while (n <= 0);
  //
  //
  //std::cout << "Поочередно вводите параметры артефактов";
  //
  //std::vector<int> profit(n);
  //std::vector<int> weight(n);
  const std::string kFilename = "input.txt";

  int n = 0;
  int capacity = 0;
  std::vector<Artifact> artifacts;

  //FIX_ME: Добавлена проверка на успешность чтения данных
  if (!ReadFromFile(kFilename, n, capacity, artifacts)) {
    std::cerr << "Не удалось прочитать файл " << kFilename << std::endl;
    return 1;
  }

  //FIX_ME: Сортировка ломала индексы предметов
  //insert_sort(weight, profit);
  //std::vector<Artifact> sorted = artifacts;
  //InsertSort(sorted);

  //FIX_ME: Программа выводила только максимальную ценность без номеров вещей,
  //  сумарного веса и общей ценности
  //std::cout << "Максимальная возможная стоимость вещей, уместимых в рюкзак: " << backpack(W, weight, profit, n) << std::endl;
  const auto result = Knapsack(capacity, artifacts);
  const int max_value = result.first;
  const std::vector<int>& chosen = result.second;

  int total_weight = 0;
  for (int idx : chosen) {
    total_weight += artifacts[idx - 1].weight;
  }

  std::cout << "Порядковые номера выбранных артефактов: ";
  for (size_t i = 0; i < chosen.size(); ++i) {
    if (i > 0) {
      std::cout << ", ";
    }
    std::cout << chosen[i];
  }
  std::cout << std::endl;

  std::cout << "Суммарный вес: " << total_weight << " кг" << std::endl;
  std::cout << "Общая ценность: " << max_value << std::endl;

  return 0;
}
