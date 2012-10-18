#ifndef KISTASDIGERGIDER_H
#define KISTASDIGERGIDER_H

#include <QDialog>
#include <QDate>
#include <QKeyEvent>
#include <QCloseEvent>
#include <QMessageBox>

namespace Ui {
class kistasdigergider;
}

class kistasdigergider : public QDialog
{
    Q_OBJECT
    
public:
    explicit kistasdigergider(QWidget *parent = 0);
    ~kistasdigergider();
    void ontanimliAyarlar();
    void ilkYukleme();
    bool getSecim();
    QDate getBaslangicTarih();
    QDate getBitisTarih();
    bool getTutarEtkinMi();
    bool getTarihEtkinMi();
    double getBaslangicTutar();
    double getBitisTutar();
    void keyPressEvent(QKeyEvent *e);
    void closeEvent(QCloseEvent *event);

public slots:
    void tutarEtkin();
    void tarihEtkin();
    void iptal();
    void tamam();
    
private:
    Ui::kistasdigergider *ui;
    bool secim;//tamam mı yoksa iptale mi basıldı
    bool tutarEtkinMi;//tamama tıklanırken sonra tur cb'si tikli miydi
    bool tarihEtkinMi;//tamama tıklanırken sonra tarih cb'si tikli miydi
};

#endif // KISTASDIGERGIDER_H
