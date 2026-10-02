/* Даны указатели P1 и P2 на начало и конец непустой очереди. Извлекать из очереди
элементы, пока значение начального элемента очереди не станет четным, и выводить значения
извлеченных элементов(если очередь не содержит элементов с четными значениями, то извлечь
все ее элементы).Вывести также новые адреса начала и конца очереди(для пустой очереди
дважды вывести nullptr).После извлечения элементов из очереди освобождать память, которую
они занимали.


Для каждой динамической структуры должен быть предусмотрен стандартный набор методов -
добавления/удаления/вывода элементов.
Во всех задачах обязательно наличие дружественного интерфейса. Ввод данных с клавиатуры.



В заданиях данной подгруппы структура «очередь» (queue) моделируется цепочкой связанных
узлов-записей типа TNode. Поле Next последнего элемента цепочки равно nullptr. Началом
очереди («головой», head) считается первый элемент цепочки, концом («хвостом», tail) — ее
последний элемент. Для возможности быстрого добавления в конец очереди нового элемента
удобно хранить, помимо указателя на начало очереди, также и указатель на ее конец. В случае
пустой очереди указатели на ее начало и конец полагаются равными nullptr. Как и для стека,
значением элемента очереди считается значение его поля Data.*/

//FIX_ME: Исправлены отступы с табуцляции на 2 пробела

#include <iostream>
#include <string>
#include <cctype>
//FIX_ME:Добавлен <vector> для std::vector
#include <vector>

//FIX_ME: Убрано использование "using namespace std;"
//using namespace std;

//FIX_ME: Изменено Node на TNode. Был вынесен наружу
struct TNode {
  TNode(int value, TNode* next) : data_(value), next_(next) {}

  int data_;
  TNode* next_;
};

//FIX_ME: isdigit(str[i]) изменён на std::isdigit(static_cast<unsigned char>
//Не обрабатывал +/- без цифр. Имя не по стилю
//bool IsNumber(const  string& str) {
//  if (str.empty()) return false;
//  int start = (str[0] == '-' || str[0] == '+') ? 1 : 0;
//  for (int i = start; i < str.length(); ++i) {
//    if (!isdigit(str[i])) return false;
//  }
//  return start < str.length();
//}
bool IsInteger(const std::string& str) {
  if (str.empty()) {
    return false;
  }
  std::size_t start = 0;
  if (str[0] == '-' || str[0] == '+') {
    start = 1;
  }
  if (start >= str.size()) {
    return false;
  }
  for (std::size_t i = start; i < str.size(); ++i) {
    if (!std::isdigit(static_cast<unsigned char>(str[i]))) {
      return false;
    }
  }
  return true;
}

//FIX_ME: getP1/getP2 возвращал указатель на приватный тип
//Имена методов не по стилю.
//class Queue {
//private:
//  struct Node {
//    int data;
//    Node* next;
//  };
//
//  Node* P1;
//  Node* P2;
//
//public:
//  Queue() : P1(nullptr), P2(nullptr) {}
//
//  void push(int num) { // Добавление элемента в очередь
//    Node* newNode = new Node;
//    newNode->data = num;
//    newNode->next = nullptr;
//    if (!P2) {
//      P1 = P2 = newNode;
//    }
//    else {
//      P2->next = newNode;
//      P2 = newNode;
//    }
//    newNode->next = nullptr;
//  }
//  void show() { // Вывод элементов
//    Node* temp = P1;
//    if (!temp) {
//      cout << "Очередь пустая" << endl;
//      return;
//    }
//    while (temp) {
//      cout << temp->data << " ";
//      temp = temp->next;
//    }
//    cout << endl;
//  }
//
//  bool pop(int& num) {  // Извлечение элемента из очереди
//    if (!P1) return false; // Очередь пуста
//
//    Node* temp = P1;
//    num = P1->data;
//    P1 = P1->next;
//    if (!P1) P2 = nullptr; // Если очередь стала пустой
//
//    delete temp;
//    return true;
//  }
//
//  Node* getP1() const {
//    return P1;
//  }
//  void getP1data() const {
//    int num1 = P1->data;
//    cout << num1;
//  }
//
//  void getP2data() const {
//    int num1 = P2->data;
//    cout << num1;
//  }
//
//  Node* getP2() const {
//    return P2;
//  }
//
//  void EvenHead() { // Извлечение элементов, пока не встретится четное значение
//    int num;
//    while (!(P1 == nullptr) && (P1->data % 2 != 0)) {
//      pop(num);
//      cout << num << " ";
//    }
//    cout << endl;
//  }
//
//  ~Queue() {
//    int del;
//    while (pop(del));
//  }
//};
class Queue {
public:
  Queue() : head_(nullptr), tail_(nullptr) {}

