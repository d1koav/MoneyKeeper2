#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "rashod.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtDebug>
#include "dohod.h"
#include "category.h"
MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  this->setWindowTitle("MoneyKeeper");
  // Создание модели для подачи Sql запросов, для заполнения таблиц
  model = new QSqlQueryModel;
  // Создание, подключение к базе данных
  QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
  mydb.setDatabaseName("project.db");
  if(!mydb.open())
    qDebug()<< "Failed to open the db";
  else
    qDebug()<< "Connected...";
  //Обновление всех таблиц.
  parse_server();


}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_rashod_window_clicked()
{
    rashod dialog;
    dialog.setModal(true);
    dialog.exec();
    parse_server();
}

void MainWindow::on_category_window_clicked()
{
    category dialog;
    dialog.setModal(true);
    dialog.exec();
    parse_server();
}

void MainWindow::on_dohod_window_clicked()
{
    dohod dialog;
    dialog.setModal(true);
    dialog.exec();
    parse_server();
}
void MainWindow::parse_server()
{
    //обработка  SQL-запросов запись в таблицы соотвентсвующие
    QSqlQueryModel *modal3 = new QSqlQueryModel;
    modal3->setQuery("SELECT name as Category, SUM(cost) as Expenditure FROM Rashod LEFT JOIN Category ON Rashod.category_id  = Category.id GROUP BY name ORDER BY name");
    ui->tableView_3->setModel(modal3);
    ui->tableView_3->resizeColumnsToContents();

    QSqlQueryModel *modal2 = new QSqlQueryModel;
    modal2->setQuery("SELECT name as Category,SUM(cost) as Income FROM Dohod LEFT JOIN Category ON Dohod.category_id  = Category.id GROUP BY name ORDER BY name");
    ui->tableView_2->setModel(modal2);
    ui->tableView_2->resizeColumnsToContents();

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT name as Category, SUM(cost) as Expenditure FROM Rashod LEFT JOIN Category ON Rashod.category_id  = Category.id GROUP BY name ORDER BY SUM(cost) DESC LIMIT 5 ");
    ui->tableView_4->setModel(model);
    ui->tableView_4->resizeColumnsToContents();

    QSqlQueryModel *modal4 = new QSqlQueryModel;
    modal4->setQuery("SELECT name as Category,SUM(cost) as Income FROM Dohod LEFT JOIN Category ON Dohod.category_id  = Category.id GROUP BY name ORDER BY SUM(cost) DESC LIMIT 5");
    ui->tableView->setModel(modal4);
    ui->tableView->resizeColumnsToContents();
    // Подсчет текущего баланса

    QSqlQuery query;
    query.prepare("SELECT SUM(cost) FROM Dohod");
    query.exec();
    query.first();
    int doh =  query.value(0).toInt();
    query.clear();
    query.prepare("SELECT SUM(cost) FROM Rashod");
    query.exec();
    query.first();
    int ras = query.value(0).toInt();
    ui->razn->setText(QString::number(doh-ras));
    query.finish();

}

void MainWindow::on_tableView_2_doubleClicked(const QModelIndex &index)
{
  QString nam = ui->tableView_2->model()->data(ui->tableView_2->model()->index(index.row(), 0)).toString();
  float val = ui->tableView_2->model()->data(ui->tableView_2->model()->index(index.row(), 1)).toFloat();
  QSqlQuery query;
  query.prepare("SELECT id FROM Category WHERE name = :n");
  query.bindValue(":n",nam);
  query.exec();
  query.first();
  QString value = query.value(0).toString();
  QSqlQuery q;
  q.prepare("DELETE FROM Dohod WHERE category_id = :id AND cost = :c");
  q.bindValue(":id",value);
  q.bindValue(":c", val);
  q.exec();
  parse_server();
}


void MainWindow::on_tableView_3_doubleClicked(const QModelIndex &index)
{
    QString nam = ui->tableView_3->model()->data(ui->tableView_3->model()->index(index.row(), 0)).toString();
    float val = ui->tableView_3->model()->data(ui->tableView_3->model()->index(index.row(), 1)).toFloat();
    QSqlQuery query;
    query.prepare("SELECT id FROM Category WHERE name = :n");
    query.bindValue(":n",nam);
    query.exec();
    query.first();
    QString value = query.value(0).toString();
    QSqlQuery q;
    q.prepare("DELETE FROM Rashod WHERE category_id = :id AND cost = :c");
    q.bindValue(":id",value);
    q.bindValue(":c", val);
    q.exec();
    parse_server();
}

