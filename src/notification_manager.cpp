#include "notification_manager.h"

NotificationManager* NotificationManager::sInstance = 0;

NotificationManager* NotificationManager::Instance() {
  if (sInstance == 0) {
    sInstance = new NotificationManager();
  }

  return sInstance;
}

NotificationManager::NotificationManager() {
  mNotificationFont = TTF_OpenFont("res/fonts/gameboy.ttf", FONT_SIZE);
}

NotificationManager::~NotificationManager() {
  TTF_CloseFont(mNotificationFont);
  mNotificationFont = NULL;
}

void NotificationManager::update() {
  if (!mNotifications.empty()) {
    mNotifications.back()->update();
  }
}

void NotificationManager::render() {
  if (!mNotifications.empty()) {
    mNotifications.back()->render();
  }
}

void NotificationManager::addNotification(std::string text) {
  mNotifications.push_front(new Notification(text, mNotificationFont));
}

void NotificationManager::popNotification() {
  if (!mNotifications.empty()) {
    delete mNotifications.back();
    mNotifications.pop_back();
  }
}
