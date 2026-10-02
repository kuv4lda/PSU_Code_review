/* Элементами контейнеров являются целые числа. Для
заполнения контейнера использовать итератор и конструктор соответствующего контейнера,
для вывода элементов использовать итератор (для вывода элементов в обратном порядке
использовать обратные итераторы, возвращаемые функциями-членами rbegin и rend)
Обязательно наличие дружественного интерфейса. Ввод данных организовать
разными способами (с клавиатуры, рандом, из файла)


 Дан дек D с нечетным количеством элементов N (≥ 5). Добавить в начало дека пять
его средних элементов в исходном порядке. Использовать один вызов функции-члена insert. */

//FIX_ME: Исправлены отступы с табуцляции на 2 пробела

#include <iostream>
#include <deque>
#include <fstream>
//FIX_ME: Вместо <cstdlib>, <ctime>, и <iterator> используется <random>
//Добален <string>
//#include <cstdlib>
//#include <ctime>
//#include <iterator>
#include <random>
#include <string>
#include <limits>

//FIX_ME: Убрано использование "using namespace std;"
//using namespace std;

//FIX_ME: Добавлен класс
class IntDeque {
public:
  IntDeque() = default;

  // Добавлен конструктор из диапазона итераторов
  template <typename InputIt>
  IntDeque(InputIt first, InputIt last) : data_(first, last) {}

  // Добавлен метод добавления в конец
  void PushBack(int value) { data_.push_back(value); }

  std::size_t Size() const { return data_.size(); }

  // ВДобавлен вывод через прямой итератор
  void Print() const {
    for (auto it = data_.begin(); it != data_.end(); ++it) {
      std::cout << *it << ' ';
    }
  }

  // Добавлен вывод через обратный итератор
  void PrintReverse() const {
    for (auto it = data_.rbegin(); it != data_.rend(); ++it) {
      std::cout << *it << ' ';
    }
  }

  //FIX_ME: Работает с приватным data_ напрямую
  friend void InsertMiddleFive(IntDeque& deque);

private:
  std::deque<int> data_;
};

//FIX_ME: Имена не по стилю. Не было проверки N >= 5 и N - нечётное
//void FuncInsert(deque<int>& D)
//{
//  size_t N = D.size();
//
//  // Вычисляем индекс среднего элемента
//  size_t MiddleIndex = N / 2;
//
//  // Получаем пять средних элементов
//  deque<int> MiddleElements;
//  for (size_t i = MiddleIndex - 2; i <= MiddleIndex + 2; ++i)
//  {
//    MiddleElements.push_back(D[i]);
//  }
//
//  // Вставляем пять средних элементов в начало дека
//  D.insert(D.begin(), MiddleElements.begin(), MiddleElements.end());
//}
void InsertMiddleFive(IntDeque& deque) {
  const std::size_t n = deque.data_.size();
  if (n < 5 || n % 2 == 0) {
    throw std::invalid_argument(
      "Дек должен содержать нечётное количество элементов >= 5");
  }

  const std::size_t middle_index = n / 2;

  auto first = deque.data_.begin() +
    static_cast<std::ptrdiff_t>(middle_index - 2);
  auto last = deque.data_.begin() +
    static_cast<std::ptrdiff_t>(middle_index + 3);

  deque.data_.insert(deque.data_.begin(), first, last);
}

//FIX_ME: Изменено название. Ввод не проверялся
//deque<int> FuncKeyboard()
//{
//  int count;
//  cout << "Введите количество целых чисел (нечетное и >= 5): ";
//  cin >> count;
//
//  while (count < 5 || count % 2 == 0)
//  {
//    cout << "Количество должно быть нечетным и >= 5. Повторите ввод: ";
//    cin >> count;
//  }
//
//  deque<int> D;
//  cout << "Введите " << count << " целых чисел:" << endl;
//  for (int i = 0; i < count; ++i)
//  {
//    int number;
//    cin >> number;
//    D.push_back(number);
//  }
//
//  return D;
//}
IntDeque ReadFromKeyboard() {
  int count = 0;
  std::cout << "Введите количество целых чисел (нечётное и >= 5): ";
  if (!(std::cin >> count)) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    throw std::invalid_argument("Некорректное число");
  }
  while (count < 5 || count % 2 == 0) {
    std::cerr << "Количество должно быть нечётным и >= 5. Повторите ввод: ";
    if (!(std::cin >> count)) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      throw std::invalid_argument("Некорректное число");
    }
  }

  std::vector<int> buffer;
  buffer.reserve(static_cast<std::size_t>(count));

  std::cout << "Введите " << count << " целых чисел:" << std::endl;
  for (int i = 0; i < count; ++i) {
    int value = 0;
    if (!(std::cin >> value)) {
      throw std::invalid_argument("Некорректное число");
    }
    buffer.push_back(value);
  }
  // Конструктор из диапазона — требование задания.
  return IntDeque(buffer.begin(), buffer.end());
}

