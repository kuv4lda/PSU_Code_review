/*Дано число D и указатель P1 на вершину непустого стека.
Добавить элемент со значением D в стек и вывести адрес P2 новой вершины стека.

Для каждой динамической структуры должен быть предусмотрен стандартный набор методов -
добавления/удаления/вывода элементов.
Во всех задачах обязательно наличие дружественного интерфейса. Ввод данных с клавиатуры.

В заданиях подгруппы структура «стек» (stack) моделируется цепочкой связанных
узлов-записей типа TNode. Поле Next последнего элемента цепочки равно nullptr. Вершиной
стека (top) считается первый элемент цепочки. Для доступа к стеку используется указатель на
его вершину (для пустого стека данный указатель полагается равным nullptr). Значением
элемента стека считается значение его поля Data*/

//FIX_ME: Исправлены отступы с табуцляции на 2 пробела

#include <iostream>

//FIX_ME: Убрано использование "using namespace std;"
//using namespace std;

//FIX_ME: Изменено Node на TNode, поля data/next не по стилю
//class Node {
//public:
//  int data;
//  Node* next;
//
//
//  Node(int value) : data(value), next(nullptr) {}
//};
class TNode {
public:
  explicit TNode(int value) : data_(value), next_(nullptr) {}

  int data_;
  TNode* next_;
};

//FIX_ME: Добавлен деструктор, getTop() публично возвращал указатель на узел
//class Stack {
//private:
//  Node* top;
//
//public:
//
//  Stack() : top(nullptr) {}
//
//  //  для добавления элемента в стек
//  void push(int value) {
//    Node* newNode = new Node(value); // Создаем новый узел
//    newNode->next = top;             // Новый узел указывает на текущую вершину
//    top = newNode;                   // Обновляем вершину стека
//    cout << "Элемент " << value << " добавлен в стек." << endl;
//  }
//
//  // Метод для удаления элемента из стека
//  void pop() {
//    if (top == nullptr) {
//      cout << "Стек пуст! Невозможно удалить элемент." << endl;
//      return;
//    }
//    Node* temp = top;
//    top = top->next;
//    cout << "Элемент " << temp->data << " удален из стека." << endl;
//    delete temp;
//  }
//
//
//  void print() {
//    if (top == nullptr) {
//      cout << "Стек пуст!" << endl;
//      return;
//    }
//    Node* current = top;
//    cout << "Элементы стека: ";
//    while (current != nullptr) {
//      cout << current->data << " ";
//      current = current->next;
//    }
//    cout << endl;
//  }
//
//
//  Node* getTop() {
//    return top;
//  }
//
//
//  void clearStack() {
//    while (top != nullptr) {
//      Node* temp = top;
//      top = top->next;
//      delete temp;                 // Удаляем узел
//    }
//    cout << "Стек очищен." << endl;
//  }
//
//
//  friend void addElementAndPrintAddress(Stack& stack, int D);
//};
class Stack {
public:
  Stack() : top_(nullptr) {}

  ~Stack() { Clear(); }

  Stack(const Stack&) = delete;
  Stack& operator=(const Stack&) = delete;

  //FIX_ME: Был убран cout. Имя не по стилю
  void Push(int value) {
    TNode* node = new TNode(value);
    node->next_ = top_;
    top_ = node;
  }

  //FIX_ME: Был убран cout. Имя не по стилю
  bool Pop() {
    if (top_ == nullptr) {
      return false;
    }
    TNode* temp = top_;
    top_ = top_->next_;
    delete temp;
    return true;
  }

  //FIX_ME: Имя не по стилю
  void Print() const {
    const TNode* current = top_;
    std::cout << "Элементы стека: ";
    while (current != nullptr) {
      std::cout << current->data_ << ' ';
      current = current->next_;
    }
    std::cout << std::endl;
  }

  bool IsEmpty() const { return top_ == nullptr; }

  //FIX_ME: Имя не по стилю
  void Clear() {
    while (top_ != nullptr) {
      TNode* temp = top_;
      top_ = top_->next_;
      delete temp;
    }
  }

  //FIX_ME: Название не по стилю
  friend void AddElementAndPrintAddress(Stack& stack, int value);

private:
  TNode* top_;
};

//FIX_ME: Функция больше не вызывает публично
//void addElementAndPrintAddress(Stack& stack, int D) {
//  stack.push(D);
//  cout << "Адрес новой вершины стека: " << stack.getTop() << endl;
//}
void AddElementAndPrintAddress(Stack& stack, int value) {
  TNode* node = new TNode(value);
  node->next_ = stack.top_;
  stack.top_ = node;
  std::cout << "Адрес новой вершины стека: "
    << static_cast<const void*>(stack.top_) << '\n';
}

int main() {
  //FIX_ME: Отсутствовал setlocale
  setlocale(LC_ALL, "ru");

  Stack stack;
  int choice, value;

  while (true) {
    std::cout << "Меню:" << std::endl
      << "1. Добавить элемент в стек" << std::endl
      << "2. Удалить элемент из стека" << std::endl
      << "3. Вывести элементы стека" << std::endl
      << "4. Очистить стек" << std::endl
      << "5. Выйти" << std::endl
      << "Введите ваш выбор: ";

    //FIX_ME: Добавлена проверка успешности чтения выбора
    //cin >> choice;
    if (!(std::cin >> choice)) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cerr << "Некорректный ввод. Попробуйте снова." << std::endl;
      continue;
    }

    switch (choice) {
    case 1:
      std::cout << "Введите число для добавления в стек: ";
      //FIX_ME: Добавлена проверка успешности чтения значения
      //cin >> value;
      if (!(std::cin >> value)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
          '\n');
        std::cerr << "Некорректное значение." << std::endl;
        break;
      }
      AddElementAndPrintAddress(stack, value);
      break;
      //FIX_ME: Добавлены проверки
      //case 2:
      //  stack.Pop();
      //  break;
      //case 3:
      //  stack.Print();
      //  break;
      //case 4:
      //  stack.Clear();
      //  break;
      //case 5:
      //  cout << "Выход из программы." << std::endl;
      //  return 0;
      //default:
      //  cout << "Неверный выбор! Пожалуйста, попробуйте снова." << std::endl;
    case 2:
      if (stack.Pop()) {
        std::cout << "Элемент удалён из стека." << std::endl;
      }
      else {
        std::cout << "Стек пуст! Невозможно удалить элемен." << std::endl;
      }
      break;
    case 3:
      if (stack.IsEmpty()) {
        std::cout << "Стек пуст!" << std::endl;
      }
      else {
        stack.Print();
      }
      break;
    case 4:
      stack.Clear();
      std::cout << "Стек очищен." << std::endl;
      break;
    case 5:
      std::cout << "Выход из программы." << std::endl;
      return 0;
    default:
      std::cout << "Неверный выбор! Пожалуйста, попробуйте снова." << std::endl;
    }
  }

  return 0;
}