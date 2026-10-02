/**
 * Сотрудник, работающий в некотором отделе.
 * При смене отдела отдел сам обновляет свой список
 * сотрудников — это гарантирует согласованность.
 */
public class Employee {
  private final String name;
  private Department department;

  public Employee(String name) {
    if (name == null || name.trim().isEmpty()) {
      throw new IllegalArgumentException(
          "Имя сотрудника не может быть пустым");
    }
    this.name = name.trim();
  }

  public String getName() {
    return name;
  }

  public Department getDepartment() {
    return department;
  }

  /**
   * Смена отдела: сначала отписываемся от старого,
   * потом подписываемся на новый — иначе сотрудник
   * остался бы в списке двух отделов одновременно.
   */
  public void setDepartment(Department department) {
    if (this.department == department) {
      return;
    }
    if (this.department != null) {
      this.department.remove_employee(this);
    }
    this.department = department;
    if (department != null) {
      department.add_employee(this);
    }
  }

  /**
   * Список всех сотрудников того же отдела, что и этот.
   * Если отдел не задан — возвращаем пустой список,
   * чтобы вызывающий код не проверял null.
   */
  public java.util.List<Employee> get_colleagues() {
    if (department == null) {
      return java.util.Collections.emptyList();
    }
    return department.getEmployees();
  }

  @Override
  public String toString() {
    return to_string();
  }

  public String to_string() {
    if (department == null) {
      return name + " (отдел не назначен)";
    }
    if (department.getHead() == this) {
      return name + " начальник отдела "
          + department.getTitle();
    }
    return name + " работает в отделе "
        + department.getTitle()
        + ", начальник которого "
        + department.getHead().getName();
  }
}