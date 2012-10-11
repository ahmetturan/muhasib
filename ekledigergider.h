#ifndef EKLEDIGERGIDER_H
#define EKLEDIGERGIDER_H

#include <QDialog>
#include <QCalendarWidget>
#include <QDir>
#include <QComboBox>
#include <QCloseEvent>
#include <QDebug>

namespace Ui {
class ekledigergider;
}

class ekledigergider : public QDialog
{
    Q_OBJECT
    
public:
    explicit ekledigergider(QWidget *parent = 0);
    ~ekledigergider();
    void ontanimliAyarlar();
    void ilkYukleme();
    QStringList getListeDigerGider();
    void setListeHesap(QStringList list);
    double getToplamTutar();
    void takvimAcikIseKapat();
    void closeEvent(QCloseEvent *event);

public slots:
    void tamam();
    void satirSil();
    void satirEkle(int a, int b);
    void takvimiAc(int,int);
    void tarihiAl();
    void hucreyeTiklandi(int, int);
    void kapat();

private:
    Ui::ekledigergider *ui;
    QCalendarWidget *cal;
    QStringList listeDigerGider;//tamam a tıklanınca girişleri ana ekrana göndermek için
    QStringList listeHesap;//hesap isimlerini cb ye eklemek için
    bool takvimAcik;
    double toplamTutar;
    int satir;
    int sutun;
    int dgdSutunSil;
    int dgdSutunTarih;
    int dgdSutunIsim;
    int dgdSutunKimden;
    int dgdSutunTutar;
    int dgdSutunAciklama;
    int dgdSutunHesap;
};

#endif // EKLEDIGERGIDER_H
