import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

/**
 * Отдел с названием, начальником и списком сотрудников.
 * Связь с Employee двусторонняя: сотрудник знает свой отдел,
 * отдел знает всех своих сотрудников.
 */
public class Department {
  private final String title;
  private final List<Employee> employees = new ArrayList<>();
  private Employee head;

  public Department(String title) {
    if (title == null || title.trim().isEmpty()) {
      throw new IllegalArgumentException(
          "Название отдела не может быть пустым");
    }
    this.title = title.trim();
  }

  public String getTitle() {
    return title;
  }

  public Employee getHead() {
    return head;
  }

  /**
   * Возвращаем неизменяемую обёртку, чтобы внешний код
   * не мог обойти логику add_employee/remove_employee
   * и рассинхронизировать обе стороны связи.
   */
  public List<Employee> getEmployees() {
    return Collections.unmodifiableList(employees);
  }

  /**
   * Пакетно-приватные методы изменения списка: их вызывает
   * только Employee, чтобы двусторонняя связь оставалась
   * согласованной. Пользовательский код должен ходить
   * через Employee.setDepartment.
   */
  void add_employee(Employee employee) {
    if (!employees.contains(employee)) {
      employees.add(employee);
    }
  }

  void remove_employee(Employee employee) {
    employees.remove(employee);
  }

  public void setHead(Employee head) {
    this.head = head;
  }

  @Override
  public String toString() {
    return to_string();
  }

  public String to_string() {
    if (head == null) {
      return "Отдел " + title + " (начальник не назначен)";
    }
    return "Отдел " + title + ", начальник "
        + head.getName();
  }
}