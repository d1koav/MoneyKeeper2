#ifndef DOHOD_H
#define DOHOD_H

#include <QDialog>

namespace Ui {
class dohod;
}
/*!
    \brief Класс описывает логику работы с окном добавления доходов.
*/
class dohod : public QDialog
{
  Q_OBJECT

public:

   /*!
      Конструктор принимает родительский класс.
  */
  explicit dohod(QWidget *parent = nullptr);
  ~dohod();

/*!
      \brief Метод для обновления и заполнения виджета QComboBox, в котором содержится информация о добавленных категориях.
*/
  void parse_serv();
private slots:
  void on_add_dohod_clicked();

private:
  Ui::dohod *ui;
};

#endif // DOHOD_H
