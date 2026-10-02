import java.util.Scanner;

public class Main {

  public static void main(String[] args) {
    System.out.println("=== Демонстрация класса Name ===");

    Name cleopatra = new Name(null, "Клеопатра", null);
    Name pushkin = new Name("Пушкин", "Александр", "Сергеевич");
    Name mayakovsky = new Name("Маяковский", "Владимир", null);

    System.out.println(cleopatra);
    System.out.println(pushkin);
    System.out.println(mayakovsky);

    System.out.println();
    System.out.println("=== Ввод имени с клавиатуры ===");
    Name user_name = read_name_from_console();
    System.out.println("Вы ввели: " + user_name);
  }

  /**
   * Читает фамилию, имя и отчество с клавиатуры.
   * Любое из полей можно оставить пустым — тогда оно
   * не будет учитываться при выводе.
   */
  private static Name read_name_from_console() {
    Scanner scanner = new Scanner(System.in);

    System.out.print("Введите фамилию "
        + "(Enter — пропустить): ");
    String surname = scanner.nextLine();

    System.out.print("Введите личное имя "
        + "(Enter — пропустить): ");
    String first_name = scanner.nextLine();

    System.out.print("Введите отчество "
        + "(Enter — пропустить): ");
    String patronymic = scanner.nextLine();

    return new Name(surname, first_name, patronymic);
  }
}