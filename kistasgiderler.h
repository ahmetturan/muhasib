#ifndef KISTASGIDERLER_H
#define KISTASGIDERLER_H

#include <QDialog>
#include <QDate>
#include <QKeyEvent>
#include <QCloseEvent>
#include <QMessageBox>

namespace Ui {
class kistasgiderler;
}

class kistasgiderler : public QDialog
{
    Q_OBJECT
    
public:
    explicit kistasgiderler(QWidget *parent = 0);
    ~kistasgiderler();
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
    Ui::kistasgiderler *ui;
    bool secim;//tamam mı yoksa iptale mi basıldı
    bool tutarEtkinMi;//tamama tıklanırken sonra tutar cb'si tikli miydi
    bool tarihEtkinMi;//tamama tıklanırken sonra tarih cb'si tikli miydi
    bool turEtkinMi;//tamama tıklanırken sonra tur cb'si tikli miydi
};

#endif // KISTASGIDERLER_H
