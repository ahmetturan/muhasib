#ifndef MAASEKLE_H
#define MAASEKLE_H

#include <QDialog>
#include <QDir>
#include <QComboBox>
#include <QCalendarWidget>
#include <QDebug>
#include <QCloseEvent>

namespace Ui {
class maasekle;
}

class maasekle : public QDialog
{
    Q_OBJECT
    
public:
    explicit maasekle(QWidget *parent = 0);
    ~maasekle();
    void ilkYukleme();
    void ontanimliAyarlar();
    QStringList getListeMaas();
    double getToplamTutar();
    void takvimAcikIseKapat();
    void setListeCalisanlar(QStringList list);
    QStringList getListeCbMaasTur();
    void setListeHesap(QStringList list);
    void closeEvent(QCloseEvent *event);
    void keyPressEvent(QKeyEvent *e);

public slots:
    void tamam();
    void kapat();
    void satirSil();
    void satirEkle(int,int);
    void tarihiAl();
    void takvimiAc(int a, int b);
    void hucreyeTiklandi(int a,int b);
    
private:
    Ui::maasekle *ui;
    QCalendarWidget *cal;
    QStringList listeMaas;//tamam a tıklanınca girişleri ana ekrana göndermek için
    QStringList listeCalisanlar;//maas ekle penceresinde calisan combobox unu doldurmak için
    QStringList listeCbMaasTur;
    QStringList listeHesap;//hesap isimlerini cb ye eklemek için
    bool takvimAcik;
    double toplamTutar;
    int msSutunSil;
    int msSutunTarih;
    int msSutunCalisan;
    int msSutunTutar;
    int msSutunAy;
    int msSutunTur;
    int msSutunHesap;
    int satir;
    int sutun;
};

#endif // MAASEKLE_H
