//К-ичные числа. Среди чисел в системе счисления с основанием K (2≤K≤10) определить сколько 
//имеется чисел из N (1<N<20, K+N<26) разрядов таких, что в их записи не содержится два и 
//более подряд идущих нулей. Для того, чтобы избежать переполнения, ответ
//представьте в виде вещественного числа.

//FIX_ME: Исправлены отступы с табуцляции на 2 пробела

#include <iostream>
//FIX_ME: <vector> не используется
//#include <vector>
//FIX_ME: Добалвен <iomanip> для std::setprecision и std::fixed
#include <iomanip>

//FIX_ME: Убрано использование "using namespace std;"
//using namespace std;

//FIX_ME: Вычисление было перенесено в отдельную функцию
double CountNumbers(int k, int n) {
  long double not_zero = static_cast<long double>(k - 1);
  long double zero = 1.0L;

  for (int length = 2; length <= n - 1; ++length) {
    const long double new_not_zero = (not_zero + zero) * (k - 1);
    const long double new_zero = not_zero;
    not_zero = new_not_zero;
    zero = new_zero;
  }

  const long double tail_total =
    (n == 1) ? 1.0L : (not_zero + zero);

  return static_cast<double>(tail_total * (k - 1));
}

int main() {
  setlocale(LC_ALL, "rus");

  //FIX_ME: имена K/N заменены на k/n
  //int K, N;
  int k, n;

  //FIX_ME: Добавлены проверки успешности чтения K и N
  //cout << "Введите основание K (2 <= K <= 10): ";
  //cin >> K;
  //cout << "Введите количество разрядов N (1 < N < 20): ";
  //cin >> N;
  std::cout << "Введите основание K (2 <= K <= 10): ";
  if (!(std::cin >> k)) {
    std::cerr << "Ошибка чтения K" << std::endl;
    return 1;
  }
  std::cout << "Введите количество разрядов N (1 < N < 20): ";
  if (!(std::cin >> n)) {
    std::cerr << "Ошибка чтения N" << std::endl;
    return 1;
  }

  //FIX_ME: Вывод ошибок изменён с std::cout на std::cerr
  //if (K < 2 || K > 10) {
  //  cout << "Некорректные входные данные." << endl;
  //  return 1;
  //}
  //if (K + N >= 26)
  //{
  //  cout << "Некорректные входные данные." << endl;
  //  return 1;
  //}
  //if (N <= 1 || N >= 20)
  //{
  //  cout << "Некорректные входные данные." << endl;
  //  return 1;
  //}
  if (k < 2 || k > 10) {
    std::cerr << "Некорректное основание K" << std::endl;
    return 1;
  }
  if (n <= 1 || n >= 20) {
    std::cerr << "Некорректное число разрядов N" << std::endl;
    return 1;
  }
  if (k + n >= 26) {
    std::cerr << "Нарушено условие K + N < 26" << std::endl;
    return 1;
  }

  //FIX_ME: Имена nz/oz/tz/_tz/_oz/_nz/s неинформативны. tz/_tz не нужны
  //Счётчики имели тип int - возможно переполнение
  //Считались все последовательности без "00", включая начинающиеся с 0
  //int nz, oz, tz, _tz, _oz, _nz;
  //nz = K - 1;
  //oz = 1;
  //tz = 0;
  //for (int i = 2; i <= N; i++)
  //{
  //  _nz = nz;
  //  _oz = oz;
  //  _tz = tz;
  //  nz = _nz * (K - 1) + _oz * (K - 1);
  //  oz = _nz;
  //  tz = _tz * K + _oz;
  //}
  //double s = nz + oz;
  const double answer = CountNumbers(k, n);

  //FIX_ME: Ответ выводился с фикисрованной точностью
  //cout << "Количество подходящих K-ичных чисел: " << s << endl;
  std::cout << "Количество подходящих K-ичных чисел: "
    << std::fixed << std::setprecision(0) << answer << std::endl;

  //FIX_ME: Остутстововал return 0;
  return 0;
}

