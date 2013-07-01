#ifndef HUMBUGWINDOW_H
#define HUMBUGWINDOW_H

#include "cookiejar.h"
#include "Config.h"

#include <QMainWindow>
#include <QTemporaryFile>
#include <QSystemTrayIcon>

#include <phonon/MediaObject>

// QtSparkle
#include <updater.h>

#ifdef Q_OS_WIN
#include <shobjidl.h>
#endif

class QAction;
namespace Ui
{
class HumbugWindow;
}

class QCloseEvent;
class QSystemTrayIcon;
class HWebView;
class QSignalMapper;
class IconRenderer;

class HumbugWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit HumbugWindow(QWidget *parent = 0);
    void setUrl(const QUrl &url);
    ~HumbugWindow();

    HWebView* webView() const;

public slots:
    void closeEvent(QCloseEvent *);

    void userQuit();
    void showAbout();
    void trayClicked();
    void linkClicked(const QUrl &url);
    void countUpdated(int newCount);
    void pmCountUpdated(int newCount);
    void displayPopup(const QString& title, const QString& content);

private slots:
    void domainSelected(const QString& domain);
    void checkForUpdates();

    void animateTray();

private:
    void setupTray();
    void setupSounds();

    void startTrayAnimation(const QList<QIcon>& stages);
    void stopTrayAnimation();

    void readSettings();
    QString domainToUrl(const QString& domain) const;

#ifdef Q_OS_WIN
    void setupTaskbarIcon();
    void setOverlayIcon(const QIcon& icon, const QString& desc);
#endif

    Ui::HumbugWindow *m_ui;

    // Tray icon
    IconRenderer *m_renderer;
    QSystemTrayIcon *m_tray;
    QTimer *m_trayTimer;
    int m_animationStep;
    QList<QIcon> m_animationStages;

    // Menu
    QSignalMapper *m_domainMapper;
    QHash<QString, QAction*> m_domains;
    QAction *m_checkForUpdates;

    CookieJar *m_cookies;
    QUrl m_start;

    // Audio
    Phonon::MediaObject *m_bellsound;
    QTemporaryFile m_sound_temp;

    int m_unreadCount, m_unreadPMCount;

    // Platform Specific
#ifdef Q_OS_WIN
    qtsparkle::Updater *m_updater;
    
#ifdef HAVE_THUMBBUTTON
    unsigned int m_IDTaskbarButtonCreated;
    ITaskbarList3* m_taskbarInterface;
#endif
#endif
};

#endif // HUMBUGWINDOW_H
