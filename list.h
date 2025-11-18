#/**
 * @file List.h
 * @brief Інтерфейси та реалізація динамічних списків.
 *
 * Цей файл містить шаблонний абстрактний клас List та його реалізації:
 * ArrayList (на основі масиву) та LinkedList (на основі зв'язного списку).
 */

#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <stdexcept>
#include <utility>

/**
 * @brief Абстрактний шаблонний клас для списку.
 * @tparam T Тип даних, що зберігаються у списку.
 */
template <typename T>
class List {
public:
    virtual ~List() = default;

    /**
     * @brief Додає елемент у кінець списку.
     * @param element Елемент, який потрібно додати.
     */
    virtual void add(const T& element) = 0;

    /**
     * @brief Отримує елемент за індексом.
     * @param index Індекс елемента (починаючи з 0).
     * @return Елемент типу T.
     * @throws std::out_of_range Якщо індекс виходить за межі списку.
     */
    virtual T get(size_t index) const = 0;

    /**
     * @brief Видаляє елемент за індексом.
     * @param index Індекс елемента для видалення.
     * @throws std::out_of_range Якщо індекс некоректний.
     */
    virtual void remove(size_t index) = 0;

    /**
     * @brief Повертає кількість елементів у списку.
     * @return size_t Розмір списку.
     */
    virtual size_t size() const = 0;

    /**
     * @brief Перевіряє, чи список порожній.
     * @return true, якщо список порожній, інакше false.
     */
    virtual bool isEmpty() const = 0;

    /**
     * @brief Замінює елемент за заданим індексом.
     * @param index Індекс елемента.
     * @param element Нове значення.
     */
    virtual void set(size_t index, const T& element) = 0;

    /**
     * @brief Обмінює місцями два елементи.
     * @param index1 Індекс першого елемента.
     * @param index2 Індекс другого елемента.
     */
    virtual void swap(size_t index1, size_t index2) {
        if (index1 >= size() || index2 >= size()) {
            throw std::out_of_range("Index out of range for swap");
        }
        T temp = get(index1);
        set(index1, get(index2));
        set(index2, temp);
    }

    /**
     * @brief Виводить елементи списку в консоль.
     */
    void print() const {
        for (size_t i = 0; i < size(); ++i) {
            std::cout << get(i) << "\n";
        }
    }
};

/**
 * @brief Реалізація списку на основі динамічного масиву.
 * @tparam T Тип елементів.
 */
template <typename T>
class ArrayList : public List<T> {
private:
    T* data;            ///< Вказівник на масив даних
    size_t currentSize; ///< Поточна кількість елементів
    size_t capacity;    ///< Поточна ємність масиву

    /**
     * @brief Збільшує ємність масиву вдвічі.
     */
    void resize() {
        capacity = (capacity == 0) ? 10 : capacity * 2;
        T* newData = new T[capacity];
        for (size_t i = 0; i < currentSize; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }

public:
    /**
     * @brief Конструктор ArrayList.
     */
    ArrayList() : data(nullptr), currentSize(0), capacity(0) {
        resize();
    }

    ~ArrayList() {
        delete[] data;
    }

    void add(const T& element) override {
        if (currentSize >= capacity) {
            resize();
        }
        data[currentSize] = element;
        currentSize++;
    }

    T get(size_t index) const override {
        if (index >= currentSize) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    void remove(size_t index) override {
        if (index >= currentSize) {
            throw std::out_of_range("Index out of range");
        }
        for (size_t i = index; i < currentSize - 1; ++i) {
            data[i] = data[i + 1];
        }
        currentSize--;
    }

    size_t size() const override {
        return currentSize;
    }

    bool isEmpty() const override {
        return currentSize == 0;
    }

    void set(size_t index, const T& element) override {
        if (index >= currentSize) {
            throw std::out_of_range("Index out of range for set");
        }
        data[index] = element;
    }

    void swap(size_t index1, size_t index2) override {
         if (index1 >= currentSize || index2 >= currentSize) {
            throw std::out_of_range("Index out of range for swap");
        }
        std::swap(data[index1], data[index2]);
    }
};

/**
 * @brief Реалізація списку на основі двозв'язного списку.
 * @tparam T Тип елементів.
 */
template <typename T>
class LinkedList : public List<T> {
private:
    /**
     * @brief Внутрішня структура для вузла списку.
     */
    struct Node {
        T value;
        Node* next = nullptr;
        Node* prev = nullptr;
        explicit Node(T val) : value(val) {}
    };

    Node* head = nullptr; ///< Вказівник на початок списку
    Node* tail = nullptr; ///< Вказівник на кінець списку
    size_t count = 0;     ///< Кількість елементів

    Node* getNode(size_t index) const {
        if (index >= count) return nullptr;
        Node* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return current;
    }

public:
    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    void add(const T& element) override {
        Node* newNode = new Node(element);
        if (isEmpty()) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        count++;
    }

    T get(size_t index) const override {
        if (index >= count) {
            throw std::out_of_range("Index out of range");
        }
        Node* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->value;
    }

    void remove(size_t index) override {
        if (index >= count) {
            throw std::out_of_range("Index out of range");
        }

        Node* toDelete = getNode(index);
        if (!toDelete) return;

        if (toDelete->prev) toDelete->prev->next = toDelete->next;
        else head = toDelete->next;

        if (toDelete->next) toDelete->next->prev = toDelete->prev;
        else tail = toDelete->prev;

        delete toDelete;
        count--;
    }

    size_t size() const override {
        return count;
    }

    bool isEmpty() const override {
        return count == 0;
    }

    void set(size_t index, const T& element) override {
        Node* node = getNode(index);
        if (node) {
            node->value = element;
        } else {
            throw std::out_of_range("Index out of range for set");
        }
    }
};

#endif // LIST_H