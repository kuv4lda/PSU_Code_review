/*
Все динамические структуры данных реализовывать через классы. Не использовать STL.  Для каждой динамической структуры должен быть предусмотрен
стандартный набор методов - добавления/удаления/вывода элементов. Во всех задачах обязательно
наличие дружественного интерфейса. Ввод данных с клавиатуры.


Дан текстовый файл, в первой строке которого хранится число N, а во второй
строке N целых чисел. Необходимо создать упорядоченный по убыванию список, в который
поместить все эти элементы, при этом очередной элемент вставлять в список так, чтобы не
нарушалась его упорядоченность.*/

//FIX_ME: Исправлены отступы с табуцляции на 2 пробела

#include <iostream>
#include <fstream>
//FIX_ME: Добавлен <string> для std::string
#include <string>

//FIX_ME: Убрано использование "using namespace std;"
//using namespace std;

//FIX_ME: Изменено Node на TNode, поля data/next не по стилю
//Node был отдельным классом, переделан в структуру
//class Node {
//public:
//  int data;
//  Node* next;
//
//
//  Node(int value) : data(value), next(nullptr) {}
//};
struct TNode {
  explicit TNode(int value, TNode* next) : data_(value), next_(next) {}

  int data_;
  TNode* next_;
};

//FIX_ME: Переименован в SortedList, добавлен деструктор
//Остутстовал метод удаления
//class LinkedList {
//private:
//  Node* head;
//
//public:
//
//  LinkedList() : head(nullptr) {}
//
//
//  void insertSorted(int value) {
//    Node* newNode = new Node(value);
//    if (head == nullptr || head->data < value) {
//      newNode->next = head;
//      head = newNode;
//    }
//    else {
//      Node* current = head;
//      while (current->next != nullptr && current->next->data > value) {
//        current = current->next;
//      }
//      newNode->next = current->next;
//      current->next = newNode;
//    }
//  }
//
//
//  void print() {
//    Node* current = head;
//    while (current != nullptr) {
//      cout << current->data << " ";
//      current = current->next;
//    }
//    cout << endl;
//  }
//
//
//  void readFromFile(const std::string& filename) {
//    ifstream file(filename);   // Открываем файл для чтения
//    if (!file.is_open()) {          // Проверяем, удалось ли открыть файл
//      cerr << "Ошибка открытия файла!" << endl;
//      return;
//    }
//
//    int N;
//    file >> N;                      // Читаем количество элементов
//
//    int value;
//    for (int i = 0; i < N; ++i) {   // Читаем элементы и добавляем их в список
//      file >> value;
//      insertSorted(value);         // Вставляем элемент с сохранением упорядоченности
//    }
//
//    file.close();                   // Закрываем файл
//  }
//
//
//  friend void readFromFile(LinkedList& list, const string& filename);
//};
class SortedList {
public:
  SortedList() : head_(nullptr) {}

  ~SortedList() { Clear(); }

  SortedList(const SortedList&) = delete;
  SortedList& operator=(const SortedList&) = delete;

  //FIX_ME: Имя не по стилю
  void InsertSorted(int value) {
    TNode* node = new TNode(value, nullptr);
    if (head_ == nullptr || head_->data_ < value) {
      node->next_ = head_;
      head_ = node;
      return;
    }
    TNode* current = head_;
    while (current->next_ != nullptr && current->next_->data_ > value) {
      current = current->next_;
    }
    node->next_ = current->next_;
    current->next_ = node;
  }

  //FIX_ME: Добавлен метод удаления головы
  bool PopFront() {
    if (head_ == nullptr) {
      return false;
    }
    TNode* temp = head_;
    head_ = head_->next_;
    delete temp;
    return true;
  }

  //FIX_ME: Добавлен метод удаления по значению
  bool Remove(int value) {
    if (head_ == nullptr) {
      return false;
    }
    if (head_->data_ == value) {
      TNode* temp = head_;
      head_ = head_->next_;
      delete temp;
      return true;
    }
    TNode* current = head_;
    while (current->next_ != nullptr && current->next_->data_ != value) {
      current = current->next_;
    }
    if (current->next_ == nullptr) {
      return false;
    }
    TNode* temp = current->next_;
    current->next_ = temp->next_;
    delete temp;
    return true;
  }

  //FIX_ME: Не было обработки пустого списка. Был убран cout. Имя не по стилю
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

  //FIX_ME: Добавлен метод очистки
  void Clear() {
    while (head_ != nullptr) {
      TNode* temp = head_;
      head_ = head_->next_;
      delete temp;
    }
  }

  //FIX_ME: Название не по стилю
  friend bool ReadFromFile(SortedList& list, const std::string& filename);

private:
  TNode* head_;
};

//FIX_ME: Добавлена проверка успешности чтения, проверяет N на положительность
//void readFromFile(LinkedList& list, const string& filename) {
//  list.readFromFile(filename);
//}
bool ReadFromFile(SortedList& list, const std::string& filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Ошибка открытия файла" << std::endl;
    return false;
  }

  int n = 0;
  if (!(file >> n)) {
    std::cerr << "Не удалось прочитать N" << std::endl;
    return false;
  }
  if (n <= 0) {
    std::cerr << "N должно быть положительным" << std::endl;
    return false;
  }

  list.Clear();
  for (int i = 0; i < n; ++i) {
    int value = 0;
    if (!(file >> value)) {
      std::cerr << "Не удалось прочитать элемент #" << (i + 1) << std::endl;
      return false;
    }
    list.InsertSorted(value);
  }
  return true;
}

int main() {
  //FIX_ME: Добавлен setlocale
  setlocale(LC_ALL, "ru");

  SortedList list;

  std::string filename;
  std::cout << "Введите имя файла: ";
  //FIX_ME: Добалена проверка чтения имени файла
  //cin >> filename;
  if (!(std::cin >> filename)) {
    std::cerr << "Ошибка чтения имени файла" << std::endl;
    return 1;
  }

  //FIX_ME: Добавлена проверка чтения файла
  //readFromFile(list, filename);
  if (!ReadFromFile(list, filename)) {
    return 1;
  }


  std::cout << "Упорядоченный список: ";
  //FIX_ME: Проверка на пустой список
  //list.print();
  std::cout << "Упорядоченный список: ";
  if (list.IsEmpty()) {
    std::cout << "Список пуст" << std::endl;
  }
  else {
    list.Print();
    std::cout << std::endl;
  }

  return 0;
}