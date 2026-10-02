public class Main {

  public static void main(String[] args) {
    System.out.println("=== Пистолет с тремя патронами ===");
    Pistol pistol = new Pistol(3);
    System.out.println("До стрельбы: " + pistol);

    // По заданию — пять выстрелов из трёх патронов.
    for (int i = 1; i <= 5; i++) {
      System.out.print("Выстрел " + i + ": ");
      pistol.shoot();
    }

    System.out.println("После стрельбы: " + pistol);

    // Демонстрация конструктора по умолчанию.
    System.out.println();
    System.out.println("=== Пистолет по умолчанию ===");
    Pistol default_pistol = new Pistol();
    System.out.println("До стрельбы: " + default_pistol);
    default_pistol.shoot();
    System.out.println("После выстрела: " + default_pistol);
  }
}