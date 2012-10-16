#ifndef EKLECALISANKONUM_H
#define EKLECALISANKONUM_H

#include <QDialog>
#include <QSqlQuery>
#include "eklecalisan.h"

namespace Ui {
class ekleCalisanKonum;
}

class ekleCalisanKonum : public QDialog
{
    Q_OBJECT
    
public:
    explicit ekleCalisanKonum(QWidget *parent = 0);
    ~ekleCalisanKonum();
    void ilkYukleme();
    void ontanimliAyarlar();
    void veritabanindanYukle();
    void kaydet();

public slots:
    void satirEkle(int a, int b);
    void satirSil();
    void tamam();
    void iptal();
    
private:
    Ui::ekleCalisanKonum *ui;
    calisanekle form_calisanEkle;
    bool degisiklikIzle;//veritabanından bilgiler aktarılırken satır ekle fonksiyonuna girmemesi için
    int clskSutunSil;
    int clskSutunIsim;
};

#endif // EKLECALISANKONUM_H
