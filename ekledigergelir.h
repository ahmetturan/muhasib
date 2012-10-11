#ifndef EKLEDIGERGELIR_H
#define EKLEDIGERGELIR_H

#include <QDialog>
#include <QCalendarWidget>
#include <QDir>
#include <QComboBox>
#include <QCloseEvent>
#include <QDebug>

namespace Ui {
class ekledigergelir;
}

class ekledigergelir : public QDialog
{
    Q_OBJECT
    
public:
    explicit ekledigergelir(QWidget *parent = 0);
    ~ekledigergelir();
    void ontanimliAyarlar();
    void ilkYukleme();
    QStringList getListeDigerGelir();
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
    Ui::ekledigergelir *ui;
    QCalendarWidget *cal;
    QStringList listeDigerGelir;//tamam a tıklanınca girişleri ana ekrana göndermek için
    QStringList listeHesap;//hesap isimlerini cb ye eklemek için
    bool takvimAcik;
    double toplamTutar;
    int satir;
    int sutun;
    int dglSutunSil;
    int dglSutunTarih;
    int dglSutunIsim;
    int dglSutunKimden;
    int dglSutunTutar;
    int dglSutunAciklama;
    int dglSutunHesap;
};

#endif // EKLEDIGERGELIR_H
