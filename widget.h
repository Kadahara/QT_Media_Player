#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMediaPlayer>
#include <QStandardItemModel>
#include <QMediaPlaylist>
#include <QMediaContent>


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void load_playlist(QString filename);
    void save_playlist(QString filename);

private slots:
    void on_pushButtonAdd_clicked();

    void on_horizontalSliderVolume_valueChanged(int value);

    void on_pushButtonPlay_clicked();
    void on_pushButtonPause_clicked();
    void on_pushButtonStop_clicked();

    void on_position_changed(qint64 position);
    void on_duration_changed(qint64 duration);

    void on_horizontalSliderProgres_valueChanged(qint64 value);

    void on_pushButtonMute_clicked();

    void on_tablePlayList_clicked(const QModelIndex &index);

    void on_pushButtonPrev_clicked();

    void on_pushButtonNext_clicked();

    void on_pushButtonCLR_clicked();

private:
    Ui::Widget *ui;

    QMediaPlayer* m_player;
    bool muted;
    const char* DEFAULTE_PLAYLIST = "C:/Users/User/Documents/build-MediaPlayerQt-Desktop_Qt_5_12_12_MinGW_64_bit-Debug/debug/playlist.m3u";
    bool play;
    QMediaPlaylist*     m_playlist;
    QStandardItemModel* m_playlist_model;

};
#endif // WIDGET_H
