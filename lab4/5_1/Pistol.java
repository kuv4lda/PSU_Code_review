/**
 * Пистолет с ограниченным количеством патронов.
 * Пустой пистолет при выстреле издаёт «Клац!» — это часть
 * контракта, а не ошибка, поэтому исключение не бросаем.
 */
public class Pistol {
  // Константа стиля: kCamelCase.
  private static final int kDefaultBullets = 5;

  private int bullets;

  // Без аргумента — пистолет заряжен по умолчанию.
  public Pistol() {
    this(kDefaultBullets);
  }

  // С указанием начального количества патронов.
  public Pistol(int bullets) {
    if (bullets < 0) {
      throw new IllegalArgumentException(
          "Количество патронов не может быть отрицательным");
    }
    this.bullets = bullets;
  }

  public int getBullets() {
    return bullets;
  }

  /**
   * Выстрел. Если патроны есть — «Бах!» и минус один патрон,
   * иначе — «Клац!».
   */
  public void shoot() {
    if (bullets > 0) {
      System.out.println("Бах!");
      bullets--;
    } else {
      System.out.println("Клац!");
    }
  }

  @Override
  public String toString() {
    return to_string();
  }

  public String to_string() {
    return "Пистолет, патронов: " + bullets;
  }
}