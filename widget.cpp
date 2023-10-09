#include "widget.h"
#include "ui_widget.h"
#include <QStyle>
#include <QFileDialog>
#include <QDir>
#include <QTime>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->pushButtonAdd->setIcon(style()->standardIcon(QStyle::SP_DirOpenIcon));
    ui->pushButtonPrev->setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward));
    ui->pushButtonPlay->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->pushButtonPause->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    ui->pushButtonNext->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));
    ui->pushButtonStop->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    ui->pushButtonMute->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
    this->muted = false;
    //ui->horizontalSliderProgres

    ////////////////// Player Init

    m_player = new QMediaPlayer(this);
    on_horizontalSliderVolume_valueChanged(70);
   // m_player->setVolume(70);
   // ui->labelVolume->setText(QString("Volume: ").append((QString::number(m_player->volume()))));
    ui->horizontalSliderVolume->setValue(m_player->volume());

    connect(m_player, &QMediaPlayer::durationChanged, this, &Widget::on_duration_changed);
    connect(m_player, &QMediaPlayer::positionChanged, this, &Widget::on_position_changed);

    //////////////////// PlayList /////////////////////

    m_playlist_model = new QStandardItemModel(this);
    ui->tablePlayList->setModel(m_playlist_model);
    m_playlist_model->setHorizontalHeaderLabels(QStringList() << tr("Audio Track")<<tr("file path"));
    ui->tablePlayList->setEditTriggers(QAbstractItemView::NoEditTriggers);

    m_playlist = new QMediaPlaylist(m_player);
    m_player->setPlaylist(m_playlist);

    connect(ui->tablePlayList, &QTableView::doubleClicked,
            [this](const QModelIndex& index){m_playlist->setCurrentIndex(index.row()); });
    connect(m_playlist, &QMediaPlaylist::currentIndexChanged,
            [this](int index)
    {
        ui->labelComposition->setText(m_playlist_model->data(m_playlist_model->index(index, 0)).toString());
    }
    );

}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButtonAdd_clicked()
{
//    QString file = QFileDialog::getOpenFileName(this,
//                                                tr("Open File"),
//                                                QString("C:\\Users\\User\\Desktop\\Music"),
//                                                tr("Audio Files (*.mp3 *.flac);; mp-3(*.mp3);; Flac (*.flac)")
//                                                );
//    QStringList path = file.split('/');
//    QString composition = path.back();

//    ui->labelComposition->setText(composition);
//    m_player->setMedia(QUrl::fromLocalFile(file));
//    m_player->play();
//    this->setWindowTitle("Media Player PU 211 - " + composition);

    QStringList files = QFileDialog::getOpenFileNames(
                this, tr("Open files"),
                QString("C:\\Users\\User\\Desktop\\Music"),
                tr("Audio Files (*.mp3 *.flac);; mp-3(*.mp3);; Flac)(*.flac)")
                );
    for(QString filesPath : files)
    {
        QList<QStandardItem*> items;
        items.append(new QStandardItem(QDir(filesPath).dirName()));
        items.append(new QStandardItem(filesPath));
        m_playlist_model->appendRow(items);
        m_playlist->addMedia(QUrl(filesPath));
    }


}


void Widget::on_horizontalSliderVolume_valueChanged(int value)
{
    ui->labelVolume->setText(QString("Volume: ").append(QString::number(value)));
    m_player->setVolume(value);

}


void Widget::on_pushButtonPlay_clicked()
{
    m_player->play();
}


void Widget::on_pushButtonPause_clicked()
{
    m_player->pause();
}


void Widget::on_pushButtonStop_clicked()
{
    m_player->stop();
}

void Widget::on_position_changed(qint64 position)
{
    ui->horizontalSliderProgres->setValue(position);
    QTime qt_position = QTime::fromMSecsSinceStartOfDay(position);
    ui->labelPlayed->setText(QString("Played: ").append(qt_position.toString("mm:ss")));
}


void Widget::on_duration_changed(qint64 duration)
{
    ui->horizontalSliderProgres->setMaximum(duration);
    QTime qt_duration = QTime::fromMSecsSinceStartOfDay(duration);
    ui->labelDuration->setText(QString("Duration: ").append(qt_duration.toString("mm:ss")));
}




void Widget::on_horizontalSliderProgres_valueChanged(qint64 position)
{
    m_player->setPosition(position);
}


void Widget::on_pushButtonMute_clicked()
{
    muted = !muted;
    m_player->setMuted(muted);
    ui->pushButtonMute->setIcon(style()->standardIcon(muted ? QStyle::SP_MediaVolumeMuted : QStyle::SP_MediaVolume));
}




