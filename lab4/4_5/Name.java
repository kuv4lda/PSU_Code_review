/**
 * Имя человека: личное имя, фамилия, отчество.
 * Любой параметр, кроме личного имени, может быть не задан —
 * тогда он не участвует в текстовом представлении.
 *
 * Порядок аргументов в конструкторах: имя, [отчество],
 * фамилия. Такое наращивание отражает естественный порядок:
 * сначала есть имя, затем добавляется фамилия, затем отчество.
 */
public class Name {
  private final String first_name;
  private final String patronymic;
  private final String surname;

  // Полный вариант: имя, отчество, фамилия.
  public Name(String first_name, String patronymic,
              String surname) {
    this.first_name = normalize(first_name);
    this.patronymic = normalize(patronymic);
    this.surname = normalize(surname);
    if (this.first_name == null) {
      throw new IllegalArgumentException(
          "Личное имя должно быть задано");
    }
  }

  // Имя и фамилия (отчество не задано).
  public Name(String first_name, String surname) {
    this(first_name, null, surname);
  }

  // Только личное имя.
  public Name(String first_name) {
    this(first_name, null, null);
  }

  public String getFirstName() {
    return first_name;
  }

  public String getPatronymic() {
    return patronymic;
  }

  public String getSurname() {
    return surname;
  }

  /**
   * Приводим null и пустые строки к null, чтобы не проверять
   * это в каждом месте использования.
   */
  private static String normalize(String value) {
    if (value == null) {
      return null;
    }
    String trimmed = value.trim();
    return trimmed.isEmpty() ? null : trimmed;
  }

  @Override
  public String toString() {
    return to_string();
  }

  /**
   * Традиционное представление: Фамилия Имя Отчество.
   * Незаданные части пропускаются.
   */
  public String to_string() {
    StringBuilder builder = new StringBuilder();
    append_part(builder, surname);
    append_part(builder, first_name);
    append_part(builder, patronymic);
    return builder.toString();
  }

  // Добавляет часть, разделяя пробелом, и молча пропускает null.
  private static void append_part(StringBuilder builder,
                                  String part) {
    if (part == null) {
      return;
    }
    if (builder.length() > 0) {
      builder.append(' ');
    }
    builder.append(part);
  }
}