//FIX_ME: Изменено название. srand/rand заменены
//Возврат через конструктор из диапазона
//deque<int> FuncRandom(int count)
//{
//  deque<int> D;
//  srand(static_cast<unsigned>(time(0)));
//
//  for (int i = 0; i < count; ++i)
//  {
//    D.push_back(rand() % 100);
//  }
//
//  return D;
//}
IntDeque ReadRandom(int count) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(0, 99);

  std::vector<int> buffer;
  buffer.reserve(static_cast<std::size_t>(count));
  for (int i = 0; i < count; ++i) {
    buffer.push_back(dist(gen));
  }
  return IntDeque(buffer.begin(), buffer.end());
}

//FIX_ME: Изменено название. Добавлен запрос названия файла для чтения
//Возврат через конструктор из диапазона
//deque<int> FuncFile()
//{
//  deque<int> D;
//  ifstream infile("a.txt");
//  int number;
//
//  if (!infile.is_open())
//  {
//    throw runtime_error("Не удалось открыть файл.");
//  }
//
//  while (infile >> number)
//  {
//    D.push_back(number);
//  }
//
//  if (D.size() < 5 || D.size() % 2 == 0)
//  {
//    throw invalid_argument("Количество чисел в файле должно быть нечетным и >= 5.");
//  }
//
//  return D;
//}
IntDeque ReadFromFile(const std::string& filename) {
  std::ifstream infile(filename);
  if (!infile.is_open()) {
    throw std::runtime_error("Не удалось открыть файл " + filename);
  }

  std::vector<int> buffer;
  int value = 0;
  while (infile >> value) {
    buffer.push_back(value);
  }

  if (buffer.size() < 5 || buffer.size() % 2 == 0) {
    throw std::invalid_argument(
      "Количество чисел в файле должно быть нечётным и >= 5");
  }

  return IntDeque(buffer.begin(), buffer.end());
}

int main()
{
  setlocale(LC_ALL, "ru");

  //FIX_ME: Приведено к корректному стилю
  //cout << "Выберите метод ввода данных: 1.Ввод с клавиатуры  2.Случайные числа  3.Чтение из файла" << endl;
  std::cout << "Выберите метод ввода данных:" << std::endl
    << "1. Ввод с клавиатуры" << std::endl
    << "2. Случайные числа" << std::endl
    << "3. Чтение из файла" << std::endl;


  int choice;
  //FIX_ME: Добавлена проверка на ввод:
  //cin >> choice;
  if (!(std::cin >> choice)) {
    std::cerr << "Некорректный выбор.\n";
    return 1;
  }

  try {
    IntDeque data;
    switch (choice) {
    case 1: {
      data = ReadFromKeyboard();
      break;
    }
    case 2: {
      int count;
      std::cout << "Введите количество чисел (нечетное и >= 5): ";
      //FIX_ME: Добавлена проверка на корректность
      //cin >> count;
      if (!(std::cin >> count)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
          '\n');
        throw std::invalid_argument("Некорректное число");
      }
      while (count < 5 || count % 2 == 0) {
        //FIX_ME: cout изменён на std::cerr
        //cout << "Количество должно быть нечетным и >= 5. Повторите ввод: ";
        std::cerr << "Количество должно быть нечётным и >= 5. Повторите ввод: ";
        //FIX_ME: Добавлена проверка на корректность
        //cin >> count;
        if (!(std::cin >> count)) {
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          throw std::invalid_argument("Некорректное число");
        }
      }
      data = ReadRandom(count);
      break;
    }
    case 3: {
      //FIX_ME: Название файла вводится с клавиатуры
      //D = FuncFile();
      std::string filename;
      std::cout << "Введите имя файла: ";
      std::cin >> filename;
      data = ReadFromFile(filename);
      break;
    }
    default: {
      std::cerr << "Некорректный выбор." << std::endl;
      return 1;
    }
    }

    std::cout << "Исходный дек: ";
    //FIX_ME: Вывод через прямой итератор
    //for (const auto& elem : D)
    //{
    //  cout << elem << " ";
    //}
    data.Print();
    std::cout << std::endl;

    //FIX_ME: Вывод через обрытный итератор
    std::cout << "Исходный дек (обратный порядок): ";
    data.PrintReverse();
    std::cout << std::endl;

    InsertMiddleFive(data);

    std::cout << "Дек после вставки: ";
    //FIX_ME: Вывод через прямой итератор
    //for (const auto& elem : D)
    //{
    //  cout << elem << " ";
    //}
    data.Print();
    std::cout << std::endl;

    //FIX_ME: Вывод через обрытный итератор
    std::cout << "Дек после вставки (обратный порядок): ";
    data.PrintReverse();
    std::cout << std::endl;

  }
  catch (const std::exception& e) {
    std::cerr << "Ошибка: " << e.what() << std::endl;
    //FIX_ME: отсутствовал return 1
    return 1;
  }
  return 0;
}
