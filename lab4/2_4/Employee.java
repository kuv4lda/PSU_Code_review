import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Main {

  public static void main(String[] args) {
    System.out.println("=== Демонстрация сотрудников ===");
    demonstrate_default();

    System.out.println();
    System.out.println("=== Ввод своих данных ===");
    read_and_show_from_console();
  }

  /**
   * Сценарий из задания: три сотрудника в отделе IT,
   * начальник — Козлов.
   */
  private static void demonstrate_default() {
    Department it = new Department("IT");

    Employee petrov = new Employee("Петров");
    Employee kozlov = new Employee("Козлов");
    Employee sidorov = new Employee("Сидоров");

    it.setHead(kozlov);

    petrov.setDepartment(it);
    kozlov.setDepartment(it);
    sidorov.setDepartment(it);

    System.out.println(petrov);
    System.out.println(kozlov);
    System.out.println(sidorov);
  }

  /**
   * Дружественный интерфейс: пользователь вводит название
   * отдела, затем имена сотрудников. Один из них выбирается
   * начальником по номеру. После этого все сотрудники
   * привязываются к отделу и выводятся.
   */
  private static void read_and_show_from_console() {
    Scanner scanner = new Scanner(System.in);

    System.out.print("Введите название отдела: ");
    String title = scanner.nextLine();
    Department department = new Department(title);

    int count = read_positive_int(
        scanner, "Сколько сотрудников создать? ");

    List<Employee> employees = new ArrayList<>();
    for (int i = 0; i < count; i++) {
      System.out.print("Имя сотрудника №" + (i + 1) + ": ");
      String name = scanner.nextLine();
      try {
        employees.add(new Employee(name));
      } catch (IllegalArgumentException e) {
        System.out.println("Ошибка: " + e.getMessage()
            + ". Повторите ввод.");
        i--; // не засчитываем неудачную попытку
      }
    }

    int head_index = read_head_index(scanner, count);
    department.setHead(employees.get(head_index));

    for (Employee employee : employees) {
      employee.setDepartment(department);
    }

    System.out.println();
    System.out.println("=== Результат ===");
    System.out.println(department);
    for (Employee employee : employees) {
      System.out.println(employee);
    }
  }

  // Читает положительное целое с защитой от неверного ввода.
  private static int read_positive_int(
      Scanner scanner, String prompt) {
    while (true) {
      System.out.print(prompt);
      String line = scanner.nextLine().trim();
      try {
        int value = Integer.parseInt(line);
        if (value <= 0) {
          System.out.println(
              "Значение должно быть больше нуля.");
          continue;
        }
        return value;
      } catch (NumberFormatException e) {
        System.out.println(
            "Ошибка: введите целое число.");
      }
    }
  }

  // Спрашивает номер начальника (1..count) с проверкой.
  private static int read_head_index(
      Scanner scanner, int count) {
    while (true) {
      System.out.print(
          "Кто из них начальник? Введите номер (1-"
          + count + "): ");
      String line = scanner.nextLine().trim();
      try {
        int number = Integer.parseInt(line);
        if (number < 1 || number > count) {
          System.out.println(
              "Номер должен быть от 1 до " + count + ".");
          continue;
        }
        return number - 1; // приводим к индексу списка
      } catch (NumberFormatException e) {
        System.out.println(
            "Ошибка: введите целое число.");
      }
    }
  }
}