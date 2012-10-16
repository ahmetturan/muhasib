#ifndef KISTASCEK_H
#define KISTASCEK_H

#include <QDialog>
#include <QDate>
#include <QMessageBox>
#include <QCloseEvent>

namespace Ui {
class kistasCek;
}

class kistasCek : public QDialog
{
    Q_OBJECT
    
public:
    explicit kistasCek(QWidget *parent = 0);
    ~kistasCek();
    void ilkYukleme();
    QDate getBaslangicTarih();
    QDate getBitisTarih();
    QStringList getTurSecim();
    bool getSecim();
    bool getTurEtkinMi();
    bool getTarihEtkinMi();
    void ontanimliAyarlar();
    void closeEvent(QCloseEvent *event);
    void keyPressEvent(QKeyEvent *e);

public slots:
    void tamam();
    void iptal();
    void turEtkin();
    void tarihEtkin();
    
private:
    Ui::kistasCek *ui;
    bool secim;//tamam mı yoksa iptale mi basıldı
    bool turEtkinMi;//tamama tıklanırken sonra tur cb'si tikli miydi
    bool tarihEtkinMi;//tamama tıklanırken sonra tarih cb'si tikli miydi
};

#endif // KISTASCEK_H
