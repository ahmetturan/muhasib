#ifndef KISTASGELIRLER_H
#define KISTASGELIRLER_H

#include <QDialog>
#include <QDate>
#include <QKeyEvent>
#include <QCloseEvent>
#include <QMessageBox>

namespace Ui {
class kistasgelirler;
}

class kistasgelirler : public QDialog
{
    Q_OBJECT
    
public:
    explicit kistasgelirler(QWidget *parent = 0);
    ~kistasgelirler();
    void ontanimliAyarlar();
    void ilkYukleme();
    bool getSecim();
    QDate getBaslangicTarih();
    QDate getBitisTarih();
    double getBaslangicTutar();
    double getBitisTutar();
    QStringList getSeciliTurler();
    bool getTutarEtkinMi();
    bool getTarihEtkinMi();
    bool getTurEtkinMi();
    void keyPressEvent(QKeyEvent *e);
    void closeEvent(QCloseEvent *event);

public slots:
    void tutarEtkin();
    void tarihEtkin();
    void turEtkin();
    void turCikar();
    void turEkle();
    void iptal();
    void tamam();
    
private:
    Ui::kistasgelirler *ui;
    bool secim;//tamam mı yoksa iptale mi basıldı
    bool tutarEtkinMi;//tamama tıklanırken sonra tutar cb'si tikli miydi
    bool tarihEtkinMi;//tamama tıklanırken sonra tarih cb'si tikli miydi
    bool turEtkinMi;//tamama tıklanırken sonra tur cb'si tikli miydi
};

#endif // KISTASGELIRLER_H
