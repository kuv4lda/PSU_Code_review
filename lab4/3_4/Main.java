public class Main {

  public static void main(String[] args) {
    System.out.println("=== Демонстрация сотрудников ===");

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

    /**
     * Новая возможность: список всех сотрудников отдела,
     * полученный по ссылке на любого из них.
     */
    System.out.println();
    System.out.println("=== Сотрудники отдела по ссылке "
        + "на Петрова ===");
    print_colleagues(petrov);

    System.out.println();
    System.out.println("=== Сотрудники отдела по ссылке "
        + "на Козлова ===");
    print_colleagues(kozlov);
  }

  private static void print_colleagues(Employee employee) {
    System.out.println("Коллеги " + employee.getName() + ":");
    for (Employee colleague : employee.get_colleagues()) {
      System.out.println("  - " + colleague.getName());
    }
  }
}