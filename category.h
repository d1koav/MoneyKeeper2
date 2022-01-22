#ifndef CATEGORY_H
#define CATEGORY_H

#include <QDialog>

#include <QtSql>
namespace Ui {
class category;
}
/*!
    \brief Класс описывает логику работы с окном добавления категории расходов или доходов
*/
class category : public QDialog
{
  Q_OBJECT

public:
/*!
    Конструктор принимает родительский класс.
*/
  explicit category(QWidget *parent = nullptr);
  ~category();
/*!
      \brief Метод для заполнения таблицы и обновления данных, после добавления новой категории.
*/
  void parse_serv();

private slots:
/*!
      \brief Метод для добавления в таблицу новую категорию.
*/
  void on_add_cat_clicked();
  /*!
        \brief Метод для удаления в таблице определенной категории по ее индексу с помощью двойного клика по соответсвующей строке.

        Параметры:

        index - индекс категории в таблице.
*/
  void on_tableView_doubleClicked(const QModelIndex &index);

private:
  Ui::category *ui;
  QSqlQueryModel *model;
};

#endif // CATEGORY_H
