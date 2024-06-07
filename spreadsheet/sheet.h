#pragma once

#include "cell.h"
#include "common.h"

#include <functional>
#include <unordered_map>
#include <memory>
#include <iostream>

struct Hasher {
    size_t operator()(const Position p) const {
        return std::hash<std::string>()(p.ToString());
    }
};

struct Comparator {
    bool operator()(const Position& lhs, const Position& rhs) const {
        return lhs == rhs;
    }
};

class Sheet : public SheetInterface {
public:
    // Деструктор
    ~Sheet();

    // Устанавливает содержимое ячейки по указанной позиции
    void SetCell(Position pos, std::string text) override;

    // Возвращает константный указатель на ячейку по указанной позиции
    const CellInterface* GetCell(Position pos) const override;

    // Возвращает изменяемый указатель на ячейку по указанной позиции
    CellInterface* GetCell(Position pos) override;
    
    const Cell* GetCellPtr(Position pos) const;
    Cell* GetCellPtr(Position pos);

    // Очищает содержимое ячейки по указанной позиции
    void ClearCell(Position pos) override;

    // Возвращает размер печатаемой области таблицы
    Size GetPrintableSize() const override;

    // Выводит значения всех ячеек таблицы в переданный поток вывода
    void PrintValues(std::ostream& output) const override;

    // Выводит тексты всех ячеек таблицы в переданный поток вывода
    void PrintTexts(std::ostream& output) const override;

private:
    // Хранит ячейки таблицы, где ключ - позиция, а значение - уникальный указатель на ячейку
    std::unordered_map<Position, std::unique_ptr<Cell>, Hasher, Comparator> cells_;

    // Вычисляет размер области, которая участвует в печати
    Size CalculatePrintableSize() const;
};
