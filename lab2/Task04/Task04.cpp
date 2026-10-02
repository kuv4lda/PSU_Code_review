/* Дан двусвязный линейный список и указатель первый элемент этого
списка. Все элементы списка хранят различные между собой значения. Необходимо
вывести значения элементов списка, которые находятся между наименьшим и
наибольшим элементами списка, в том порядке, в каком они находятся в исходном
списке. Использовать процедуры.

Все динамические структуры данных реализовывать через классы. Не использовать STL.
Для каждой динамической структуры должен быть предусмотрен
стандартный набор методов - добавления/удаления/вывода элементов.
Во всех задачах обязательно наличие дружественного интерфейса. Ввод данных с клавиатуры.*/

//FIX_ME: Исправлены отступы с табуцляции на 2 пробела

#include <iostream>

//FIX_ME: Убрано использование "using namespace std;"
//using namespace std;

//FIX_ME: Имена должны быть на английском, поля не по стилю, нет конструктора
//// Структура узла двусвязного списка
//struct Uzel {
//  int Znachenie;         // Значение узла
//  Uzel* Predydushiy;      // Указатель на предыдущий узел
//  Uzel* Sleduyushiy;      // Указатель на следующий узел
//};
struct TNode {
  explicit TNode(int value) : data_(value), prev_(nullptr), next_(nullptr) {}

  int data_;
  TNode* prev_;
  TNode* next_;
};

//FIX_ME: Имена должны быть на английском, не было деструктора
//Инициализация списка была отдельным методом, не было метода удаления
//// Класс для работы с двусвязным списком
//class Spisok {
//private:
//  Uzel* PerviyElement;    // Указатель на первый элемент списка
//
//public:
//  // Инициализация списка
//  void Initsializatsiya() {
//    PerviyElement = nullptr;
//  }
//
//  // Очистка списка
//  void Ochistka() {
//    Uzel* Tekushiy = PerviyElement;
//    while (Tekushiy != nullptr) {
//      Uzel* Vremenniy = Tekushiy;
//      Tekushiy = Tekushiy->Sleduyushiy;
//      delete Vremenniy;
//    }
//    PerviyElement = nullptr;
//  }
//
//  // Добавление элемента в конец списка
//  void DobavitElement(int Znachenie) {
//    Uzel* Noviy = new Uzel;
//    Noviy->Znachenie = Znachenie;
//    Noviy->Predydushiy = nullptr;
//    Noviy->Sleduyushiy = nullptr;
//
//    if (PerviyElement == nullptr) {
//      PerviyElement = Noviy;
//    }
//    else {
//      Uzel* Tekushiy = PerviyElement;
//      while (Tekushiy->Sleduyushiy != nullptr) {
//        Tekushiy = Tekushiy->Sleduyushiy;
//      }
//      Tekushiy->Sleduyushiy = Noviy;
//      Noviy->Predydushiy = Tekushiy;
//    }
//  }
//
//  // Вывод всех элементов списка
//  void VivodSpiska() {
//    Uzel* Tekushiy = PerviyElement;
//    while (Tekushiy != nullptr) {
//      cout << Tekushiy->Znachenie << " ";
//      Tekushiy = Tekushiy->Sleduyushiy;
//    }
//    cout << endl;
//  }
//
//  // Поиск минимального и максимального элементов
//  void PoiskMinMax(Uzel*& Min, Uzel*& Max) {
//    if (PerviyElement == nullptr) return;
//
//    Min = Max = PerviyElement;
//    Uzel* Tekushiy = PerviyElement->Sleduyushiy;
//
//    while (Tekushiy != nullptr) {
//      if (Tekushiy->Znachenie < Min->Znachenie) Min = Tekushiy;
//      if (Tekushiy->Znachenie > Max->Znachenie) Max = Tekushiy;
//      Tekushiy = Tekushiy->Sleduyushiy;
//    }
//  }
//
//  // Проверка, какой элемент встречается раньше
//  bool ProverkaPoryadka(Uzel* A, Uzel* B) {
//    Uzel* Tekushiy = PerviyElement;
//    while (Tekushiy != nullptr) {
//      if (Tekushiy == A) return true;
//      if (Tekushiy == B) return false;
//      Tekushiy = Tekushiy->Sleduyushiy;
//    }
//    return false;
//  }
//
//  // Вывод элементов между минимальным и максимальным
//  void VivodMezhduMinMax() {
//    Uzel* Min = nullptr;
//    Uzel* Max = nullptr;
//    PoiskMinMax(Min, Max);
//
//    if (Min == nullptr || Max == nullptr || Min == Max) {
//      cout << "Нет элементов для вывода!" << endl;
//      return;
//    }
//
//    bool MinPerviy = ProverkaPoryadka(Min, Max);
//    Uzel* Start = MinPerviy ? Min : Max;
//    Uzel* End = MinPerviy ? Max : Min;
//
//    cout << "Элементы между " << Min->Znachenie << " и " << Max->Znachenie << ": ";
//    Uzel* Tekushiy = Start->Sleduyushiy;
//    bool EstElementy = false;
//
//    while (Tekushiy != nullptr && Tekushiy != End) {
//      cout << Tekushiy->Znachenie << " ";
//      EstElementy = true;
//      Tekushiy = Tekushiy->Sleduyushiy;
//    }
//
//    if (!EstElementy) cout << "Отсутствуют";
//    cout << endl;
//  }
//};
class DoublyList {
public:
  DoublyList() : head_(nullptr), tail_(nullptr) {}

