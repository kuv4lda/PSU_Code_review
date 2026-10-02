public class Main {

  public static void main(String[] args) {
    System.out.println("=== Демонстрация класса Name ===");

    // 1. Только личное имя.
    Name cleopatra = new Name("Клеопатра");

    // 2. Имя + отчество + фамилия.
    Name pushkin = new Name("Александр", "Сергеевич",
        "Пушкин");

    // 3. Имя + фамилия (отчества нет).
    Name mayakovsky = new Name("Владимир", "Маяковский");

    // 4. Христофор — имя, Бонифатьевич — фамилия,
    //    отчество не задано.
    Name hristofor = new Name("Христофор", "Бонифатьевич");

    System.out.println(cleopatra);
    System.out.println(pushkin);
    System.out.println(mayakovsky);
    System.out.println(hristofor);
  }
}