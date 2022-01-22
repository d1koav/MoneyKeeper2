#include "category.h"
#include "ui_category.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtDebug>
#include <QMessageBox>
category::category(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::category)
{
  ui->setupUi(this);
  this->setWindowTitle("Добавление категории");
  model = new QSqlQueryModel;
  parse_serv();
}

category::~category()
{
  delete model;
  delete ui;
}
void category::parse_serv()
{
    model = new QSqlQueryModel(this);
    model->setQuery("SELECT name FROM Category");
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
    qDebug() << model->lastError();
}
void category::on_add_cat_clicked()
{
  QString txt = ui->cat->text();
  if(txt != "")
  {
    QSqlQuery query;
    query.prepare("SELECT * FROM Category WHERE name = :text");
    query.bindValue(":text", txt);
    query.exec();
    qDebug() << query.lastError();
    if (query.next())
    {
        QMessageBox::critical(this,"Ошибка добавления","Данная категория уже существует.");
        query.clear();
    }
    else
    {
      QSqlQuery ins;
      ins.prepare("INSERT INTO Category (name) VALUES(:text)");
      ins.bindValue(":text",txt);
      ins.exec();
      qDebug() << ins.lastError();
    }
    }
  else
  {
      QMessageBox::critical(this,"Ошибка добавления","Введены некорретные данные. \n Проверьте поля для ввода!");
  }
    parse_serv();
  }

void category::on_tableView_doubleClicked(const QModelIndex &index)
{
    QString name = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 0)).toString();
    QSqlQuery q;
    q.prepare("DELETE FROM Category WHERE name = :name ");
    q.bindValue(":name",name);
    q.exec();
    parse_serv();
}

