#ifndef CALISANEKLE_H
#define CALISANEKLE_H

#include <QDialog>
#include <QCalendarWidget>
#include <QDir>
#include <QComboBox>
#include <QCloseEvent>
#include <QSqlQuery>

namespace Ui {
class calisanekle;
}

class calisanekle : public QDialog
{
    Q_OBJECT
    
public:
    explicit calisanekle(QWidget *parent = 0);
    ~calisanekle();
    void ilkYukleme();
    void ontanimliAyarlar();
    void takvimAcikIseKapat();
    //QStringList getListeCbCalisanTur();
    void closeEvent(QCloseEvent *event);
    void setListeCalisanKonum(QStringList list);
    QStringList getListeCalisanKonum();
    QStringList getListeCalisan();
    double getToplamTutar();

public slots:
    void satirEkle(int,int);
    void satirSil();
    void tamam();
    void kapat();
    void takvimiAc(int,int);
    void tarihiAl();
    void hucreyeTiklandi(int,int);
    
private:
    Ui::calisanekle *ui;
    QCalendarWidget *cal;
    QStringList listeCalisan;
    //QStringList listeCbCalisanTur;
    //QStringList listeCalisanKonum;
    double toplamTutar;
    bool takvimAcik;
    int clsSutunSil;
    int clsSutunIsim;
    int clsSutunKonum;
    int clsSutunIseGiris;
    int clsSutunMaas;
    int clsSutunAciklama;
    int satir;
    int sutun;
};

#endif // CALISANEKLE_H
