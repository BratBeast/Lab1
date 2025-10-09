# OOП Лаба 1 — Текстові документи + Сортування

## Варіант
- **Перелік 1:** Списки та алгоритми сортування(insertion sort, quicksort, merge sort. ) + інші алгоритми сортування; + реалізацію швидких алгоритмів, не заснованих на порівнянні (non-comparison sorts, наприклад counting, radix, bucket sort); + реалізацію загального механізму, що дозволить підключати нові алгоритми сортування;

- **Перелік 2:** Текстові документи (рівні a, b, c)

## Опис
Мета — продемонструвати базові ідеї ООП: класи, інкапсуляція, успадкування, статичний та динамічний поліморфізм.  
Домен: текстові документи як колекції об'єктів (речення, абзаци).

### Модулі
- `collections/` — шаблонний `List<T>`, `LinkedList<T>`, `ArrayList<T>`
- `algorithms/` — `SortingAlgorithm<T>`, `QuickSort`, `MergeSort`, `InsertionSort`
- `entities/` — ієрархія `TextEntity → Paragraph/Sentence`, `Document`, `TextAnalyzer`

### Структура проєкту
(усі файли лежать у кореневій директорії)

| Файл | Зміст |
|---|---|
| `List.h` | Шаблонний список (`List<T>`) та його реалізації (`LinkedList<T>`, `ArrayList<T>`). |
| `SortingAlgorithms.h` | Алгоритми сортування (`SortingAlgorithm<T>`, `QuickSort`, `MergeSort` та інші). |
| `TextEntities.h` | Класи документів, абзаців, речень (`TextEntity`, `Paragraph`, `Sentence`, `Document`). |
| `TextAnalyzer.h` | Аналіз та оркестрація сортування текстів (`TextAnalyzer`). |
| `main.cpp` | Демонстрація роботи програми. |
| `CMakeLists.txt` | Конфігурація збірки проєкту. |

---

## Збірка та запуск

#### Запуск в IDE (CLion, Visual Studio)
1. Відкрити папку проєкту.
2. Натиснути **Build** (🔨).
3. Натиснути **Run** (▶️).

#### Запуск з терміналу
```bash
mkdir build
cd build
cmake ..
cmake --build .
./Lab1