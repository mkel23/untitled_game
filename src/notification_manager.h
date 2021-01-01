#ifndef NOTIFICATION_MANAGER_H
#define NOTIFICATION_MANAGER_H

#include <deque>
#include <string>
#include <SDL2/SDL_ttf.h>
#include "notification.h"

class NotificationManager {
  public:
    static NotificationManager* Instance();
    NotificationManager(NotificationManager&) = delete;
    void operator=(const NotificationManager&) = delete;
    NotificationManager& operator=(NotificationManager&&) = delete;

    void update();

    void render();

    void addNotification(std::string text);

    void popNotification();

  private:
    const int FONT_SIZE = 12;
    static NotificationManager* sInstance;

    NotificationManager();
    ~NotificationManager();

    void operator delete(void *) {};

    std::deque<Notification*> mNotifications;

    TTF_Font* mNotificationFont;
};

#endif
