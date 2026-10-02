import java.util.InputMismatchException;
import java.util.Scanner;

public class Main {

  public static void main(String[] args) {
    // Демонстрация работы класса Person с фиксированными данными.
    System.out.println("=== Демонстрация класса Person ===");
    Person cleopatra = new Person("Клеопатра", 152);
    Person pushkin = new Person("Пушкин", 167);
    Person vladimir = new Person("Владимир", 189);

    System.out.println(cleopatra);
    System.out.println(pushkin);
    System.out.println(vladimir);

    // Дружественный интерфейс для ввода с клавиатуры.
    System.out.println();
    System.out.println("=== Ввод человека с клавиатуры ===");
    Person user_person = read_person_from_console();
    System.out.println("Вы ввели: " + user_person);
  }

  
  //Читает данные человека с клавиатуры с проверкой ввода.
   
  private static Person read_person_from_console() {
    try (Scanner scanner = new Scanner(System.in)) {
      while (true) {
        try {
          System.out.print("Введите имя: ");
          String name = scanner.nextLine();

          System.out.print("Введите рост (целое число): ");
          int height = scanner.nextInt();

          return new Person(name, height);
        } catch (InputMismatchException e) {
          System.out.println(
              "Ошибка: рост должен быть целым числом. "
              + "Попробуйте снова.");
          scanner.nextLine(); // очистка буфера
        } catch (IllegalArgumentException e) {
          System.out.println("Ошибка: " + e.getMessage()
              + ". Попробуйте снова.");
        }
      }
    }
  }
}