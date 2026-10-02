/**
 * Сущность, описывающая имя человека.
 * Любой из параметров (фамилия, личное имя, отчество)
 * может быть не задан — тогда он не участвует в выводе.
 */
public class Name {
  private final String surname;
  private final String first_name;
  private final String patronymic;

  public Name(String surname, String first_name, String patronymic) {
    this.surname = normalize(surname);
    this.first_name = normalize(first_name);
    this.patronymic = normalize(patronymic);
  }

  public Name(String surname, String first_name) {
    this(surname, first_name, null);
  }

  public Name(String surname) {
    this(surname, null, null);
  }

  public String getSurname() {
    return surname;
  }

  public String getFirstName() {
    return first_name;
  }

  public String getPatronymic() {
    return patronymic;
  }

  // Приводим null и пустые строки к null, чтобы не проверять
  // это в каждом месте использования.
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

  public String to_string() {
    StringBuilder builder = new StringBuilder();
    append_part(builder, surname);
    append_part(builder, first_name);
    append_part(builder, patronymic);
    return builder.toString();
  }

  // Добавляет часть к результату, разделяя пробелом,
  // и молча пропускает незаданные (null) части.
  private static void append_part(StringBuilder builder, String part) {
    if (part == null) {
      return;
    }
    if (builder.length() > 0) {
      builder.append(' ');
    }
    builder.append(part);
  }
}