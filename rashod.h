#ifndef RASHOD_H
#define RASHOD_H

#include <QDialog>

namespace Ui {
class rashod;
}
/*!
    \brief Класс описывает логику работы с окном добавления расходов.
*/
class rashod : public QDialog
{
  Q_OBJECT

public:
/*!
    Конструктор принимает родительский класс.
*/
  explicit rashod(QWidget *parent = nullptr);
  ~rashod();
/*!
      \brief Метод для обновления и заполнения виджета QComboBox, в котором содержится информация о добавленных категориях.
*/
    void parse_serv();
private slots:
    void on_pushButton_clicked();

private:
  Ui::rashod *ui;
};

#endif // RASHOD_H