  ~Queue() { Clear(); }

  Queue(const Queue&) = delete;
  Queue& operator=(const Queue&) = delete;

  //FIX_ME: Был убран cout. Имя не по стилю
  //newNode->next = nullptr дублировался
  void Push(int value) {
    TNode* node = new TNode(value, nullptr);
    if (tail_ == nullptr) {
      head_ = tail_ = node;
    }
    else {
      tail_->next_ = node;
      tail_ = node;
    }
  }

  //FIX_ME: Был убран cout. Имя не по стилю
  bool Pop(int& value) {
    if (head_ == nullptr) {
      return false;
    }
    TNode* temp = head_;
    value = head_->data_;
    head_ = head_->next_;
    if (head_ == nullptr) {
      tail_ = nullptr;
    }
    delete temp;
    return true;
  }

  //FIX_ME: Был убран cout. Имя не по стилю
  void Print() const {
    const TNode* current = head_;
    while (current != nullptr) {
      std::cout << current->data_ << ' ';
      current = current->next_;
    }
  }

  bool IsEmpty() const { return head_ == nullptr; }

  //FIX_ME: Имя не по стилю. Добавлена проверка на пустую очередь
  bool ValueHead(int& value) const {
    if (head_ == nullptr) {
      return false;
    }
    value = head_->data_;
    return true;
  }

  //FIX_ME: Имя не по стилю. Добавлена проверка на пустую очередь
  bool ValueTail(int& value) const {
    if (tail_ == nullptr) {
      return false;
    }
    value = tail_->data_;
    return true;
  }

  //FIX_ME: Был убран cout. Имя не по стилю
  std::vector<int> ExtractUntilEven() {
    std::vector<int> extracted;
    int value = 0;
    while (head_ != nullptr && head_->data_ % 2 != 0) {
      Pop(value);
      extracted.push_back(value);
    }
    return extracted;
  }

  //FIX_ME: Добавлена функция очистки очереди
  void Clear() {
    int value = 0;
    while (Pop(value)) {
    }
  }

  //FIX_ME: Добавлены функции для работы с приватными head_/tail_
  friend void PrintHeadAddress(const Queue& queue);
  friend void PrintTailAddress(const Queue& queue);

private:
  TNode* head_;
  TNode* tail_;
};

//FIX_ME: Добавлены функции, которые печатают адрес головы/хвоста или "nullptr"
void PrintHeadAddress(const Queue& queue) {
  if (queue.head_ == nullptr) {
    std::cout << "nullptr";
  }
  else {
    std::cout << static_cast<const void*>(queue.head_);
  }
}

void PrintTailAddress(const Queue& queue) {
  if (queue.tail_ == nullptr) {
    std::cout << "nullptr";
  }
  else {
    std::cout << static_cast<const void*>(queue.tail_);
  }
}

