//Во всех заданиях данной подгруппы предполагается, что исходные строки, определяющие выражения, 
//не содержат пробелов.При выполнении заданий не следует использовать оператор цикла.
//Вывести значение логического выражения, заданного в виде строки S.Выражение определяется следующим 
//образом(«T» — True, «F» — False) :
//    <выражение> :: = T | F | And(<параметры>) | Or(<параметры>)
//    <параметры> :: = <выражение> | <выражение>, <параметры>

//FIX_ME: Исправлены отступы с табуцляции на 2 пробела

//FIX_ME: Убраны не используемые заголовки
//#include <iostream>
//#include <fstream>
//#include <vector>
//#include <string>
//#include <cstdlib>
//#include <ctime>
//#include <random>
//#include <sstream>
#include <iostream>
#include <string>
#include <vector>

//FIX_ME: Убрано использование "using namespace std;"
using namespace std;

//FIX_ME: Имена не по стилю, имена параметров неинформативны
//Функция неправильно учитывала скобки
//Отстутствовала проверка строки
//bool evaluate(const string& expr);
//
//vector<string> splitRecursive(const string& s, char delimiter, size_t start = 0) {
//  vector<string> result;
//  size_t pos = s.find(delimiter, start);
//
//  if (pos != string::npos) {
//    result.push_back(s.substr(start, pos - start));
//
//    vector<string> remaining = splitRecursive(s, delimiter, pos + 1);
//
//    result.insert(result.end(), remaining.begin(), remaining.end());
//  }
//  else {
//    if (start < s.length()) {
//      result.push_back(s.substr(start));
//    }
//  }
//
//  return result;
//}
std::size_t FindTopComma(const std::string& s,
  std::size_t pos,
  int depth) {
  if (pos >= s.size()) {
    return std::string::npos;
  }
  if (s[pos] == '(') {
    return FindTopComma(s, pos + 1, depth + 1);
  }
  if (s[pos] == ')') {
    return FindTopComma(s, pos + 1, depth - 1);
  }
  if (s[pos] == ',' && depth == 0) {
    return pos;
  }
  return FindTopComma(s, pos + 1, depth);
}

std::vector<std::string> SplitTopLevelImpl(const std::string& params,
  std::size_t start) {
  std::vector<std::string> result;
  if (start >= params.size()) {
    return result;
  }
  const std::size_t comma = FindTopComma(params, start, 0);
  if (comma == std::string::npos) {
    result.push_back(params.substr(start));
    return result;
  }
  result.push_back(params.substr(start, comma - start));
  const std::vector<std::string> rest =
    SplitTopLevelImpl(params, comma + 1);
  result.insert(result.end(), rest.begin(), rest.end());
  return result;
}

std::vector<std::string> SplitTopLevel(const std::string& params) {
  return SplitTopLevelImpl(params, 0);
}

bool Evaluate(const std::string& expr);

//FIX_ME: имена не по стилю, логика evaluateAnd и одинаковая
//bool evaluateAnd(const vector<string>& expressions, size_t index = 0) {
//  if (index >= expressions.size()) {
//    return true;
//  }
//
//  if (!evaluate(expressions[index])) {
//    return false;
//  }
//
//  return evaluateAnd(expressions, index + 1);
//}
//
//bool evaluateOr(const vector<string>& expressions, size_t index = 0) {
//  if (index >= expressions.size()) {
//    return false;
//  }
//
//  if (evaluate(expressions[index])) {
//    return true;
//  }
//
//  return evaluateOr(expressions, index + 1);
//}
bool EvaluateAnd(const std::vector<std::string>& params,
  std::size_t index) {
  if (index >= params.size()) {
    return true;
  }
  if (!Evaluate(params[index])) {
    return false;
  }
  return EvaluateAnd(params, index + 1);
}

bool EvaluateOr(const std::vector<std::string>& params,
  std::size_t index) {
  if (index >= params.size()) {
    return false;
  }
  if (Evaluate(params[index])) {
    return true;
  }
  return EvaluateOr(params, index + 1);
}

//FIX_ME: Добавлена функция, проверящая начало строки с префикса prefix
bool StartsWith(const std::string& s, const std::string& prefix) {
  return s.size() >= prefix.size() &&
    s.compare(0, prefix.size(), prefix) == 0;
}

//FIX_ME: Исправлена некорреткная проверка на And
//Исправлена проверка закрывающей скобки в конце
//bool evaluate(const string& expr) {
//  if (expr == "T") {
//    return true;
//  }
//  else if (expr == "F") {
//    return false;
//  }
//  else if (expr.substr(0, 3) == "And") {
//    // Убираем "And(" и ")"
//    string params = expr.substr(4, expr.size() - 5);
//    vector<string> sub_exprs = splitRecursive(params, ',');
//    return evaluateAnd(sub_exprs);
//  }
//  else if (expr.substr(0, 2) == "Or") {
//    // Убираем "Or(" и ")"
//    string params = expr.substr(3, expr.size() - 4);
//    vector<string> sub_exprs = splitRecursive(params, ',');
//    return evaluateOr(sub_exprs);
//  }
//  return false;
//}
bool Evaluate(const std::string& expr) {
  if (expr == "T") {
    return true;
  }
  if (expr == "F") {
    return false;
  }
  const bool is_and = StartsWith(expr, "And(");
  const bool is_or = StartsWith(expr, "Or(");
  if (!is_and && !is_or) {
    throw std::invalid_argument("Некорректное выражение: " + expr);
  }
  if (expr.back() != ')') {
    throw std::invalid_argument("Нет закрывающей скобки: " + expr);
  }
  const std::size_t open = expr.find('(');
  const std::string params = expr.substr(open + 1,
    expr.size() - open - 2);
  const std::vector<std::string> sub_exprs = SplitTopLevel(params);
  if (sub_exprs.empty()) {
    throw std::invalid_argument("Пустой список параметров: " + expr);
  }
  return is_and ? EvaluateAnd(sub_exprs, 0)
    : EvaluateOr(sub_exprs, 0);
}


//FIX_ME: Функция не нужна, перенос в main
//void Recur23() {
//  string expr;
//  cin >> expr;
//  bool result = evaluate(expr);
//  cout << (result ? "T" : "F") << endl;
//}

int main() {
  setlocale(LC_ALL, "ru");

  std::string expr;
  //FIX_ME: Добавлена проверка чтения строки
  if (!std::getline(std::cin, expr)) {
    std::cerr << "Ошибка чтения выражения" << std::endl;
    return 1;
  }

  try {
    const bool result = Evaluate(expr);
    std::cout << (result ? 'T' : 'F') << std::endl;
  }
  catch (const std::exception& e) {
    std::cerr << "Ошибка: " << e.what() << std::endl;
    return 1;
  }

  //FIX_ME: Добавлен return 0.
  return 0;
}