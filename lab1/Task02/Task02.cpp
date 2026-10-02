//Хромой король.На квадратной доске расставлены монеты, достоинством от 1 до 100. 
//Хромой король, находящийся в правом нижнем углу, мечтает попасть в левый верхний.
//При этом он может передвигаться только в клетку слева или сверху и хочет, чтобы сумма всех
//монет, оказавшихся у него на пути, была бы максимальной.Определить эту сумму и путь, каким
//образом должен двигаться король, чтобы ее собрать.Ввод и вывод организовать при помощи
//текстовых файлов.Формат входных данных : в первой строке входного файла записано число 
//N - размер доски(1 < N < 80).Далее следует N строк, каждая из которых содержит N целых чисел,
//представляющих доску.В первую строку выходного файл нужно вывести единственное число :
//максимальную сумму, а во второй строке вывести путь в виде строки символов, обозначив сим
//волом L движение влево, а символом U - движение вверх.


//FIX_ME: Исправлены отступы с табуцляции на 2 пробела

#include <fstream>  
#include <iostream>  
#include <vector>  
#include <string>
//FIX_ME: Добавлен <algorithm> для std::reverse
#include <algorithm>

//FIX_ME: Убрано использование "using namespace std;"
//using namespace std;

//FIX_ME: Убрано использование глобальной переменной 'n'
//int n;

//FIX_ME: Использовались короткие имена параметров
//void Solve(vector<vector<int>>& a, vector<vector<int>>& b, vector<vector<char>>& put)
//{
//  int max;
//  b[n - 1][n - 1] = a[n - 1][n - 1];
//  for (int i = n - 2;i >= 0;i--)
//  {
//    b[i][n - 1] = b[i + 1][n - 1] + a[i][n - 1];
//    put[i][n - 1] = 'U';
//  }
//  for (int j = n - 2;j >= 0;j--)
//  {
//    b[n - 1][j] = b[n - 1][j + 1] + a[n - 1][j];
//    put[n - 1][j] = 'L';
//  }
//  for (int i = n - 2;i >= 0;i--)
//  {
//    for (int j = n - 2;j >= 0;j--)
//    {
//      if (b[i + 1][j] > b[i][j + 1])
//      {
//        max = b[i + 1][j];
//        put[i][j] = 'U';
//      }
//      else
//      {
//        max = b[i][j + 1];
//        put[i][j] = 'L';
//      }
//      b[i][j] = max + a[i][j];
//    }
//  }
//}
void Solve(const std::vector<std::vector<int>>& board,
  std::vector<std::vector<int>>& best,
  std::vector<std::vector<char>>& move) {
  const int n = static_cast<int>(board.size());

  best[n - 1][n - 1] = board[n - 1][n - 1];

  // Правый столбец: единственный путь — вниз по i.
  for (int i = n - 2; i >= 0; --i) {
    best[i][n - 1] = best[i + 1][n - 1] + board[i][n - 1];
    move[i][n - 1] = 'U';
  }

  // Нижняя строка: единственный путь — вправо по j.
  for (int j = n - 2; j >= 0; --j) {
    best[n - 1][j] = best[n - 1][j + 1] + board[n - 1][j];
    move[n - 1][j] = 'L';
  }

  // Основная часть.
  for (int i = n - 2; i >= 0; --i) {
    for (int j = n - 2; j >= 0; --j) {
      if (best[i + 1][j] > best[i][j + 1]) {
        best[i][j] = best[i + 1][j] + board[i][j];
        move[i][j] = 'U';
      }
      else {
        best[i][j] = best[i][j + 1] + board[i][j];
        move[i][j] = 'L';
      }
    }
  }
}

//FIX_ME: Имя функции не соответствует. Использовались короткие имена параметров
//В цикле while при некоректном move[i][j] цикл мог зависать
//Путь выводился с пробелами между символов
//void p(vector<vector<char>>& put, string& put1)
//{
//  int i = 0;
//  int j = 0;
//  while (i < n - 1 || j < n - 1)
//  {
//    if (put[i][j] == 'U')
//    {
//      put1 = put1 + "U ";
//      i++;
//    }
//    else if (put[i][j] == 'L')
//    {
//      put1 = put1 + "L ";
//      j++;
//    }
//  }
//  reverse(put1.begin(), put1.end());
//}
std::string BuildPath(const std::vector<std::vector<char>>& move) {
  const int n = static_cast<int>(move.size());
  std::string path;
  int i = 0;
  int j = 0;
  while (i < n - 1 || j < n - 1) {
    if (move[i][j] == 'U') {
      path.push_back('U');
      ++i;
    }
    else if (move[i][j] == 'L') {
      path.push_back('L');
      ++j;
    }
    else {
      break;
    }
  }
  std::reverse(path.begin(), path.end());
  return path;
}

int main()
{
  setlocale(LC_ALL, "Russian");
  //FIX_ME: Имена не информативны f1 и f2
  //ifstream f1("a.txt", ios::in);
  //ofstream f2("b.txt", ios::out);
  const std::string kInputFile = "a.txt";
  const std::string kOutputFile = "b.txt";

  std::ifstream input(kInputFile);
  //FIX_ME: Добавлена проверка на успешность чтения данных
  //f1 >> n;
  if (!input.is_open()) {
    std::cerr << "Не удалось открыть файл " << kInputFile << std::endl;
    return 1;
  }

  int n = 0;
  if (!(input >> n)) {
    std::cerr << "Не удалось прочитать N" << std::endl;
    return 1;
  }

  //FIX_ME: Добавлена проверка на размер поля (1 < N < 80)
  if (n <= 1 || n >= 80) {
    std::cerr << "Некорректный размер доски: " << n << std::endl;
    return 1;
  }

  std::vector<std::vector<int>> board(n, std::vector<int>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      //FIX_ME: Добавлена проверка каждой ячейки
      // f1 >> pole1[i][j];
      if (!(input >> board[i][j])) {
        std::cerr << "Ошибка чтения доски" << std::endl;
        return 1;
      }
    }
  }
  input.close();

  //FIX_ME: Имена не информативны
  //vector<vector<int>> pole1(n, vector<int>(n));
  //vector<vector<int>> pole2(n, vector<int>(n));
  //vector<vector<char>> put(n, vector<char>(n));
  //string put1;
  std::vector<std::vector<int>> best(n, std::vector<int>(n, 0));
  std::vector<std::vector<char>> move(n, std::vector<char>(n, ' '));

  //FIX_ME: Формат вывода не соответствовал заданию
  //Solve(pole1, pole2, put);
  //f2 << "Максимальная сумма монет, которую может собрать король: " << pole2[0][0] << '\n';
  //p(put, put1);
  //f2 << "Путь: " << put1;
  //f1.close();
  //f2.close();
  //cout << "Программа завершена. Ответ записан в файл b.txt";

  Solve(board, best, move);
  const std::string path = BuildPath(move);

  std::ofstream output(kOutputFile);
  if (!output.is_open()) {
    std::cerr << "Не удалось открыть файл " << kOutputFile << std::endl;
    return 1;
  }
  output << best[0][0] << std::endl;
  output << path << std::endl;
  output.close();

  std::cout << "Программа завершена. Ответ записан в файл "
    << kOutputFile << std::endl;
  return 0;
}