int main() {
  setlocale(LC_ALL, "ru");

  //FIX_ME: Имена не информативны. Лишние переменные удалены
  Queue queue;
  //string in;
  //string inum;
  std::string input;
  //int num;
  int n;

  std::cout << "Введите количество элементов в очереди: ";
  //FIX_ME: Добавлена проверка на число
  //std::cin >> input;
  //if (!IsNumber(in)) {
  if (!(std::cin >> input) || !IsInteger(input)) {
    //FIX_ME: cout изменён на std::serr
    //cout << "Недопустимое значение.";
    std::cerr << "Недопустимое значение." << std::endl;
    return 1;
  }
  //FIX_ME: Добавлена проверка на корректность
  //else {
  //  n = stoi(in);
  //}
  try {
    n = std::stoi(input);
  }
  catch (const std::exception&) {
    std::cerr << "Число вне диапазона int." << std::endl;
    return 1;
  }

  //FIX_ME: Добавлена проверка на размер очереди (n > 0)
  if (n <= 0) {
    std::cerr << "Число элементов должно быть положительным." << std::endl;
    return 1;
  }

  std::cout << "Введите элементы очереди: ";
  for (int i = 1; i <= n; i++) {
    std::string token;
    //FIX_ME: Добавлена проверка на число
    //if (!IsInteger(input)) {
    if (!(std::cin >> token) || !IsInteger(token)) {
      //FIX_ME: cout изменён на std::cerr
      //cout << "Недопустимое значение.";
      std::cerr << "Недопустимое значение." << std::endl;
      return 1;
    }
    //FIX_ME: Добавлена проверка на корректность
    //else {
    //  n = std::stoi(input);
    //  queue.Push(n);
    //}
    int value = 0;
    try {
      value = std::stoi(token);
    }
    catch (const std::exception&) {
      std::cerr << "Число вне диапазона int." << std::endl;
      return 1;
    }
    queue.Push(value);
  }

  std::cout << "Изначальная очередь: ";
  //FIX_ME: Добавлена проверка на пустую очередь
  //q.show();
  if (queue.IsEmpty()) {
    std::cout << "Очередь пустая" << std::endl;
  }
  else {
    queue.Print();
    std::cout << std::endl;
  }

  std::cout << "Извлеченные элементы: ";
  //FIX_ME: Инициализирована отдельная переменная для хранения элементов
  //q.EvenHead();
  const std::vector<int> extracted = queue.ExtractUntilEven();
  for (std::size_t i = 0; i < extracted.size(); ++i) {
    if (i > 0) {
      std::cout << ' ';
    }
    std::cout << extracted[i];
  }
  std::cout << std::endl;

  std::cout << "Измененная очередь: ";
  //FIX_ME: Добавлена проверка на пустую очередь
  //q.show();
  if (queue.IsEmpty()) {
    std::cout << "Очередь пустая" << std::endl;
  }
  else {
    queue.Print();
    std::cout << std::endl;
  }

  std::cout << "Значение первого элемента: ";
  //FIX_ME: Для пустой очереди getP1data работал некорректно
  //q.getP1data();
  //cout << endl;
  int head_value = 0;
  if (queue.ValueHead(head_value)) {
    std::cout << head_value << std::endl;
  }
  else {
    std::cout << "Элемент отстутствует. Очередь пустая" << std::endl;
  }

  //cout << "Новый адрес начала очереди (P1): " << q.getP1() << endl;
  std::cout << "Новый адрес начала очереди (P1): ";
  PrintHeadAddress(queue);
  std::cout << std::endl;

  std::cout << "Значение последнего элемента: ";
  //FIX_ME: Для пустой очереди getP2data работал некорректно
  //q.getP2data();
  //cout << endl;
  int tail_value = 0;
  if (queue.ValueTail(tail_value)) {
    std::cout << tail_value << std::endl;
  }
  else {
    std::cout << "Элемент отстутствует. Очередь пустая" << std::endl;
  }

  //cout << "Новый адрес конца очереди (P2): " << q.getP2() << endl;
  std::cout << "Новый адрес конца очереди (P2): ";
  PrintTailAddress(queue);
  std::cout << std::endl;

  return 0;
}