  ~DoublyList() { Clear(); }

  DoublyList(const DoublyList&) = delete;
  DoublyList& operator=(const DoublyList&) = delete;

  void PushBack(int value) {
    TNode* node = new TNode(value);
    if (tail_ == nullptr) {
      head_ = tail_ = node;
    }
    else {
      tail_->next_ = node;
      node->prev_ = tail_;
      tail_ = node;
    }
  }

  //FIX_ME: Добавлен метод удаления по значению
  bool Remove(int value) {
    TNode* current = head_;
    while (current != nullptr && current->data_ != value) {
      current = current->next_;
    }
    if (current == nullptr) {
      return false;
    }
    if (current->prev_ != nullptr) {
      current->prev_->next_ = current->next_;
    }
    else {
      head_ = current->next_;
    }
    if (current->next_ != nullptr) {
      current->next_->prev_ = current->prev_;
    }
    else {
      tail_ = current->prev_;
    }
    delete current;
    return true;
  }

  //FIX_ME: Имя должно быть на английском
  void Print() const {
    const TNode* current = head_;
    bool first = true;
    while (current != nullptr) {
      if (!first) {
        std::cout << ' ';
      }
      std::cout << current->data_;
      first = false;
      current = current->next_;
    }
  }

  bool IsEmpty() const { return head_ == nullptr; }

  //FIX_ME: Имя должно быть на английском
  void Clear() {
    TNode* current = head_;
    while (current != nullptr) {
      TNode* temp = current;
      current = current->next_;
      delete temp;
    }
    head_ = tail_ = nullptr;
  }

  //FIX_ME: Имена должны быть на английском
  //Упрощено на возврат структуры MinMax
  struct MinMax {
    TNode* min_node;
    TNode* max_node;
  };

  //Возвращает указатели на минимальный и максимальный узлы
  MinMax FindMinMax() const {
    MinMax result{ nullptr, nullptr };
    if (head_ == nullptr) {
      return result;
    }
    result.min_node = result.max_node = head_;
    const TNode* current = head_->next_;
    while (current != nullptr) {
      if (current->data_ < result.min_node->data_) {
        result.min_node = const_cast<TNode*>(current);
      }
      if (current->data_ > result.max_node->data_) {
        result.max_node = const_cast<TNode*>(current);
      }
      current = current->next_;
    }
    return result;
  }

  // Проверяет, идёт ли узел a раньше узла b в списке
  bool IsBefore(const TNode* a, const TNode* b) const {
    const TNode* current = head_;
    while (current != nullptr) {
      if (current == a) {
        return true;
      }
      if (current == b) {
        return false;
      }
      current = current->next_;
    }
    return false;
  }

  //FIX_ME: Работает с приватным head_ напрямую
  friend void PrintBetweenMinMaxProc(const DoublyList& list);

private:
  TNode* head_;
  TNode* tail_;
};

//FIX_ME: Добавлена процедура вывода элементов между min и max
void PrintBetweenMinMaxProc(const DoublyList& list) {
  const DoublyList::MinMax mm = list.FindMinMax();
  if (mm.min_node == nullptr || mm.max_node == nullptr ||
    mm.min_node == mm.max_node) {
    std::cout << "Нет элементов для вывода!\n";
    return;
  }

  const bool min_first = list.IsBefore(mm.min_node, mm.max_node);
  const TNode* start = min_first ? mm.min_node : mm.max_node;
  const TNode* end = min_first ? mm.max_node : mm.min_node;

  std::cout << "Элементы между " << mm.min_node->data_
    << " и " << mm.max_node->data_ << ": ";

  const TNode* current = start->next_;
  bool has_elements = false;
  while (current != nullptr && current != end) {
    if (has_elements) {
      std::cout << ' ';
    }
    std::cout << current->data_;
    has_elements = true;
    current = current->next_;
  }
  if (!has_elements) {
    std::cout << "Отсутствуют";
  }
  std::cout << std::endl;
}

int main() {
  setlocale(LC_ALL, "Russian");

  DoublyList list;

  //FIX_ME: Выполнялось вручную, теперь есть конструктор и деструктор
  //Spisok.Initsializatsiya();

  std::cout << "Введите количество элементов: ";
  int n = 0;
  //FIX_ME: Добавлена проверка на корректность
  //cin >> N;
  if (!(std::cin >> n)) {
    std::cerr << "Некорректное число!" << std::endl;
    return 1;
  }
  if (n <= 0) {
    std::cerr << "Некорректное число!" << std::endl;
    return 1;
  }


  std::cout << "Вводите элементы:" << std::endl;
  for (int i = 0; i < n; i++) {
    int value = 0;
    if (!(std::cin >> value)) {
      //FIX_ME: cout заменён на std::cerr, return должен возвращать 1
      std::cerr << "Ошибка ввода!" << std::endl;
      return 1;
    }
    list.PushBack(value);
  }

  std::cout << "Список: ";
  //FIX_ME: Добавлена проверка на пустой список
  //Spisok.VivodSpiska();
  if (list.IsEmpty()) {
    std::cout << "Список пуст" << std::endl;
  }
  else {
    list.Print();
    std::cout << std::endl;
  }

  PrintBetweenMinMaxProc(list);

  //FIX_ME: Ручная очистка не нужна
  //Spisok.Ochistka();

  return 0;
}