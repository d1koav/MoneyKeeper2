/*!
  @mainpage Приложение для учета расходов и доходов
    ⚡Приложения для ведения базы данных доходов и расходов

    📄Приложение выполнено с помощью графической библиотеки Qt и программной библиотеки SQLite

    🔨Основные функции:

        - Добавление/удаление доходов

        - Добавление/удаление расходов

        - Добавление/удаление категорий

        - Удаление произовдится с помощью двойного клика по строке в таблицах.

    🔧В папке лежит база данных чтобы активировать её,
        необходимо скопировать/перенести её в папку с билдом программы

*/



#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QtSql>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
/*!
    \brief Класс описывает логику работы основного окна

    Основное окно содержит одну вкладку, 4 таблицы, 3 кнопки.

*/
class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
    /*!
    Конструктор принимает родительский класс.
*/
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  /*!
      \brief Метод для заполнения таблиц и обновления данных.
  */
  void parse_server();
private slots:
  /*!
    \brief Слот для обработки окна и показа его на экране.
  */
  void on_rashod_window_clicked();
  /*!
    \brief Слот для обработки окна и показа его на экране.
  */
  void on_category_window_clicked();
  /*!
    \brief Слот для обработки окна и показа его на экране.
  */
  void on_dohod_window_clicked();
  /*!
    \brief Слот для обработки двойного клика по строке в таблице и последующего удаления.
    Параметры:

    index - номер строки, которую нужно удалить.
  */
  void on_tableView_2_doubleClicked(const QModelIndex &index);
  /*!
    \brief Слот для обработки двойного клика по строке в таблице и последующего удаления.

    Параметры:

    index - номер строки, которую нужно удалить.
  */
  void on_tableView_3_doubleClicked(const QModelIndex &index);

private:
  Ui::MainWindow *ui;
  QSqlQueryModel *model;
};
#endif // MAINWINDOW_H
