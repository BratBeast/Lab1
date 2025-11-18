/**
 * @file TextAnalyzer.h
 * @brief Клас для аналізу та обробки текстових сутностей.
 *
 * Цей файл містить клас TextAnalyzer, який виступає фасадом для
 * операцій над текстом, зокрема для сортування та перевірки правил.
 */

#ifndef TEXT_ANALYZER_H
#define TEXT_ANALYZER_H

#include "TextEntities.h"
#include "list.h"
#include "SortingAlgorithms.h"
#include <memory>
#include <vector>
#include <string>

/**
 * @brief Псевдонім для типу даних, що підлягають сортуванню (вказівник на TextEntity).
 */
using SortableEntity = TextEntity*;

/**
 * @brief Клас-аналізатор для керування обробкою тексту.
 *
 * Цей клас реалізує патерн "Стратегія" для сортування, дозволяючи динамічно
 * змінювати алгоритм. Також він містить методи для перевірки структури документа.
 */
class TextAnalyzer {
private:
    /**
     * @brief Поточна стратегія сортування.
     */
    std::unique_ptr<SortingAlgorithm<SortableEntity>> sortStrategy;

public:
    /**
     * @brief Встановлює алгоритм сортування.
     * @param strategy Розумний вказівник на конкретний алгоритм сортування.
     *
     * Приклад використання:
     * @code
     * analyzer.setSortStrategy(std::make_unique<QuickSort<TextEntity*>>());
     * @endcode
     */
    void setSortStrategy(std::unique_ptr<SortingAlgorithm<SortableEntity>> strategy) {
        sortStrategy = std::move(strategy);
    }

    /**
     * @brief Виконує сортування списку сутностей.
     * @param entityList Список, який потрібно відсортувати.
     * @param comparator Функція-компаратор для порівняння двох елементів.
     *
     * Якщо стратегія не встановлена, виводить повідомлення про помилку в stderr.
     */
    void sort(List<SortableEntity>& entityList, std::function<bool(const SortableEntity&, const SortableEntity&)> comparator) {
        if (!sortStrategy) {
            std::cerr << "Error: Sorting strategy is not set!" << std::endl;
            return;
        }
        sortStrategy->sort(entityList, comparator);
    }

    // --- Методи для перевірки правил оформлення ---

    /**
     * @brief Перевіряє, чи всі зображення в документі мають підписи.
     * @param doc Документ для перевірки.
     * @return std::vector<std::string> Список знайдених помилок.
     * @note Наразі реалізовано як заглушка.
     */
    std::vector<std::string> checkImageCaptions(const Document& doc) {
        return {};
    }

    /**
     * @brief Знаходить речення, що перевищують задану кількість слів.
     * @param doc Документ для перевірки.
     * @param maxWordCount Максимально допустима кількість слів.
     * @return std::vector<std::string> Список занадто довгих речень.
     * @note Наразі реалізовано як заглушка.
     */
    std::vector<std::string> findLongSentences(const Document& doc, size_t maxWordCount) {
        return {};
    }
};

#endif // TEXT_ANALYZER_H